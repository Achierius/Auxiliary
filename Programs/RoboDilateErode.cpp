#include "RoboDilateErode.h";

cv::Mat roboDilateErode(cv::Mat in, int holes, int noise, cv::Mat element)
{
	cv::dilate(in, in, element, cv::Point(-1, -1), holes);
	cv::erode(in, in, element, cv::Point(-1, -1), holes+noise); //Can use cv::Mat() instead of element for the kernel matrix being used as the third argument 
	cv::dilate(in, in, element, cv::Point(-1, -1), noise);
	return in;
}
