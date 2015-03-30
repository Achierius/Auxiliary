#ifndef DILATEERODE
#define DILATEERODE

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat dilateErode(Mat in, int holes, int noise, Mat element);

#endif
