#include "opencv2/opencv.hpp"
#include "opencv2/face.hpp"
#include <fstream>

using namespace std;
using namespace cv;
using namespace cv::face;

class IrisComparison{
	
	vector<Mat> trainImage;
	vector<int> trainLabel;
	vector<Mat> testImage;
	vector<int> testLabel;
	
	public:
	void imageAndLabelGeneratorTemplate();
	void imageAndLabelGeneratorTest(int);
	void irisRecognizer(int,int);
	
};
