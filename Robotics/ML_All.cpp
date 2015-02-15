#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
 
using namespace cv;
using namespace std;

void sharpenTest();

int main( int argc, char* argv[] ) {

	sharpenTest();
	return 0;

}

void sharpenTest() {

	Mat image, image_gray, dst, abs_dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	int minH = 20;
	int maxH = 60;
	int minS = 150;
	int maxS = 255;
	int minH2 = 60; // neon hue = 156.7 (111)
	int maxH2 = 90;
	int minS2 = 215; // neon sat = 234.6 (0.92)
	int maxS2 = 245;
	int minV2 = 230; // neon value = 255 (1.0)
	int maxV2 = 255;

	// load video
	VideoCapture cap(0);
	if(!cap.isOpened()) {
		cout<< "Error \n";
		return;
 	}
	
	while(true) { // gaussian, color filter, canny, sharpen, hough
		Mat * channels = new Mat[3];	
		cap>>image;

		// Gaussian (blur)
		GaussianBlur( image, image, Size(7,7), 3, 0, BORDER_DEFAULT );
		imshow("Gaussian", image);

		cvtColor(image, image, CV_BGR2HSV); // convert from RGB to HSV
		split(image, channels);
/*		imshow("PreHue", channels[0]); // Hue before thresholds
		// yellow tote color filter
		inRange(channels[0], Scalar(minH), Scalar(maxH), channels[0]);
		imshow("Hue", channels[0]); // Hue with non-yellow removed
		imshow("PreSat", channels[1]); // Sat before thresholds
		inRange(channels[1], Scalar(minS), Scalar(maxS), channels[1]);
		imshow("Sat", channels[1]); // Sat 
		bitwise_and(channels[0], channels[1], channels[0]);
		imshow("And", channels[0]); // Hue + Sat
			channels[1] = channels[0];
			channels[2] = channels[0];
		merge(channels, 3, image);
		imshow("PreCanny", image);
*/		

		// reflective tape color filter
		imshow("PreHueReflective", channels[0]);
		inRange(channels[0], Scalar(minH2), Scalar(maxH2), channels[0]);
		imshow("HueReflective", channels[0]);
		imshow("PreSatReflective", channels[1]);
		inRange(channels[1], Scalar(minS2), Scalar(maxH2), channels[1]);	
		imshow("Sat", channels[1]);
		imshow("PreValueReflective", channels[2]);
		inRange(channels[2], Scalar(minV2), Scalar(maxV2), channels[2]);
		imshow("ValueReflective", channels[2]);	

		// Canny (edge detection) 
		dilate(image, image, Mat());
		split(image, channels);
		Canny(image, channels[0], 100, 255);
			channels[1] = channels[0];
			channels[2] = channels[0];
		merge(channels, 3, image);
		imshow("Canny", image);
		
		

		// Hough Line
		//vector<Vec4i> lines;
		
		//HoughLines(channels[0], lines, 5, CV_PI/90, 10, 20, 50);
		/*source, dest, resolution of parameter r in pixels, theta size radians (CV_PI/90 = 2 degrees), Min intersections for lines, Minimum line length, max gap between line points
		merge(channels, 3, image);
		for(size_t i = 0; i < lines.size(); i++);
		{
			Vec4i l = lines[i];
  			line( channels[0], Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
		}*/
		// imshow("Edges", channels[0]);
		// imshow("hough", image);
		// imshow("Output", image);


		imshow("Pre", image);

		// grayscale for sharpen
		cvtColor( image, image_gray, COLOR_RGB2GRAY );

		// Laplacian (sharpen)
  		Laplacian( image_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
  		convertScaleAbs( dst, abs_dst );
  
			channels[0] = abs_dst;
			channels[1] = abs_dst;
			channels[2] = abs_dst;
			merge(channels, 3, abs_dst);
			addWeighted(image, 1, abs_dst, 2, 0, image); 

		imshow("Laplacian", image);

		delete [] channels;
		waitKey(1);
	}

}

