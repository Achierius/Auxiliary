#ifndef COLORFILTER
#define COLORFILTER

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

cv::Mat roboColorFilter(Mat in, int hMin = 0, int hMax = 255, int sMin = 0, int sMax = 255, int vMin = 0, int vMax = 255, bool DEBUG = false, bool DEBUGPRE = false, bool bitAnd = true);

#endif
