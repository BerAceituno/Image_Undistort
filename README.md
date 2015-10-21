# Camera Calibration
Camera calibration and parameter extraction software developed for the U.S.B. Mechatronics Group.

# Requirements

This software requires the following packages:

- CMake 2.6 or higher
- Opencv 2.0.0 or higher

And has been succesfully tested on Ubuntu 14.04 and 12.04, no GPU required.

# Installation

* Download dependencies

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

* Cloning the repository and building

locate the terminal in your workspace folder and enter:

```
  $ git clone https://github.com/BerAceituno/Camera_Calibration
```

locate the terminal in the source code folder and build by entering the following commands:

```
  $ cd Camera_Calibration
  $ cmake . 
  $ make
```

# Use

then you can run it by simply typing

```
  $ ./Calibracion <Input>
```

where the input must be a .xml settings file (for an example check USB_PICS.xml).

# Distributed under MIT License
