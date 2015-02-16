#include "opencv2/highgui/highgui.hpp"
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
	namedWindow("Window", WINDOW_AUTOSIZE);
	int minH = 20;
	int maxH = 80;
	while(true)
	{
		camera>>pre;
		cvtColor(pre, pre, CV_BGR2HSV);	
		Mat*channels = new Mat [3];
		split(pre, channels);
		inRange(channels[0], Scalar(minH), Scalar(maxH), channels[0]);
		merge(channels, 3, image);
		delete[] channels;
		cvtColor(pre, pre, CV_HSV2BGR);
		imshow("Original", pre);
		imshow("Colors", image);
		Canny(image, image, 50, 200, 3);
		cvtColor(image, image, COLOR_GRAY2BGR);
		vector<Vec4i> lines;
		waitKey(0);
		HoughLines(image, lines, 1, CV_PI/180, 50, 50, 10);
		waitKey(0);
		imshow("PreLines", image);
		for( size_t i = 0; i < lines.size(); i++ )
		{
			Vec4i l = lines[i];
			line(image, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
		}
		imshow("Window", image);
		waitKey(1);
	}
	return 0;
}	
