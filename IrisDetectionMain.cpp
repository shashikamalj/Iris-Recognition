#include <sstream>
#include <fstream>
#include <iomanip>
#include<iostream>
#include "opencv2/opencv.hpp"
#include "IrisProcessing.h"
#include "IrisComparison.h"

using namespace std;
using namespace cv;

int read_input()
{
    double input = -1;
    bool valid= false;
    do
    {
        cout << "Please Enter User ID: " << flush;
        cin >> input;
        if (cin.good())
        {
            //everything went well, we'll get out of the loop and return the value
            valid = true;
        }
        else
        {
            //something went wrong, we reset the buffer's state to good
            cin.clear();
            //and empty it
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "\nInvalid input, please re-enter. \n" << endl;
        }
    } while (!valid);

    return (input);
}
void validateTestImage(IrisComparison irisComparator)
{
    int id = 0;   
    int label = 0;
    
        while(label == 0){
        id = read_input();
        switch(id){
            case 1: label = 1;
                    break;
            case 2: label = 2;
                    break;
            default: 
                    {
                        cout << "\nPlease Enter Correct User ID!\n "<<endl;
                        label = 0;
                        break;
                    }
        }   
    }
    cout<<endl;
    
    FileSelector fileSelector;
    fileSelector.readFile(false);
    
    Mat actualImage = imread(fileSelector.getImageFiles()[0], IMREAD_GRAYSCALE);
    cout<<"User image has been read.\n"<<endl;
	fileSelector.pupilSegmentation(actualImage);
		
     // STEP 2: Identify the contour of iris outer
	fileSelector.outerIrisContourDetection();
    // STEP 3: Create the mask for the image
	fileSelector.Result();
    // STEP 4: Cropping Unwrapping followed by Radial Unwrapping 
	fileSelector.unWrapping();
	// STEP 5: Save output from the previous step
	fileSelector.outputShow(0);
    
   	// Read in the file with the images and labels
    // File should be in format name<space>label<enter>

    //tStart = clock();
    
    irisComparator.imageAndLabelGeneratorTest(label);
    irisComparator.irisRecognizer(label,id); 

}

int main( int argc, const char** argv )
{

	FileSelector fileSelector;
    IrisComparison irisComparator; 
    cout<<"//////////////////////////////////////////////////////////////////////////////////////////////"<<endl;
    cout<<"                           Iris Detection System"<<endl;
    cout<<"//////////////////////////////////////////////////////////////////////////////////////////////"<<endl;

	fileSelector.readFile(true);

	// This for loop iterates through each image and then performs segmentation and normalization on them.
    /* Do your stuff here */

   for(int imageCounter=0; imageCounter < fileSelector.getImageFiles().size(); imageCounter++){
		
        Mat actualImage = imread(fileSelector.getImageFiles()[imageCounter], IMREAD_GRAYSCALE);

		// STEP 1: the pupil needs to be segmented
		fileSelector.pupilSegmentation(actualImage);
		
        // STEP 2: Identify the contour of iris outer
		fileSelector.outerIrisContourDetection();
        // STEP 3: Create the mask for the image
		fileSelector.Result();
       // STEP 4: Cropping Unwrapping followed by Radial Unwrapping 
		fileSelector.unWrapping();
		// STEP 5: Save output from the previous step
		fileSelector.outputShow(imageCounter);
	}

    irisComparator.imageAndLabelGeneratorTemplate();  
    clock_t tStart = clock();
    validateTestImage(irisComparator);
    cout<<endl;
    cout<<endl;   
    return 0;
    
}
