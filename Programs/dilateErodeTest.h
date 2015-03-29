#ifndef DILATEERODETEST
#define DILATEERODETEST

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace std;
using namespace cv;

Mat dilateErode(Mat in, int holes, int noise, Mat element);

#endif
