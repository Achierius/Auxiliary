#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> 

using namespace cv;
using namespace std;

void sharpenMask (int dy, int dx); 

void sharpenMask (int dy, int dx) {
	Mat image;
	Mat blurred;  	
	Mat mask; 	
	Mat shp; 
	double t = 5;
	double amt = 1; 
	VideoCapture cap (0); 
	if(!cap.isOpened()) {
		cout<< "Error";
		return; 
	}
	while (true) {
		cap>>image; 
		imshow("Image", image);
		GaussianBlur(image, blurred, cvSize(11, 11), dx, dy, BORDER_DEFAULT);
 		mask = abs(image - blurred) < t;
		shp = image*(1+amt) + blurred*(-amt); 
		image.copyTo(shp, mask);  
		imshow("Smoothed", shp); 
		// addWeighted(image, 1.5, temp, -0.5, 0, image); 

	}

} 

int main(int argc, char* argv[])
{
	
	sharpenMask(1,1); 
	return 1;
}
	
