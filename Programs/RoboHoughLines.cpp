#include "RoboHoughLines.cpp";

cv::Mat roboHoughLines(cv::Mat in, int rho, int theta, int threshold, int lineMin, int maxGap)
{
	cv::Mat writing;
	
	writing = in.cv::clone();
	std::vector<Vec4i> lines;
	Canny(in, in, 50, 200, 3); // apparently this is needed to make the next line work - Min Hoo 2/28/15
	HoughLinesP(in, lines, rho+1, cv::CV_PI/theta, threshold+1, lineMin+1, maxGap+1 ); // something wrong with this line - Min Hoo 2/28/15
	for( size_t i = 0; i < lines.size(); i++ )
	{
		Vec4i l = lines[i];
		cv::line(writing, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 3,cv::CV_AA);
	}
	return writing;
}

