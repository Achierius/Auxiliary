#ifndef LAPACIAN
#define LAPACIAN 

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat laplacian(Mat image, Mat * channels, int ddepth, int sharpen_ksize, int scale, int delta);

#endif
