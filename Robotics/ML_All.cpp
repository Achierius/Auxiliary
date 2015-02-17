#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
 
using namespace cv;
using namespace std;

void work();

int main( int argc, char* argv[] ) {

	work();
	return 0;

}

void work() {

	Mat image, image2, resImg, detailImg, image_gray, dst, abs_dst, kernel;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	// load video
	VideoCapture cap(1);
	if(!cap.isOpened()) {
		cout << "Error \n";
		return;
 	}
	
	while(true) { // gaussian, color filter, canny, sharpen, hough
		Mat * channels = new Mat[3];
		Mat * channels2 = new Mat[3];	
		cap >> image;


		// Gaussian (blur)
		GaussianBlur(image, image, Size(7,7), 13, 13, BORDER_DEFAULT);
		imshow("Gaussian", image);

	
		// Double Gaussian (gives error)
/*		GaussianBlur(image, image2, Size(7,7), 7, 4, BORDER_DEFAULT);
		filter2D (image2, resImg, -1, kernel , Point(-1,-1), 0, BORDER_DEFAULT); // Double Gaussian (gives error)
		detailImg = image - resImg;
		image = resImg + detailImg;
		imshow("DoubleGaussian", image);
*/

/*		// MATLAB version of Double Gaussian (reference only)
		int Radius = 7;
		int EdgeStrength = 4;

		LPF = fspecial('gaussian', Radius, EdgeStrength);

		detailImg = origImg - imfilter(origImg, LPF, 'replicate');

		resultImg = imfilter(origImg, LPF, 'replicate') + detailImg;



		// Another way is to use conv2 function rather than imfilter

		detailImg = origImg - conv2(origImg, LPF, 'same');

		resultImg = conv2(origImg, LPF, 'same') + detailImg;
*/


		cvtColor(image, image, CV_BGR2HSV); // convert from RGB to HSV
		split(image, channels);
		split(image, channels2);


		// yellow tote color filter
/*		int minH = 20; // not 40-160 // not 0-10
		int maxH = 40;
		int minS = 140; // 150-255 works // 150-255 is iffy
		int maxS = 255;
*/		int erosion_size = 2;
		int erosion_type = 1;

		int minH = 10; // 19
		int maxH = 60; // 55
		int minS = 125; // 135
		int maxS = 255; // 255
		int minV = 100; // 108 
		int maxV = 255; // 248

		Mat element = getStructuringElement(erosion_type = MORPH_RECT, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size)); // element for erosion and dilation

//		imshow("PreHueY", channels[0]); // Hue before thresholds
		inRange(channels[0], Scalar(minH), Scalar(maxH), channels[0]);
		imshow("HueY", channels[0]); // Hue with non-yellow removed
		erode(image, image, element, Point(-1, -1), 2);
//		imshow("PreSatY", channels[1]); // Sat before thresholds
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
		imshow("PreErodeDilateY", image);
		erode(image, image, element, Point(-1, -1), 4); // eradicate black holes
		dilate(image, image, element, Point(-1, -1), 8);
		erode(image, image, element, Point(-1, -1), 4);
		imshow("ErodeDilateY", image);

		
/*		// reflective tape color filter
		int minH2 = 50; // neon hue = 123 (174) // not 55-95, not 45-53 // 53-55 works
		int maxH2 = 100;
		int minS2 = 30; // neon sat = 155 (0.61) // not 20-40 // 15-20 works
		int maxS2 = 50;
		int minV2 = 230; // neon value = 255 (1.0) // 230-255 works
		int maxV2 = 255;
*/

		int minH2 = 44;
		int maxH2 = 87;
		int minS2 = 0;
		int maxS2 = 86;
		int minV2 = 234;
		int maxV2 = 255;

//		imshow("PreHueR", channels2[0]);
		inRange(channels2[0], Scalar(minH2), Scalar(maxH2), channels2[0]);
		imshow("HueR", channels2[0]);
//		imshow("PreSatR", channels2[1]);
		inRange(channels2[1], Scalar(minS2), Scalar(maxS2), channels2[1]);	
		imshow("SatR", channels2[1]);
//		imshow("PreValueR", channels[2]);
		inRange(channels2[2], Scalar(minV2), Scalar(maxV2), channels2[2]);
		imshow("ValueR", channels2[2]);	
		bitwise_and(channels2[0], channels2[1], channels2[1]);
		bitwise_and(channels2[1], channels2[2], channels2[2]);
		imshow("HS AndR", channels2[1]);
		imshow("SV AndR", channels2[2]);
			channels2[0] = channels2[2];
			channels2[1] = channels2[2];
		merge(channels2, 3, image2);		
		imshow("PreDilateErodeR", image2);
		addWeighted(image, 1, image2, 1, 0, image);	
		imshow("PreDilateErodeAll", image);


		// erode and dilate three times both in order to eradicate black noise
		dilate(image, image, element, Point(-1, -1), 4);
  		erode(image, image, element, Point (-1, -1), 8);
		dilate(image, image, element, Point(-1, -1), 4);
		imshow("DilateErodeAll", image);


		// Canny (edge detection) 
		split(image, channels);
		Canny(image, channels[1], 100, 255);
			channels[0] = channels[1];
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


		// Laplacian (sharpen)
		cvtColor( image, image_gray, COLOR_RGB2GRAY ); // HSV to grayscale
  		Laplacian( image_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
  		convertScaleAbs( dst, abs_dst );
  			channels[0] = abs_dst;
			channels[1] = abs_dst;
			channels[2] = abs_dst;
			merge(channels, 3, abs_dst);
			addWeighted(image, 1, abs_dst, 2, 0, image); 
		imshow("Laplacian", image);

		delete [] channels;
		delete [] channels2;
		waitKey(1);
	}

}

