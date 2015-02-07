#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <chrono>
//#include <boost/lexical_cast.hpp>
#include <thread>
using namespace cv;
void input(int * pTi_data)
{
	while(true)
	{
		std::cin>>*pTi_data;
		std::cout<<*pTi_data;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	return;
}

void show(Mat cvM_image)
{
	imshow("Image", cvM_image);
	waitKey(3);
	return;	
}

int main(int argc, char* argv[])
{
	int * pTi_data = new int [1];
	*pTi_data = 1;
	std::thread t_in(&input, pTi_data);
	t_in.detach();
	Mat cvM_image;
	VideoCapture cvVC_camera(0);
	while(*pTi_data != 0)
	{
		cvVC_camera>>cvM_image;
		switch(*pTi_data)
		{
			case 0: //Break
				return 1;
			case 1: //Normal
				true;
				break;
			case 2: //Sharpen
				break;
			case 3: //Sobel
				Sobel(cvM_image, cvM_image, cvM_image.depth(), 1, 1);
				break;
			case 4: //Gauss
				GaussianBlur(cvM_image, cvM_image, cvSize(15, 15), 3);
				break;
			case 5: //Box
				blur(cvM_image, cvM_image, cvSize(15, 15));
				break;
			case 6: //Color
				Mat* channels = new Mat [3];
	                        split(cvM_image, channels);
				inRange(channels[2], Scalar(150, 255, 255), Scalar(255, 255, 255), channels[2]);
				merge(channels, 3, cvM_image);
				delete[] channels;	
				break;
		}
		show(cvM_image);
	}
}
