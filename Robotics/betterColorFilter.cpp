#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include "convert.hpp"
#include "enumCvType.h"
using namespace std;
using namespace cv;

void code();

int main( int argc, char* argv[] ) {

	code();
	return 0;

}

void code() {

	VideoCapture camera(0);
	Mat image;
	int minH = 20;
	int maxH = 80;
	int minS = 150;
	int maxS = 255;

	while(true) { // guided, color filter, canny, sharpen, hough
		VideoCapture camera
		camera>>image;
		cvtColor(image, image, CV_BGR2HSV);
		Mat * channels = new Mat [3];
		split(image, channels);
		imshow("PreHue", channels[0]);
		inRange(channels[0], Scalar(minH),Scalar(maxH), channels[0]);
		imshow("Hue", channels[0]);
		imshow("PreSat", channels[1]);
		inRange(channels[1], Scalar(minS),Scalar(maxS), channels[1]);
		imshow("Sat", channels[1]);
		bitwise_and(channels[0], channels[1], channels[0]);
		imshow("And", channels[0]);
		channels[1] = channels[0];
		channels[2] = channels[0];
		merge(channels, 3, image);
		dilate(image,image, Mat());
		//Sobel(image, image, image.depth(), 1, 1);	
		split(image, channels);
		Canny(image, channels[0], 100, 255);
		vector<Vec4i> lines;
		
		HoughLines(channels[0], lines, 5, CV_PI/90, 10, 20, 50);
		//source, dest, resolution of parameter r in pixels, theta size radians (CV_PI/90 = 2 degrees), Min intersections for lines, Minimum line length, max gap between line points
		//merge(channels, 3, image);
		/*for(size_t i = 0; i < lines.size(); i++);
		{
			Vec4i l = lines[i];
  			line( channels[0], Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
		}*/
		imshow("Edges", channels[0]);
		//imshow("hough", image);
		delete[] channels;
		//imshow("Output", image);
		waitKey(1);

	Mat image, image_gray, dst, abs_dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;


// guided, color filter, canny, sharpen, hough

		cap>>image;
		imshow("Pre", image);

		// guided filter (blur)
//		guidedFilter(guide, image, image, 4, 0.4, -1);
//		imshow("guided filter", image);

		// color filter
//		imshow("colorFilter", image);

		// Gaussian (blur)
		GaussianBlur( image, image, Size(7,7), 3, 0, BORDER_DEFAULT );
		imshow("Gaussian", image);

		// Canny (edge detection)
//		imshow("Canny", image);

		// grayscale for sharpen
		cvtColor( image, image_gray, COLOR_RGB2GRAY );

		// Laplacian (sharpen)
  		Laplacian( image_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
  		convertScaleAbs( dst, abs_dst );
  
			Mat * channels = new Mat [3];
			channels[0] = abs_dst;
			channels[1] = abs_dst;
			channels[2] = abs_dst;
			merge(channels, 3, abs_dst);
			addWeighted(image, 1, abs_dst, 2, 0, image); 

		imshow("Laplacian", image);

		// hough line
//		imshow("Hough Line", image);

		waitKey(1);
	}
}

