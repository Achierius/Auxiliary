#include "RoboEdgeDetect.h";

cv::Mat roboEdgeDetect(cv::Mat image, cv::Mat * channels, int edge_ksize, int threshLow, int threshHigh)
{
	cv::split(image, channels);
	cv::Canny(image, channels[1], threshLow, threshHigh);
		channels[0] = channels[1];
		channels[2] = channels[0];	
	cv::merge(channels, 3, image);
	return image;
}
