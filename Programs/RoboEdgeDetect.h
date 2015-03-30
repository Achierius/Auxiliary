#ifndef EDGEDETECT
#define EDGEDETECT

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat edgeDetect(Mat image, Mat * channels, int edge_ksize, int threshLow, int threshHigh);

#endif
