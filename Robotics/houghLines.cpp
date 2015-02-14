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
	namedWindow("Window", WINDOW_AUTOSIZE);
	namedWindow("Image", WINDOW_AUTOSIZE);
	while(true)
	{
		camera>>pre;
		Canny(pre, image, 50, 200, 3);
		vector<Vec4i> lines;
		Mat * channels = new Mat[3];
		cout<<"Image: "<<enumCvType(image)<<"\n";
		/*split(image, channels);
		inrange(channels[0], Scalar(20), Scalar(80), channels[0]); 
		merge(channels, 3, image);*/
		waitKey(0);
		imshow("Image", image);
		waitKey(0);
		HoughLines(image, lines, 1, CV_PI/180, 50, 50, 10 );
		for( size_t i = 0; i < lines.size(); i++ )
		{
			Vec4i l = lines[i];
			line( image, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
		}
		imshow("Window", image);
		delete[] channels;
		waitKey(1);
	}
	return 0;
}	
