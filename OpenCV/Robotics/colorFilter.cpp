#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include "convert.hpp"

//#include "enumCvType.h"

//#include <chrono>
//#include <boost/lexical_cast.hpp>
//#include <thread>

using namespace cv;


int main(int argc, char* argv[])
{	
	bool end = false;
	VideoCapture camera(0);
	Mat image;
	Mat blurImage;
	namedWindow("output", WINDOW_AUTOSIZE);
	camera>>image;
	//std::cout<<enumCvType(image)<<"\n";
	//image.convertTo(image, CV_64F);
	//std::cout<<enumCvType(image)<<"\n";
	while(!end) //Color Filter, bilateral filter, sobel, sharpen
	{
		camera>>image;
		cvtColor(image,image,CV_BGR2HSV);
		Mat * channels = new Mat[3];
		/*image = cv::Scalar(60, 60, 60);
		Mat * channels = new Mat [3];
		split(image, channels);
		//inRange(image, Scalar(0, 0, 0), Scalar(255, 255, 255), blurImage);
//addWeighted(blurImage, -1, image, 1, 0, image);
		RGB conv = RGB(0,0,0);
		HSV convd = HSV(0, 0, 0);
		
		for(int x = 0; x < channels[0].rows; x++) {
			for(int y = 0; y < channels[0].cols; y++) {
				conv.b = channels[0].at<TYP>(x,y);
				conv.g = channels[1].at<TYP>(x,y);
				conv.r = channels[2].at<TYP>(x,y);
				convd = rgb2Hsv(conv);
				channels[0].at<TYP>(x,y) = convd.h;
				channels[1].at<TYP>(x,y) = convd.s;
				channels[2].at<TYP>(x,y) = convd.v;
			}
		}
		std::cout << image.at<cv::Vec3b>(10, 10) << std::endl;
		cvtColor(image, image, CV_BGR2HSV);
		std::cout << image.at<cv::Vec3b>(10, 10) << std::endl;
		merge(channels, 3, image);
		std::cout << image.at<cv::Vec3b>(10, 10) << std::endl;
		delete[] channels;*/
		//std::cin>>conv.g;
		split(image, channels);
		imshow("pre", channels[0]);
		
		/* Min Hoo's Erosion stuff
		Mat dilation_dst;
		dilation_dst = erosion(channels[0]);
		imshow("erosion", dilation_dst);
		*/

		imshow("Saturation", channels[1]); // saturation

		inRange(channels[0], Scalar(22), Scalar(38), channels[0]);
		
		Mat imageL, image_gray, dst, abs_dst;
		int kernel_size = 3;
		int scale = 1;
		int delta = 0;
		int ddepth = CV_16S;	

		GaussianBlur( image, imageL, Size(3,3), 0, 0, BORDER_DEFAULT );
		cvtColor( imageL, image_gray, COLOR_RGB2GRAY );

		Laplacian( image_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
		convertScaleAbs( dst, abs_dst );
			//Mat* lChannels = new Mat [3];
			channels[0] = abs_dst;	
			channels[1] = abs_dst;
			channels[2] = abs_dst;

			inRange(channels[0], Scalar(22), Scalar(38), channels[0]);
			merge (channels, 3, image);
			cvtColor(image, image, CV_GRAY2RGB);
			imshow("Laplace Hue", image);
			addWeighted(imageL, 1, abs_dst, 2, 0, imageL);			
		imshow ("Laplacian Demo", imageL);
		

/*
		Mat image, blurred, mask, shp;
		double t = 5;
		double amt = 1;

		GaussianBlur(image, blurred, cvSize(11, 11), 0, 0, BORDER_DEFAULT);		
		mask = abs(image - blurred) < t;
		shp = image*(1+amt) + blurred*(-amt);
		image.copyTo(shp, mask);
		imshow("Radhika's", shp);
*/	

		inRange(channels[0], Scalar(22), Scalar(38), channels[0]);
		imshow("output", channels[0]);
		//channels[0].convertTo(channels[0], CV_8U);
		merge(channels, 3, image);
		cvtColor(image,image,CV_HSV2BGR);
		imshow("post", image);
		//std::cin>>conv.g;
		//channels = new Mat [3];
		/*split(image, channels);
		inRange(channels[2], Scalar(200),Scalar(255) , channels[2]);
		channels [0] = channels[2];
		channels [1] = channels[2];
		//mask[0].convertTo(mask[0], CV_8U);
		//channels[0] += mask[0];
		merge(channels, 3, image);*/ //HSV?
		/*Mat maskmin = image.clone();
		Mat maskmax = image.clone();
		split(maskmin, channels);
		channels[0] = Scalar(20); //B 40
		channels[1] = Scalar(150); //G 210
		channels[2] = Scalar(160); //R 220
		merge(channels, 3, maskmin);
		split(maskmax, channels);
                channels[0] = Scalar(120); //80
                channels[1] = Scalar(255); //245
                channels[2] = Scalar(255); //255
		merge(channels, 3, maskmax);
		imshow("unproc", image);
		imshow("min", maskmin);
		imshow("max", maskmax);
		inRange(image, maskmin,maskmax, image);
		delete[] channels;
		imshow("preproc", image);
		bilateralFilter(image, blurImage, 5, 20, 20); //source, dest, diameter of pixel neighborhood processed at once, sigmaColor, sigmaSpace 
		blur(blurImage, blurImage, cvSize(11,11));	
		Sobel(blurImage, blurImage, blurImage.depth(), 2, 2);
		blur(blurImage, blurImage, cvSize(5, 5));
		blurImage *= 50;
		imshow("output", blurImage);*/
		waitKey(1);	
	}
	
}
/* Min Hoo's Erosion code (doesn't work)
Mat erosion( Mat* channels ) {
	int erosion_type = 0;
	int erosion_elem = 0;
	int erosion_size = 0;
	int dilation_elem = 0;
	int dilation_size = 0;
	int const max_elem = 2;
	int const max_kernel_size = 21;
	
	if( erosion_elem == 0 ) { erosion_type = MORPH_RECT; }
	else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
	else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

	element = getStructuringElement( erosion_type, Size( 2*erosion_size + 1, 2*erosion_size+1 ), Point( erosion_size, erosion_size ) ); // Apply the erosion operation
	dilate( image, dilation_dst, element );

	return dilation_dst;
} */
