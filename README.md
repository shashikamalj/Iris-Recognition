## Iris-Recognition

# Intent of the Project
A simulation based project which analyses a set of NIR(Near-Infra-Red) greyscale images obtained from the CASIA(Chines Academy of Sciences Institute of Automation) database. Based on the assumption that the system is working in a scenario, in which a user would use his authentication ID, such as ID card, unique login data, in order to prepare the system to compare the input data against the user's data from the database. 
As this is a simulation based project, system works with only a certain type of images, and the algorithm is tuned to detect only these type of images. OpenCV library is used as to leverage image processing algorithms and created the application entirely in C++.

# Environment:
Linux Mint 19(64 bit)
OpenCV 3.2
gcc version 7.3.0 (Ubuntu 7.3.0-27ubuntu1~18.04)

For OpenCV installation you may use:

`<link>` :http://www.codebind.com/linux-tutorials/install-opencv-3-2-ubuntu-16-04/

`<link>` :https://www.learnopencv.com/install-opencv3-on-ubuntu/

# To run the program:

####Unordered list (plus sign and nested)
+Replace "./Downloads" to change the path of:
  +In IrisProcessing.cpp: 
    line 30: "<pwd>/iris/S1001L"
    line 38: "<pwd>/iris/S1001L"
    line 46:"<pwd>/iris/S1001L10.jpg"
    line 166: "<pwd>/iris/iris_unwrapped/"

  +In IrisComparison.cpp
    line 12: "<pwd>/iris/iris_unwrapped/iris_wrapped.txt"
    line 28: "<pwd>/iris/iris_unwrapped/S1001L10.jpg"

+In path "<pwd>/iris" run the following commands to execute the program:
  +g++ -c IrisProcessing.h IrisComparison.h
  +g++ IrisProcessing.cpp IrisComparison.cpp IrisDetectionMain.cpp `pkg-config --cflags --libs opencv`
  +./a.out

*pwd - present working directory
