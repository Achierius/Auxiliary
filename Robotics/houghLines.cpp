#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "enumCvType.h"

#include <iostream>

using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	VideoCapture camera(0);
	Mat pre;
	Mat image;
	Mat writing;
	namedWindow("Window", WINDOW_AUTOSIZE);
	namedWindow("Image", WINDOW_AUTOSIZE);
	writing = imread("FedExSide.jpeg");
	pre = imread("FedExSideLines.jpeg");
	int rho = 1;
	int theta = 180;
	int threshold = 49;
	int lineMin = 9;
	int maxGap = 49;
	createTrackbar("Theta", "Window", &theta, 180);
	createTrackbar("Rho", "Window", &rho, 100);
	createTrackbar("Threshold", "Window", &threshold, 199);
	createTrackbar("LineMin", "Window", &lineMin, 399);
	createTrackbar("MaxGap", "Window", &maxGap, 399);
	while(true)
	{
		/*camera>>pre;
		imwrite("FedExSide.jpeg", pre);
		waitKey(0);*/
		writing = imread("FedExSide.jpeg");
		Canny(pre, image, 50, 200, 3);
		vector<Vec4i> lines;
		//imshow("Image", image);
		cout<<enumCvType(image)<<"\n";
		HoughLinesP(image, lines, rho, CV_PI/theta, threshold+1, lineMin+1, maxGap+1 );
		for( size_t i = 0; i < lines.size(); i++ )
		{
			Vec4i l = lines[i];
			line(writing, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
		}
		
		imshow("Window", writing);
		waitKey(1);
	}
	return 0;
}	
