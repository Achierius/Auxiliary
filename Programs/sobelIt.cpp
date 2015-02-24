#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		cout<<"Usage: ./sobelIt <inputName> <outputName>\n";
	}
	Mat image;
	int max = 100;
	int min = 50;
	namedWindow("Preview", WINDOW_AUTOSIZE);
	createTrackbar("Max", "Preview", &max, 500);
	createTrackbar("Min", "Preview", &min, 499);
	int stop = 1;
	while(stop != 0)
	{
		image = imread(argv[1]);
		imshow("Original", image);
		Canny(image, image, min, max);
		imshow("Preview", image);
		stop = waitKey(15);
		if(stop == 0)
		{
			break;
		}
		imwrite(argv[2], image);
	}
	return 0;
}

