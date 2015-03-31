#include "RoboGaussianBlur.h";

cv::Mat roboGaussianBlur(cv::Mat in, int blur_ksize, int sigmaX, int sigmaY) 
{
	if ((blur_ksize%2 != 1) && (blur_ksize > 1)) // kernel size must be odd and positive
		blur_ksize = blur_ksize*2+1;
	cv::GaussianBlur(in, in, Size(blur_ksize, blur_ksize), sigmaX, sigmaY, BORDER_DEFAULT);
	return in;
}
