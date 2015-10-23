# Image Undistort
Image and Video Undistort from extracted parameters software developed for the U.S.B. Mechatronics Group.

# Requirements

This software requires the following packages:

- CMake 2.6 or higher
- Opencv 2.0.0 or higher

And has been succesfully tested on Ubuntu 14.04 and 12.04, no GPU required.

# Installation

* **Download dependencies**

  To install CMake and Build-essentials enter your workspace and enter the following:
  
  ```
    $ sudo apt-get install build-essential
    $ sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
  ```
  
  then to install opencv enter:
  
  ```
    $ git clone https://github.com/Itseez/opencv.git
  ```
  
  once it finishes downloading it can be build by entering:
  
  ```
    $ cd ~/opencv
    $ mkdir release
    $ cd release
    $ cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
  ```  
    
  then it is build by entering:
  
  ```
    $ make
    $ sudo make install
  ```

* **Cloning the repository and building**

  locate the terminal in your workspace folder and enter:
  
  ```
    $ git clone https://github.com/BerAceituno/Image_Undistort.git
  ```
  
  locate the terminal in the source code folder and build by entering the following commands:
  
  ```
    $ cd Image_Undistort
    $ cmake . 
    $ make
  ```

# Use

The software is ran via terminal by locating in the build folder and entering:

```
  $ ./Undistort <Parameters .xml file> <source to undistort> <(Optional) Output directory>
```

where the inputs are:

  1. argv[1]  = a .xml file containing the intrinsic parameters of the camera in openCV format (*check PARAMETERS.xml for reference*).
  
  2. argv[2]  = the source to undistort:
        
        2.1.  Imagelist     =  an .xml containing a list of images in opencv format (*check IMAGELIST.xml for reference*)
        2.2.  Video         =  the absolute of relative path of a video file in .avi format.
        2.3.  Single Image  =  the absolute of relative path of an image file.
  3. argv[3]  = (optional) the output directory, imagefiles will be saved to the directory given, its important to                    remember that the path must be already created or else the saving process will fail.

**Distributed under an MIT License**
