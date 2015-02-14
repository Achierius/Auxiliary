#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include "enumCvType.h"
#include <string>
using namespace cv;
int main(int argc, char* argv[])
{

	Mat image;
	Mat * channels = new Mat [3];
	VideoCapture cap(0);
	std::string in = argv[1];
	
	while(true)
	{
		cap>>image;
		cvtColor(image, image, CV_BGR2HSV);
		split(image, channels);
		if(in == ("a"))
		{
			std::cout<<"Hue\n";
			imshow("image", channels[0]);
		}
                else if(in == ("b"))
                {
			std::cout<<"Saturation\n";
                        imshow("image", channels[1]);
                }
                else if(in == ("c"))
                {
			std::cout<<"Value/Lightness?\n";
                        imshow("image", channels[2]);
                }
		else if(in == ("d"))
		{
			std::cout<<"All";
			imshow("hue", channels[0]);
			imshow("saturation", channels[1]);
			imshow("value/lightness?", channels[2]);
		}
		else
		{
			imshow("image", image);
		}
		waitKey(1);
	}
	return 0;
}
