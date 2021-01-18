Environment:
Linux Mint 19(64 bit)
OpenCV 3.2
gcc version 7.3.0 (Ubuntu 7.3.0-27ubuntu1~18.04)

For OpenCV installation you may use:
http://www.codebind.com/linux-tutorials/install-opencv-3-2-ubuntu-16-04/
https://www.learnopencv.com/install-opencv3-on-ubuntu/

To run the program:
1) Replace "/home/chinmay/Downloads" to change the path of:
a)In IrisProcessing.cpp: 
line 30: "<pwd>/iris/S1001L"
line 38: "<pwd>/iris/S1001L"
line 46:"<pwd>/iris/S1001L10.jpg"
line 166: "<pwd>/iris/iris_unwrapped/"

b)In IrisComparison.cpp
line 12: "<pwd>/iris/iris_unwrapped/iris_wrapped.txt"
line 28: "<pwd>/iris/iris_unwrapped/S1001L10.jpg"

2)In path "<pwd>/iris" run the following commands to execute the program:
i) g++ -c IrisProcessing.h IrisComparison.h
ii) g++ IrisProcessing.cpp IrisComparison.cpp IrisDetectionMain.cpp `pkg-config --cflags --libs opencv`
iii) ./a.out

*pwd - present working directory
