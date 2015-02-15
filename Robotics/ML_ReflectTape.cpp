#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

void reflectiveTape();

int main() {

	reflectiveTape();
	return 0;

}

void reflectiveTape() {
	
	Mat image, image_gray


	VideoCapture cap (0);
	if (!cap.isOpened()) {
		cout<<"Error \n"
		return;
	}
	
	while (true) {
	


	}
	
	waitKey(0);

}
