#include <sstream>
#include <fstream>
#include <iomanip>

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class FileSelector{
	vector<string> imageFiles;
	Mat pupilBlacked;
	Mat resultFinal;
	Point2f mcentroid;
	Vec3f circleFound;
	Mat regionCropped;
	Mat pixelsOfIris;
	vector< vector<Point> > contours;

	
	public:	
	void readFile(bool);
	void unWrapping();
	void Result();
	void outerIrisContourDetection();
	void pupilSegmentation(Mat);
	vector<string> getImageFiles();
    void outputShow(int);
};
