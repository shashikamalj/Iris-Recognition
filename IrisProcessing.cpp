#include "IrisProcessing.h"
#include <sstream>
#include <fstream>
#include <iomanip>
#include <time.h>

#include "opencv2/opencv.hpp"

int fileCountLeft = 10;
int fileCountRight = 11;

using namespace std;
using namespace cv;


	vector<string> FileSelector::getImageFiles(){
    
    return this->imageFiles; 
}


void FileSelector::readFile(bool flag_train){
		// The for loop iterates through the folder and selects each file. This is to simulate a RT scenario
    int finalFilecounter = 0;
    int fileCount=1;
    
    if (flag_train){
        for(fileCount=1; fileCount < fileCountLeft; fileCount++){
            stringstream leftImagefile;
            leftImagefile << "./Downloads/iris/S1001L" << std::setfill('0') << std::setw(2) << fileCount << ".jpg";
            this->imageFiles.push_back(leftImagefile.str());
        }
        
        finalFilecounter += fileCount;
        
        for(fileCount=1; fileCount < fileCountRight; fileCount++){
            stringstream rightImagefile;
            rightImagefile << "./Downloads/iris/S1001R" << std::setfill('0') << std::setw(2) << fileCount << ".jpg";
            this->imageFiles.push_back(rightImagefile.str());
        }
        finalFilecounter += fileCount;
        cout<<"\nNumber of training images for detection model: "<<finalFilecounter-4<<endl;
        }
    else
    {
        string testFile = "./Downloads/iris/S1001L10.jpg";
        this->imageFiles.push_back(testFile);
    }
}

void FileSelector::pupilSegmentation(Mat actualImage){		
        Mat pupilmaskImage;
        inRange(actualImage, Scalar(30,30,30), Scalar(80,80,80), pupilmaskImage);
        
        findContours(pupilmaskImage.clone(), this->contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
       
		// Identifies and removes a noise area based on nearby areas that are larger than a specificied area value.
		
        vector< vector<Point> > noiseFilter;
        for(size_t i=0; i<this->contours.size(); i++){
           double area = contourArea(this->contours[i]);
           // Noise removal logic
           if(area > 50.0){
              noiseFilter.push_back(this->contours[i]);
           }
        }
        
		// If there are multiple contours present, then identify the one with center closest to the center of the image.
		
        vector<Point> contourFinal=noiseFilter[0];
        if(noiseFilter.size() > 1){
           double distanceImagecenter = 5000;
           int index = -1;
           Point2f centerOfOrigin(actualImage.cols/2, actualImage.rows/2);
           for(size_t i=0; i<noiseFilter.size(); i++){
              Moments tempMoments = moments(noiseFilter[i]);
              Point2f centerCurrent((tempMoments.m10/tempMoments.m00), (tempMoments.m01/tempMoments.m00));
              // Euclidean distance calculation
              double distEuclidean = norm(Mat(centerOfOrigin), Mat(centerCurrent));
              if(distEuclidean < distanceImagecenter){
                 distanceImagecenter = distEuclidean;
                 index = i;
              }
           }
           contourFinal = noiseFilter[index];
        }
        
		//Generate the contoured image
		
        vector< vector<Point> > drawBlack;
        drawBlack.push_back(contourFinal);
        this->pupilBlacked = actualImage.clone();
        drawContours(this->pupilBlacked, drawBlack, -1, Scalar(0,0,0), CV_FILLED);

		//Compute the centroid, in order to align the contours that are outside and inside
		
        Moments momentCentroid = moments(contourFinal, true);
        Point2f mcentroid(momentCentroid.m10/momentCentroid.m00, momentCentroid.m01/momentCentroid.m00);
        this->mcentroid=mcentroid;
}

		void FileSelector::outerIrisContourDetection(){
        
        // Identify the outer contour using canny filter
        Mat cannyBlacked, preprocessed;
        Canny(this->pupilBlacked, cannyBlacked, 5, 70, 3);
        GaussianBlur(cannyBlacked, preprocessed, Size(7,7), 0, 0);

        // Execution of Hough Circle Function
        int i = 80;
        
        while (i < 151){
           vector< Vec3f > storageVector;
           // These parameter values are for the sample images considered for the simulation
           HoughCircles(preprocessed, storageVector, CV_HOUGH_GRADIENT, 2, 100.0, 30, i, 100, 140);
           if(storageVector.size() == 1){
              this->circleFound = storageVector[0];
              break;
           }
           i++;
        }
		}

		void FileSelector::Result(){
			                
        Mat maskImage = Mat::zeros(this->pupilBlacked.rows, this->pupilBlacked.cols, CV_8UC1);
        circle(maskImage, this->mcentroid, this->circleFound[2], Scalar(255,255,255), CV_FILLED);
        this->resultFinal = Mat::zeros(this->pupilBlacked.rows, this->pupilBlacked.cols, CV_8UC1);
        this->pupilBlacked.copyTo(this->resultFinal, maskImage);
        

        // Selecting necessary region from Iris image
        int radiusIris = this->circleFound[2];
        int x = int(this->mcentroid.x - radiusIris);
        int y = int(this->mcentroid.y - radiusIris);
        int w = int(radiusIris * 2) + 2;
        int h = w;
        //cout<<" x "<<x<<" y "<<y<<" w "<<w<<" h "<<h<<endl  ;       
        this->regionCropped = resultFinal( Rect(x,y,w,h) ).clone();		
   		
        }
		
		void FileSelector::unWrapping(){
			        // Unwrapping 
        Mat unwrappedData;
        Point2f centerValue (float(this->regionCropped.cols/2.0), float(this->regionCropped.cols /2.0));
        logPolar(this->regionCropped, unwrappedData, centerValue, 40, INTER_LINEAR +  WARP_FILL_OUTLIERS);

        // Isolating the region of Interest
        Mat thresholdMatrix;
        threshold(unwrappedData, thresholdMatrix, 10, 255, THRESH_BINARY);
        findContours(thresholdMatrix.clone(), this->contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
        Rect ROI = boundingRect(this->contours[0]);
        this->pixelsOfIris = unwrappedData(ROI).clone();
		}
		
		void FileSelector::outputShow(int imageCounter){
        
        string outputFileName = this->imageFiles.at(imageCounter);
        stringstream tempMoments(outputFileName);
        string item;
        while( getline(tempMoments, item, '/') ){
        }

        stringstream tempMoment2;
        tempMoment2 << "./Downloads/iris/iris_unwrapped/" << item;
        imwrite(tempMoment2.str(), this->pixelsOfIris);
}
	

