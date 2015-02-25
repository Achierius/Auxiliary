#include "opencv2/highgui/highgui.hpp"
#include <typeinfo>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "enumCvType.h"
#include <cmath>
#include <iostream>

using namespace cv;
using namespace std;
int dist(int x1, int y1, int x2, int y2)
{
	return sqrt(((x1-x2)^2 + (y1-y2)^2));
}

vector<pair<int, int> > corners(vector<Vec4i> in, Mat image) //Topleft, Topright, botleft, botright
{
	int curMax = image.rows+image.cols;
	vector<pair<int, int> > points;
	
	for(int i = 0; i < 4; i++)
	{
		pair<int, int> pointu ;
		pointu.first = 0;
		pointu.second = 0;
		points.push_back(pointu);
	}
	for(size_t i = 0; i < in.size(); i++) //Topleft
	{
		Vec4i cur  = in[i];
		
		if(cur[1] == 0 || cur[0] == 0 || cur[2] == 0 || cur[3] == 0)
		{
			continue; //This is detecting an edge as a line, ignore it	
	}
		
		if(dist(0, 0, cur[0], cur[1]) < curMax)
		{
			points[0] = make_pair(cur[0], cur[1]);
		}
		if(dist(0, 0, cur[2], cur[3]) < curMax)
		{
			points[0] = make_pair(cur[2], cur[3]);
		}
	}
	curMax = image.rows+image.cols;
	for(size_t i = 0; i < in.size(); i++) //Topright
	{
		Vec4i cur  = in[i];
		
		if(cur[1] == 0 || cur[0] == 0 || cur[2] == 0 || cur[3] == 0)
		{
			continue; //This is detecting an edge as a line, ignore it	
		}
		
		if(dist(image.cols, 0, cur[0], cur[1]) < curMax)
		{
			points[1] = make_pair(cur[0], cur[1]);
		}
		if(dist(image.cols, 0, cur[2], cur[3]) < curMax)
		{
			points[1] = make_pair(cur[2], cur[3]);
		}
	}
	curMax = image.rows+image.cols;
	for(size_t i = 0; i < in.size(); i++) //Bottomleft
	{
		Vec4i cur  = in[i];
		
		if(cur[1] == 0 || cur[0] == 0 || cur[2] == 0|| cur[3] == 0)
		{
			continue; //This is detecting an edge as a line, ignore it	
		}
			
		if(dist(0, image.rows, cur[0], cur[1]) < curMax)
		{
			points[2] = make_pair(cur[0], cur[1]);
		}
		if(dist(0, image.rows, cur[2], cur[3]) < curMax)
		{
			points[2] = make_pair(cur[2], cur[3]);
		}
	}
	curMax = image.rows+image.cols;
	for(size_t i = 0; i < in.size(); i++) //Bottomright
	{
		Vec4i cur  = in[i];
		if(!(cur[1] == 0 || cur[0] == 0 || cur[2] == 0 || cur[3] == 0))
		{
			if(dist(image.cols, image.rows, cur[0], cur[1]) < curMax)
			{
				points[3] = make_pair(cur[0], cur[1]);
			}
			if(dist(image.cols, image.rows, cur[2], cur[3]) < curMax)
			{
				points[3] = make_pair(cur[2], cur[3]);
			}
		}
	}
	return points;
}
int main(int argc, char** argv)
{
	VideoCapture camera(0);
	Mat pre;
	Mat image;
	Mat writing;
	namedWindow("Window", WINDOW_AUTOSIZE);
	namedWindow("Image", WINDOW_AUTOSIZE);
	writing = imread("FedExSide.jpeg");
	pre = imread("FilteredToteEdges.jpeg");
	int rho = 1;
	int theta = 180;
	int threshold = 49;
	int lineMin = 9;
	int maxGap = 49;
	createTrackbar("Theta", "Window", &theta, 180);
	createTrackbar("Rho", "Window", &rho, 100);
	createTrackbar("Threshold", "Window", &threshold, 199);
	createTrackbar("LineMin", "Window", &lineMin, 399);
	createTrackbar("MaxGap", "Window", &maxGap, 399);
	while(true)
	{
		//camera>>pre;
		//imwrite("FedExSide.jpeg", pre);
		//waitKey(0);
		writing = imread("FilteredTote.jpeg");
		Canny(pre, image, 50, 200, 3);
		vector<Vec4i> lines;
		//imshow("Image", image);
		cout<<enumCvType(image)<<"\n";
		HoughLinesP(image, lines, rho, CV_PI/theta, threshold+1, lineMin+1, maxGap+1 );
		for( size_t i = 0; i < lines.size(); i++ )
		{
			Vec4i l = lines[i];
			line(writing, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
			cout<<"Line "<<i<<": ("<<l[0]<<","<<l[1]<<") by ("<<l[2]<<","<<l[3]<<")\n"; 
		}
		vector< pair<int, int> > cornerPoints = corners(lines, image);
		for( size_t i = 0; i < cornerPoints.size(); i++)
		{
			circle(writing, Point(cornerPoints[i].first, cornerPoints[i].second), 10, Scalar(175, 150, 150));
		}
		for(int i = 0; i < 4; i++)
		{
			cout<<"Point "<<i<<": ("<<cornerPoints[i].first<<","<<cornerPoints[i].second<<")\n";
		}
		cout<<"\n \n \n \n";
		imshow("Window", writing);
		waitKey(1);
	}
	return 0;
}	
