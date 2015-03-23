#include "opencv2/highgui/highgui.hpp"
#include <typeinfo>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cmath>
#include <iostream>

using namespace cv;
using namespace std;

double dist(double x1, double y1, double x2, int y2)
{
	return hypot ( (x1-x2) , (y1-y2) );
}

Mat houghLines(Mat in, int rho, int theta, int threshold, int lineMin, int maxGap)
{
	Mat writing;
	
	writing = in.clone();
	vector<Vec4i> lines;
	Canny(in, in, 50, 200, 3); // apparently this is needed to make the next line work - Min Hoo 2/28/15
	HoughLinesP(in, lines, rho+1, CV_PI/theta, threshold+1, lineMin+1, maxGap+1 ); // something wrong with this line - Min Hoo 2/28/15
	for( size_t i = 0; i < lines.size(); i++ )
	{
		Vec4i l = lines[i];
		line(writing, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
	}
	return writing;
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
			curMax = dist(0, 0, cur[0], cur[1]);
		}
		if(dist(0, 0, cur[2], cur[3]) < curMax)
		{
			points[0] = make_pair(cur[2], cur[3]);
			curMax = dist(0, 0, cur[2], cur[3]);
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
			curMax = dist(image.cols, 0, cur[0], cur[1]);
		}
		if(dist(image.cols, 0, cur[2], cur[3]) < curMax)
		{
			points[1] = make_pair(cur[2], cur[3]);
			curMax = dist(image.cols, 0, cur[2], cur[3]);
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
			curMax = dist(0, image.rows, cur[0], cur[1]);
		}
		if(dist(0, image.rows, cur[2], cur[3]) < curMax)
		{
			points[2] = make_pair(cur[2], cur[3]);
			curMax = dist(0, image.rows, cur[2], cur[3]);
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
				curMax = dist(image.cols, image.cols, cur[0], cur[1]);
			}
			if(dist(image.cols, image.rows, cur[2], cur[3]) < curMax)
			{
				points[3] = make_pair(cur[2], cur[3]);
				curMax = dist(image.cols, image.rows, cur[2], cur[3]);	
			}
		}
	}
	return points;
}
}

int main()
{
	// distance() parameters
	public final int RATIO = n; // idk where to put fields
	
	double width = 0;
	double height = 0;

	// houghLine parameters
	int rho = 1;
	int theta = 180;
	int threshold = 49;
	int lineMin = 9;
	int maxGap = 49;
	createTrackbar("Theta", "Hough Lines Editor", &theta, 180);
	createTrackbar("Rho", "Hough Lines Editor", &rho, 99);
	createTrackbar("Threshold", "Hough Lines Editor", &threshold, 199);
	createTrackbar("LineMin", "Hough Lines Editor", &lineMin, 399);
	createTrackbar("MaxGap", "Hough Lines Editor", &maxGap, 399);

	// video feed
	VideoCapture camera(0);
	Mat image;
	Mat orig;
	if(!camera.isOpened())
	{
		std::cout<<"Unable to open Camera\n";
		return -1;
	}

	// decide weighted sums of image and filtered image
	int weight1 = 1;
	int weight2 = 1;

	char kill = ' ';
	
	while(kill != 's' && kill != 'q')
	{
		vector<Vec4i> lines;
		camera>>image;
		orig = image.clone();
		Mat * channels = new Mat[3];
		image = houghLines(image, rho, theta, threshold, lineMin, maxGap);
		imshow("Hough Lines", image);
//		HoughLinesP(image, lines, rho, CV_PI/theta, threshold+1, lineMin+1, maxGap+1 );
		for( int i = 0; i < lines.size(); i++ )
		{
			Vec4i l = lines[i];
			line(writing, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
			cout<<"Line "<<i<<": ("<<l[0]<<","<<l[1]<<") by ("<<l[2]<<","<<l[3]<<")\n"; 
		}
		vector< pair<int, int> > cornerPoints = corners(lines, image);
		for( size_t i = 0; i < 4; i++)
		{
			circle(writing, Point(cornerPoints[i].first, cornerPoints[i].second), 10, Scalar(175, 150, 150));
	
		for(int i = 0; i < 4; i++)
		{
			cout<<"Point "<<i<<": ("<<cornerPoints[i].first<<","<<cornerPoints[i].second<<")\n";
		}
		cout<<"\n \n \n \n";
		imshow("Window", writing);
		
		width = dist(cornerPoints[0].first, cornerPoints[0].second, cornerPoints[1], cornerPoints[1]);	
		height = dist(cornerPoints[2].first, cornerPoints[2].second, cornerPoints[3], cornerPoints[3]);	
		if ((width/height) == RATIO) {
			cout<<"Object is can"; 
		}
		addWeighted(image, weight1, orig, weight2, 3, image);
		imshow("Final Weighted Average", image);
//		imshow("Original", orig);
		delete [] channels;
		kill = waitKey(5);
	}
	return 0;
}

