#include "opencv2/opencv.hpp"
#include "opencv2/face.hpp"
#include <fstream>
#include "IrisComparison.h"

using namespace std;
using namespace cv;
using namespace cv::face;

void IrisComparison::imageAndLabelGeneratorTemplate(){
	string currentLine;
    ifstream trainingFile("/home/chinmay/Downloads/iris/iris_unwrapped/iris_wrapped.txt");
 	while( getline(trainingFile, currentLine) ){
        vector<string> lineData;
        stringstream tempStreamData (currentLine);
        string singleElement;
        while ( getline(tempStreamData, singleElement, ' ') ) {
            lineData.push_back(singleElement);
        }
        Mat irisImage = imread(lineData[0], CV_LOAD_IMAGE_GRAYSCALE);
        int irisLabel = atoi(lineData[1].c_str());
        this->trainImage.push_back(irisImage);
        this->trainLabel.push_back(irisLabel);
    }
}

void IrisComparison::imageAndLabelGeneratorTest(int label){
string testString = "/home/chinmay/Downloads/iris/iris_unwrapped/S1001L10.jpg";
        Mat irisImage = imread(testString, CV_LOAD_IMAGE_GRAYSCALE);
        this->testImage.push_back(irisImage);
        this->testLabel.push_back(label);
}   

void IrisComparison::irisRecognizer(int label,int id){
		Ptr<LBPHFaceRecognizer> irisComparisonModel = createLBPHFaceRecognizer();
		irisComparisonModel->train(this->trainImage,this->trainLabel);
		int itr=0;
		bool flag_user_detected = false;
		int predictionLabel = irisComparisonModel->predict(this->testImage.at(itr));
        if(predictionLabel == this->testLabel.at(itr)){
                    flag_user_detected = true;
        }

	    if(flag_user_detected){
            cout << "User "<<id<<" is identified successfully. \nWelcome User "<<id<<"."<<endl;
        }
        else{
            cout<<"Incorrect User"<<endl;
        }

}


