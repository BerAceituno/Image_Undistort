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
  $ ./Undistort <Parameters .xml file> <source to undistort>
```

where the inputs are:

  argv[1] = a .xml file containing the intrinsic parameters of the camera in openCV format (*check PARAMETERS.xml for reference*).
  
  argv[2] = the source to undistort:
        *  Imagelist     =  an .xml containing a list of images in opencv format (*check IMAGELIST.xml for reference*)
        *  Video         =  the absolute of relative path of a video file in .avi or .TOD format.
        *  Single Image  =  the absolute of relative path of an image file.

The outputs have **generic sequential names** depending on the type of input and are saved on the path of the executable file, therefore is recommended to move every undistorted frame to another folder to avoid overwriting.

**Distributed under an MIT License**
