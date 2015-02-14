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
		Canny(pre, image, 50, 200, 3);
		vector<Vec4i> lines;
		Mat * channels = new Mat [3];
		split(image, channels);
		inRange(channels[0], Scalar(minH), Scalar(maxH), channels[0]);
		imshow("desu", channels[0]);
		HoughLines(channels[0], lines, 1, CV_PI/180, 50, 50, 10);
		for( size_t i = 0; i < lines.size(); i++ )
		{
			Vec4i l = lines[i];
			line( channels[0], Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
		}
		imshow("Window", channels[0]);
		waitKey(1);
	}
	return 0;
}	
