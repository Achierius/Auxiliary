#ifndef GAUSSIANBLUR
#define GAUSSIANBLUR

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

cv::Mat gaussianBlur(Mat in, int blur_ksize, int sigmaX, int sigmaY); 

#endif
