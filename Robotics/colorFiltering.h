#ifndef COLORFILTERING
#define COLORFILTERING

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "enumCvType.h"

#include <iostream>

using namespace cv;
using namespace std;

Mat binaryAnd(int channel1, int channel2, Mat image, bool fill = false); //Not working?
Mat colorFilter(Mat in, int hMin = 0, int hMax = 255, int sMin = 0, int sMax = 255, int vMin = 0, int vMax = 255, bool DEBUG = false, bool DEBUGPRE = false, int primary = 0);

#endif
