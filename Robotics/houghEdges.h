#include "opencv2/highgui/highgui.hpp"
#include <typeinfo>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cmath>
#include <iostream>

using namespace std;
using namespace cv;

double dist(double x1, double y1, double x2, int y2);

vector<pair<int, int> > corners(vector<Vec4i> in, Mat image);
