#include "RoboLaplacian.h";

cv::Mat roboLaplacian(cv::Mat image, cv::Mat * channels, int ddepth, int sharpen_ksize, int scale, int delta)
{
	cv::Mat image_gray, dst, abs_dst;

	cv::cvtColor(image, image_gray, COLOR_RGB2GRAY); // HSV to grayscale
  	cv::Laplacian(image_gray, dst, ddepth, sharpen_ksize, scale, delta, BORDER_DEFAULT);
  	cv::convertScaleAbs(dst, abs_dst);
  		channels[0] = abs_dst;
		channels[1] = abs_dst;
		channels[2] = abs_dst;
	cv::merge(channels, 3, abs_dst);
	cv::addWeighted(image, 1, abs_dst, 2, 0, image); 
	return image;
}
