#ifndef INTEGRATEDTESTINGTIME
#define INTEGRATEDTESTINGTIME

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <ctime>
#include <cmath>

#include <chrono>
#include <ratio>
#include <iostream>

using namespace cv;
using namespace std;
using namespace std::chrono;

Mat gaussianBlur(Mat in, int blur_ksize, int sigmaX, int sigmaY); 

Mat colorFilter(Mat in, int hMin, int hMax, int sMin, int sMax, int vMin, int vMax, bool DEBUG = false, bool DEBUGPRE = false, bool bitAnd = true);

Mat edgeDetect(Mat image, Mat * channels, int edge_ksize, int threshLow, int threshHigh);

Mat houghLines(Mat in, int rho, int theta, int threshold, int lineMin, int maxGap);

#endif
