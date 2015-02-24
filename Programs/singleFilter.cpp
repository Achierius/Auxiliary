#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
 
using namespace cv;
using namespace std;

void singleImage(Mat image);

int main( int argc, char* argv[] ) {
	
	Mat image;

	while(true) {
		image = imread(argv[1]);
		singleImage(image);
		waitKey(1);
	}	
	return 0;

}

void singleImage(Mat image) {

	Mat image2, image_gray, dst, abs_dst, kernel;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	Mat * channels = new Mat[3];	
	Mat * channels2 = new Mat[3];	


	// Gaussian (blur)
	GaussianBlur(image, image, Size(7,7), 13, 13, BORDER_DEFAULT);
///	imshow("Gaussian", image);


	// convert from RGB to HSV		
	cvtColor(image, image, CV_BGR2HSV);
	split(image, channels);
	split(image, channels2);

	
	// yellow tote color filter
	int erosion_size = 2;
	int erosion_type = 1;	
	int minH = 0; // 19
	int maxH = 30; // 55
	int minS = 150; // 135
	int maxS = 200; // 255
	int minV = 160; // 108 
	int maxV = 190; // 248

	Mat element = getStructuringElement(erosion_type = MORPH_RECT, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size)); // element for erosion and dilation

//	imshow("PreHueY", channels[0]); // Hue before thresholds
	inRange(channels[0], Scalar(minH), Scalar(maxH), channels[0]);
	imshow("HueY", channels[0]); // Hue with non-yellow removed
	erode(image, image, element, Point(-1, -1), 2);
//	imshow("PreSatY", channels[1]); // Sat before thresholds
	inRange(channels[1], Scalar(minS), Scalar(maxS), channels[1]);
	imshow("SatY", channels[1]); // Sat 
	inRange(channels[2], Scalar(minV), Scalar(maxV), channels[2]);
	imshow("ValueY", channels[2]);	
	bitwise_and(channels[0], channels[1], channels[1]); // Hue + Sat
	bitwise_and(channels[1], channels[2], channels[2]);
	imshow("HS AndY", channels[2]); // Hue + Sat
		channels[0] = channels[2];
		channels[1] = channels[2];
	merge(channels, 3, image);
//	imshow("PreErodeDilateY", image);
	erode(image, image, element, Point(-1, -1), 4); // eradicate black holes
	dilate(image, image, element, Point(-1, -1), 8);
	erode(image, image, element, Point(-1, -1), 4);
///	imshow("ErodeDilateY", image);

		
/*	// reflective tape color filter
	int minH2 = 44;
	int maxH2 = 87;
	int minS2 = 0;
	int maxS2 = 86;
	int minV2 = 234;
	int maxV2 = 255;

//	imshow("PreHueR", channels2[0]);
	inRange(channels2[0], Scalar(minH2), Scalar(maxH2), channels2[0]);
	imshow("HueR", channels2[0]);
//	imshow("PreSatR", channels2[1]);
	inRange(channels2[1], Scalar(minS2), Scalar(maxS2), channels2[1]);	
	imshow("SatR", channels2[1]);
//	imshow("PreValueR", channels[2]);
	inRange(channels2[2], Scalar(minV2), Scalar(maxV2), channels2[2]);
	imshow("ValueR", channels2[2]);	
	bitwise_and(channels2[0], channels2[1], channels2[1]);
	bitwise_and(channels2[1], channels2[2], channels2[2]);
	imshow("HS AndR", channels2[1]);
	imshow("SV AndR", channels2[2]);
		channels2[0] = channels2[2];
		channels2[1] = channels2[2];
	merge(channels2, 3, image2);		
///	imshow("PreDilateErodeR", image2);
	addWeighted(image, 1, image2, 1, 0, image);	
///	imshow("PreDilateErodeAll", image);


	// erode and dilate three times both in order to eradicate black noise
	dilate(image, image, element, Point(-1, -1), 4);
 	erode(image, image, element, Point (-1, -1), 8);
	dilate(image, image, element, Point(-1, -1), 4);
///	imshow("DilateErodeAll", image);


	// Canny (edge detection) 
	split(image, channels);
	Canny(image, channels[1], 100, 255);
		channels[0] = channels[1];
		channels[2] = channels[0];
	merge(channels, 3, image);
///	imshow("Canny", image);	


	// Laplacian (sharpen)
	cvtColor( image, image_gray, COLOR_RGB2GRAY ); // HSV to grayscale
  	Laplacian( image_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
  	convertScaleAbs( dst, abs_dst );
  		channels[0] = abs_dst;
		channels[1] = abs_dst;
		channels[2] = abs_dst;
		merge(channels, 3, abs_dst);
		addWeighted(image, 1, abs_dst, 2, 0, image); 
///	imshow("Laplacian", image);
*/
	delete [] channels;
	delete [] channels2;

}

