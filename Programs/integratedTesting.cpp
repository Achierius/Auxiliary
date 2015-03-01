#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

Mat gaussianBlur(Mat in, int blur_ksize, int sigmaX, int sigmaY); 

Mat colorFilter(Mat in, int hMin = 0, int hMax = 255, int sMin = 0, int sMax = 255, int vMin = 0, int vMax = 255, bool DEBUG = false, bool DEBUGPRE = false, bool bitAnd = true);

Mat dilateErode(Mat in, int holes, int noise, Mat element);

Mat edgeDetect(Mat image, Mat * channels, int edge_ksize, int threshLow, int threshHigh);

Mat sharpen(Mat image, Mat * channels, int ddepth, int sharpen_ksize, int scale, int delta);

Mat houghLines(Mat in, int rho, int theta, int threshold, int lineMin, int maxGap);

Mat gaussianBlur(Mat in, int blur_ksize, int sigmaX, int sigmaY) 
{
	if ((blur_ksize%2 != 1) && (blur_ksize > 1)) // kernel size must be odd and positive
		blur_ksize = blur_ksize*2+1;
	GaussianBlur(in, in, Size(blur_ksize, blur_ksize), sigmaX, sigmaY, BORDER_DEFAULT);
	return in;
}

Mat colorFilter(Mat in, int hMin = 0, int hMax = 255, int sMin = 0, int sMax = 255, int vMin = 0, int vMax = 255, bool DEBUG = false, bool DEBUGPRE = false, bool bitAnd = true)
{
 
        bool hueAltered = false;
	bool satAltered = false;
	bool valAltered = false;

	if(DEBUG) imshow("PreFiltered", in);
        cvtColor(in, in, CV_BGR2HSV);
        Mat * channels = new Mat [3];
        split(in, channels);

        if(hMin != 0 || hMax != 255)
        {
		hueAltered = true;
//                if(DEBUGPRE) imshow("Hue-Unfiltered", channels[0]);
                inRange(channels[0], Scalar(hMin), Scalar(hMax), channels[0]);
                if(DEBUG) imshow("Hue-Filtered", channels[0]);
        }
        if(sMin != 0 || sMax != 255)
        {
		satAltered = true;
//                if(DEBUGPRE) imshow("Saturation-Unfiltered", channels[1]);
                inRange(channels[1], Scalar(sMin), Scalar(sMax), channels[1]);
                if(DEBUG) imshow("Saturation-Filtered", channels[1]);
		if(hueAltered && bitAnd)
		{
			bitwise_and(channels[0], channels[1], channels[0]);
			channels[1] = channels[0].clone();
		}
        }
        if(vMin != 0 || vMax != 255)
        {
		valAltered = true;
//               if(DEBUGPRE) imshow("Value-Unfiltered", channels[2]);
                inRange(channels[2], Scalar(vMin), Scalar(vMax), channels[2]);
                if(DEBUG) imshow("Value-Filtered", channels[2]);
        }
	if(bitAnd)
	{
		if(hueAltered && valAltered && satAltered) //Sat, Value, Hue
		{
			bitwise_and(channels[0], channels[1], channels[0]);
			bitwise_and(channels[0], channels[2], channels[0]);
			channels[1] = channels[0].clone();
			channels[2] = channels[0].clone();
		}
		else if(valAltered && hueAltered) //Value, Hue
		{
			bitwise_and(channels[0], channels[2], channels[0]);
			channels[2] = channels[0].clone();
			channels[1] = channels[0].clone();
		}
		else if(hueAltered && satAltered) //Sat, Hue
		{
			bitwise_and(channels[0], channels[1], channels[0]);
			channels[2] = channels[0].clone();
			channels[1] = channels[0].clone();
		}
		else if(satAltered && valAltered) //Sat, Val
		{
			bitwise_and(channels[2], channels[1], channels[1]);
			channels[2] = channels[1].clone();
			channels[0] = channels[1].clone();
		}
		else if(valAltered) //Only Value
		{
			channels[1] = channels[2].clone();
			channels[0] = channels[2].clone();
		}
		else if(satAltered) //Only Sat
		{
			channels[2] = channels[1].clone();
			channels[0] = channels[1].clone();
		}
		else if(hueAltered) //Only Hue
		{
			channels[1] = channels[0].clone();
			channels[2] = channels[0].clone();
		}
	}
	merge(channels, 3, in);
//	delete[] channels;
	cvtColor(in, in, CV_HSV2BGR);
	return in;
}

Mat dilateErode(Mat in, int holes, int noise, Mat element)
{
	dilate(in, in, element, Point(-1, -1), holes);
	erode(in, in, element, Point(-1, -1), holes+noise); //Can use cv::Mat() instead of element for the kernel matrix being used as the third argument 
	dilate(in, in, element, Point(-1, -1), noise);
	return in;
}

Mat edgeDetect(Mat image, Mat * channels, int edge_ksize, int threshLow, int threshHigh)
{
	split(image, channels);
	Canny(image, channels[1], threshLow, threshHigh);
		channels[0] = channels[1];
		channels[2] = channels[0];	
	merge(channels, 3, image);
	return image;
}

Mat sharpen(Mat image, Mat * channels, int ddepth, int sharpen_ksize, int scale, int delta)
{
	Mat image_gray, dst, abs_dst;

	cvtColor(image, image_gray, COLOR_RGB2GRAY); // HSV to grayscale
  	Laplacian(image_gray, dst, ddepth, sharpen_ksize, scale, delta, BORDER_DEFAULT);
  	convertScaleAbs(dst, abs_dst);
  		channels[0] = abs_dst;
		channels[1] = abs_dst;
		channels[2] = abs_dst;
	merge(channels, 3, abs_dst);
	addWeighted(image, 1, abs_dst, 2, 0, image); 
	return image;
}

Mat houghLines(Mat in, int rho, int theta, int threshold, int lineMin, int maxGap)
{
	Mat writing;
	
	writing = in.clone();
	vector<Vec4i> lines;
	Canny(in, in, 50, 200, 3); // apparently this is needed to make the next line work - Min Hoo 2/28/15
	HoughLinesP(in, lines, rho+1, CV_PI/theta, threshold+1, lineMin+1, maxGap+1 ); // something wrong with this line - Min Hoo 2/28/15
	for( size_t i = 0; i < lines.size(); i++ )
	{
		Vec4i l = lines[i];
		line(writing, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
	}
	return writing;
}

int main()
{
	// named windows
	namedWindow("HSV Filtered Image", WINDOW_AUTOSIZE);
	namedWindow("Dilate and Erode", WINDOW_AUTOSIZE);
	namedWindow("Hough Lines", WINDOW_AUTOSIZE);	
	namedWindow("Blur Image", WINDOW_AUTOSIZE);
	namedWindow("Edge Image", WINDOW_AUTOSIZE);
	namedWindow("Sharpen Image", WINDOW_AUTOSIZE);

	// gaussianBlur parameters
	int blur_ksize = 1;
	int sigmaX = 0;
	int sigmaY = 0;
	createTrackbar("Kernel Size", "Blur Image", &blur_ksize, 10);
	createTrackbar("Sigma X", "Blur Image", &sigmaX, 100);
	createTrackbar("Sigma Y", "Blur Image", &sigmaY, 100);

	// colorTest parameters
	int hMin = 0;
	int hMax = 255;
	int sMin = 0;
	int sMax = 255;
	int vMin = 0;
	int vMax = 255;
	int debugMode = 0; //0 is none, 1 is debug, 2 is debug and debugpre	
	createTrackbar("Hue Min", "HSV Filtered Image", &hMin, 255);
	createTrackbar("Hue Max", "HSV Filtered Image", &hMax, 255);
	createTrackbar("Sat Min", "HSV Filtered Image", &sMin, 255);
	createTrackbar("Sat Max", "HSV Filtered Image", &sMax, 255);
	createTrackbar("Val Min", "HSV Filtered Image", &vMin, 255);
	createTrackbar("Val Max", "HSV Filtered Image", &vMax, 255);
	createTrackbar("Debug Mode", "HSV Filtered Image", &debugMode, 2);
	
	// erodeDilateTest parameters
	int holes = 1;
	int noise = 1;
	int size = 1;
	cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS,
                      cv::Size(2 * size + 1, 2 * size + 1), 
                      cv::Point(size, size) );
	createTrackbar("Noise Iterations", "Dilate and Erode", &noise, 15);
	createTrackbar("Filter Size", "Dilate and Erode", &size, 10);
	createTrackbar("Hole Iterations", "Dilate and Erode", &holes, 15);
	
	// edgeDetect parameters
	int threshLow = 0;
	int threshHigh = 255;
	int edge_ksize = 1;
	createTrackbar("Kernel Size", "Edge Image", &edge_ksize, 10);
	createTrackbar("Bottom Threshold", "Edge Image", &threshLow, 255);
	createTrackbar("Upper Threshold", "Edge Image", &threshHigh, 255);
	
	// sharpen parameters
	int sharpen_ksize = 1;
	int scale = 0; // optional scale value added to image
	int delta = 0; // optional delta value added to image
	int ddepth = CV_16S;
	createTrackbar("Kernel Size", "Sharpen Image", &sharpen_ksize, 9);
	createTrackbar("Scale", "Sharpen Image", &scale, 9);
	createTrackbar("Delta", "Sharpen Image", &delta, 9);

	// houghLine parameters
	int rho = 1;
	int theta = 180;
	int threshold = 49;
	int lineMin = 9;
	int maxGap = 49;
	createTrackbar("Theta", "Hough Lines", &theta, 180);
	createTrackbar("Rho", "Hough Lines", &rho, 99);
	createTrackbar("Threshold", "Hough Lines", &threshold, 199);
	createTrackbar("LineMin", "Hough Lines", &lineMin, 399);
	createTrackbar("MaxGap", "Hough Lines", &maxGap, 399);

	// video feed
	VideoCapture camera(0);
	Mat image;
	Mat orig;
	if(!camera.isOpened())
	{
		std::cout<<"Unable to open Camera\n";
		return -1;
	}

	char kill = ' ';
	
	while(kill != 's' && kill != 'q')
	{
		camera>>image;
		orig = image.clone();
		Mat * channels = new Mat[3];
		imshow("Original", image);
		image = gaussianBlur(image, blur_ksize, sigmaX, sigmaY);
		imshow("Blur Filtered", image);
		image = colorFilter(image, hMin, hMax, sMin, sMax, vMin, vMax, debugMode>0, debugMode>1);
		imshow("HSV Filtered", image);
		image = dilateErode(image, holes, noise, element);
		imshow("Dilate and Erode Filtered", image);
		image = edgeDetect(image, channels, edge_ksize, threshLow, threshHigh);
		imshow("Edge Detection", image);
		image = sharpen(image, channels, ddepth, sharpen_ksize, scale, delta);
		imshow("Sharpen", image);
		image = houghLines(image, rho, theta, threshold, lineMin, maxGap);
		imshow("All Filtered", image);

		addWeighted(image, 1, orig, 1, 3, image);
		imshow("Final Product", image);
		delete [] channels;
		kill = waitKey(5);

		
	}
	return 0;
}

