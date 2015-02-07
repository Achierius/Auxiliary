#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
// ??? #include <opencv2/improc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <boost/lexical_cast.hpp>

using namespace cv;
using namespace std;
void selfie();
void sobel(int dy, int dx, int kernel);
void scharr(int dy, int dx);
void boxBlurr(int kernel);
void sobelOverlay(int dy, int dx, int kernel, int weight)
{
        Mat image;
	Mat overlay;
	Mat blurred;
        VideoCapture cap(0);
        if(!cap.isOpened()){cout<<"Error"; return;}
        while(true)
        {
                cap>>image;
		blur(image, blurred, cvSize(5, 5));
                Sobel(blurred, overlay, image.depth(), dx, dy, kernel);
                addWeighted(overlay, weight, image, 1, 0, image);
		imshow("Img", image);
		
                waitKey(1);
        }
}
void selfie()
{
    		 Mat image;
                 VideoCapture cap(0);
                 cap>>image;
                 imshow("Img", image);
                 imwrite("selfie.jpg", image);
                                waitKey(0);

}
void sobel(int dy, int dx, int kernel)
{
	Mat image;
	VideoCapture cap(0);
	if(!cap.isOpened()){cout<<"Error"; return;}
        while(true) 
        {
                cap>>image;
                Sobel(image, image, image.depth(), dx, dy, kernel);
                imshow("Img", image);
                waitKey(1);
        }	
}
void boxBlur(int kernel)
{
	Mat image;
        VideoCapture cap(0);
        if(!cap.isOpened()){cout<<"Error"; return;}
        while(true)
        {
                cap>>image;
		blur(image, image, cvSize(kernel, kernel));
                imshow("Img", image);
                waitKey(1);
        }
}
void boxBlur_scharr(int dy, int dx, int kernel)
{
	Mat image;
        VideoCapture cap(0);
        if(!cap.isOpened()){cout<<"Error"; return;}
        while(true)
        {
                cap>>image;
                blur(image, image, cvSize(kernel, kernel));
		Sobel(image, image, image.depth(), dx, dy, CV_SCHARR);
                imshow("Img", image);
                waitKey(1);
        }
}
void scharr(int dy, int dx)
{
	Mat image;
	VideoCapture cap(0);
	if(!cap.isOpened()){cout<<"Error"; return;}
	while(1)
	{
		cap>>image;
		Sobel(image, image, image.depth(), dx, dy, CV_SCHARR);
		imshow("Img", image);
		waitKey(1);
	}
}

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		using boost::lexical_cast;
                using boost::bad_lexical_cast;
		switch( lexical_cast<int>(argv[1]) )
		{
			case 0: //Sobel
				if(argc == 4)
				{
					sobel(lexical_cast<int>(argv[3]), lexical_cast<int>(argv[3]), lexical_cast<int>(argv[2]));
				}
				else
				{
					cout<<"Usage: ./vid 0 <kernelsize> <derivativeOrder>\n";
				}
				break;
			case 1: //Selfie
				selfie();
				break;
			case 10: 
				if(argc == 5)
				{
					cout<<"Performing overlay of sobel edge detection on normal vision\n";
					sobelOverlay(lexical_cast<int>(argv[3]), lexical_cast<int>(argv[3]), lexical_cast<int>(argv[2]), lexical_cast<int>(argv[4]));
				}	
				else
				{
					cout<<"Usage: ./vid 10 <kernelsize> <derivativeOrder> <amp>\n";
				}
				break;
			case 2: //Scharr
				if(argc == 4)
                                { 
					cout<<"Scharr filter with kernel size 3 and derivative order x "<<lexical_cast<int>(argv[2])<<" and derivative order y "<<lexical_cast<int>(argv[3])<<"\n";
                                        scharr(lexical_cast<int>(argv[2]), lexical_cast<int>(argv[3]));
                                } 
                                else
                                {
                                        cout<<"Usage: ./vid 2 <kernelsize> \n";
                                }
				break;
			case 3: //Box Blur
				if(argc == 3)
				{
					cout<<"Box Blur with blur size "<<argv[1]<<"\n";
					boxBlur(lexical_cast<int>(argv[2]));
				}
				else
				{
					cout<<"Proper usage: ./vid.o 3 <blurSize>\n";
				}
				break;
			case 32:
				if(argc == 5)
				{
					cout<<"Combined Box Blur followed by Scharr Filter with prior derivative orders (x,y) of "<<argv[2]<<" & "<<argv[3]<<" and blur size "<<argv[4]<<".\n";
					boxBlur_scharr(lexical_cast<int>(argv[2]), lexical_cast<int>(argv[3]), lexical_cast<int>(argv[4]));
				}
				else
				{
					cout<<"Proper usage:   ./vid.o <dx> <dy> <blurSize>   where either dx or dy is 1 and the other is 0\n";
				}
			default: 
				cout<<"Valid cases:  0: Sobel  1: Selfie  2: Scharr 3:  Box Blur\n";
				break;
		}
	}
	else
	{
		cout<<"Valid usage: ./vid -option- -paramenters*- \n";
	}
	return 1;
}
