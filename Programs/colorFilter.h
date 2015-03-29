#ifndef CFILTER
#define CFILTER

Mat colorFilter(Mat in, int hMin = 0, int hMax = 255, int sMin = 0, int sMax = 255, int vMin = 0, int vMax = 255, bool DEBUG = false, bool DEBUGPRE = false, bool bitAnd = true);

#endif
