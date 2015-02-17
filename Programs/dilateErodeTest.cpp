#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace std;
using namespace cv;

Mat dilateErode(Mat in, int holes, int noise, Mat element);

Mat dilateErode(Mat in, int holes, int noise, Mat element)
{
	dilate(in, in, element, Point(-1, -1), holes);
	erode(in, in, element, Point(-1, -1), holes+noise); //Can use cv::Mat() instead of element for the kernel matrix being used as the third argument 
	dilate(in, in, element, Point(-1, -1), noise);
	return in;
}

int main()
{
	VideoCapture camera(0);
        Mat image;
        namedWindow("Filtered Image", WINDOW_AUTOSIZE);
        if(!camera.isOpened())
        {
                std::cout<<"Unable to open Camera\n";
                return -1;
        }
	int holes = 1;
	int noise = 1;
	int size = 1;
	cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS,
                      cv::Size(2 * size + 1, 2 * size + 1), 
                      cv::Point(size, size) );
	createTrackbar("Noise Iterations", "Filtered Image", &noise, 15);
	createTrackbar("Filter Size", "Filtered Image", &size, 10);
	createTrackbar("Hole Iterations", "Filtered Image", &holes, 15);
	while(true)
	{
		camera>>image;
		image = dilateErode(image, holes, noise, element);
		imshow("Filtered Image", image);
		waitKey(5);
	}
}

