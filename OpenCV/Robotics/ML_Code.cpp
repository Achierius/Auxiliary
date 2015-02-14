#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

void sharpenTest( int dy, int dx );

// void guidedFilter( InputArray guide, InputArray src, OutputArray dst, int radius, double eps, int dDepth );

int main( int argc, char* argv[] ) {

	sharpenTest(1,1);
	return 1;

}

void sharpenTest( int dy, int dx ) {

	Mat image, image_gray, dst, abs_dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;


	// load video
	VideoCapture cap(0);
	if(!cap.isOpened()) {
		cout<< "Error";
		return;
 	}
	

	while(true) { // guided, color filter, canny, sharpen, hough

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

