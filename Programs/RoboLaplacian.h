#ifndef LAPACIAN
#define LAPACIAN 

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

cv::Mat laplacian(Mat image, Mat * channels, int ddepth, int sharpen_ksize, int scale, int delta);

#endif
