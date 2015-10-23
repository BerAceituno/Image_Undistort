/*********************************************************************/
/* File: Undistort.cpp                                               */
/* Last Edition: 14/10/2015, 01:54 PM.                               */
/*********************************************************************/
/* Programmed by:                                                    */
/* Bernardo Aceituno C                                               */
/* Jose Cappelletto						     */
/*********************************************************************/
/*Image undistort program, takes the Output .XML and the source as   */
/*inputs and outputs the undistorted source (image, list or video    */
/*Requires OpenCV 2.0.0 or higher                                    */
/*********************************************************************/

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <time.h>

#include <boost/filesystem.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif
    
using namespace cv;
using namespace std;

bool readStringList( const string& filename, vector<string>& l){

    l.clear();

    FileStorage fs(filename, FileStorage::READ);
    
    if( !fs.isOpened() ) return false;
    
    FileNode n = fs.getFirstTopLevelNode();
    
    if( n.type() != FileNode::SEQ ) return false;
    
    FileNodeIterator it = n.begin(), it_end = n.end();
    
    for( ; it != it_end; ++it) l.push_back((string)*it);
    
    return true;
}

int main(int argc, char* argv[]){
	
    //declares the camera coefficient arrays
    Mat cameraMatrix, distCoeffs;

    //declares the image dimensions
    int width, height;

    //reads the time
    time_t tm;
    time( &tm );
    struct tm *t2 = localtime( &tm );
    char t3[1024];
    strftime(t3, sizeof(t3)-1, "%x%X", t2);

    const string time_str = string(t3);

    //determines if the two inputs arguments are given
    if(argc < 3){
        cout << "Error! wrong or no input provided!" << endl;
        cout << "Usage: > Undistort calibration_file file_input file_output" << endl;
        cout << "HELP: argv[1] is the .XML calibration file" << endl;
        cout << "      argv[2] is the source imagefile" << endl;
        cout << "      argv[3] is the output imagefile" << endl;
        cout << "See -h option for further details" << endl;
        return -1;
    }

	//checks if an output path has been provided
    string BasePath;
    if(argc == 4){
	BasePath = string(argv[3]);
    }
    else{
	BasePath = string("");
    }

    if(argv[2]=="-h"){
        cout << "Help:" << endl;
        cout << "argv[1]: calibration .XML in OpenCV format." << endl;
        cout << "argv[2]: Input source" << endl;
        cout << "     .xml: assumed for imagelist" << endl; 
        cout << "     .avi: for video (testing)" << endl;
        cout << "         : other formats will be assumed for image" << endl; 
        cout << "argv[3]: Output file [optional]" << endl;

        return 0;
    }

    //reads the .xml file
    const string CoeffFilename = argv[1];
    FileStorage f(CoeffFilename,FileStorage::READ); 

    //declares the name of the output
    const string InputFilename = argv[2];;   

    //reads the data form the input
    f["Camera_Matrix"] >> cameraMatrix;
    f["Distortion_Coefficients"] >> distCoeffs;
    f["image_Width"] >> width;
    f["image_Height"] >> height;

    //determines the filetype
    const string filetype = (InputFilename.substr(InputFilename.find_last_of(".")));

    //Computes the compression parameters for the camera
    vector<int> compression_params; //vector that stores the compression parameters of the image
    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY); //specify the compression technique
    compression_params.push_back(100); //specify techniquehe compression quality
    
    //
    if(filetype == ".xml" || filetype == ".XML") {
        //declares some variables
        vector<string> imageList;

        //reads the imagelist
        bool readed = readStringList(InputFilename, imageList);

        if(!readed){
            cout << "Failed to open image list" << endl;
        }

        //declares the matrix for the current image
        Mat image;

        //size of tue image
        Size imageSize;

        //declares a counter for the loop
        int atImageList = 0;

        //reads the first image from the list
        image = imread(imageList[atImageList++], CV_LOAD_IMAGE_COLOR);

        //enters the calibration loop
        while(atImageList < (int)imageList.size()){
            //gets the image size
            imageSize = image.size();
            //declares the outputs
            Mat Output(width, height, CV_16UC3, Scalar(0,50000, 50000));
            
            //remaps the input
            Mat map1, map2;
            initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(), getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0), imageSize, CV_16SC2, map1, map2);
            remap(image, Output, map1, map2, INTER_LINEAR);

            //gets the name of the original file
	    	string fullpath = imageList[atImageList];
	    	string filename = fullpath.substr(fullpath.find_last_of("/") + 1,fullpath.length() - 4);

	    	ostringstream Namefr;


	    	if(filename.empty()) Namefr << "ŔEMAP_" << fullpath;
	    	else Namefr << BasePath << "ŔEMAP_" << filename;

	    	//saves the undistorted file
			bool save = imwrite(Namefr.str(), Output, compression_params);
  
          	//checks if the image was saved correctly;
            if(!(save)){
                cout << "Frame could not be saved" << endl;
                return -1;
            }

            //loads the next image
            image = imread(imageList[atImageList++], CV_LOAD_IMAGE_COLOR);

	    	//cout << "image " << atImageList << " done!" << endl; 
        }
    }
    else if(filetype == ".avi"){
        VideoCapture Video(InputFilename);
        if(!Video.isOpened()){
            cout << "Video could not be opened!" << endl;
            return -1;
        }

        //declares the variable for each frame
        Mat image;

        //size of tue image
        Size imageSize;

        //reads the first fream
        bool bSuccess = Video.read(image);

        //gets the name of the input
        string videoname = InputFilename.substr(InputFilename.find_last_of("/") + 1,InputFilename.length() - 4);
        
        //declares a counter
        int cnt = 0;

        while(!image.empty()){
            if(!bSuccess){
                cout << "error with the frame" << endl;
                return -1;
            }

            //gets the image size
            imageSize = image.size();

            //declares the outputs
            Mat Output(width, height, CV_16UC3, Scalar(0,50000, 50000));
            
            //remaps the input
            Mat map1, map2;
            initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(), getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0), imageSize, CV_16SC2, map1, map2);
            remap(image, Output, map1, map2, INTER_LINEAR);

            //saves the remaped frame
            ostringstream namevidefr;
            namevidefr << BasePath << "REMAP_" << videoname << "_" << cnt << ".jpg";
            bool save = imwrite(namevidefr.str(), Output, compression_params);

            //checks if the image was saved correctly;
            if(!(save)){
                cout << "video frame could not be saved" << endl;
                return -1;
            }

            //reads the next image
            bSuccess = Video.read(image);

            //increases the counter
            cnt++;
        }
    }
    else{
        //reads the image
        Mat image = imread(argv[2],CV_LOAD_IMAGE_UNCHANGED);

        //checks if the image is empty
        if(image.empty()){
            cout << "Error! invalid imagefile" << endl;
            return -1;
        }

        //gets the size of the image
        Size imageSize = image.size();

        //declares the outputs
        Mat Output(width, height, CV_16UC3, Scalar(0,50000, 50000));
        
        //remaps the input
        Mat map1, map2;
        initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(), getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0), imageSize, CV_16SC2, map1, map2);
        remap(image, Output, map1, map2, INTER_LINEAR);

        //saves the calibrated frame
        bool save = imwrite("REMAP_"+InputFilename, Output, compression_params);

        //checks if it was saved correctly
        if(!(save)){
            cout << "Image could not be saved" << endl;
            return -1;
        }

        cout << "image stored!" << endl;
    }
    
    return 0;
}
