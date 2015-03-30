#ifndef HOUGHLINES
#define HOUGHLINES

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat houghLines(Mat in, int rho, int theta, int threshold, int lineMin, int maxGap);

#endif
