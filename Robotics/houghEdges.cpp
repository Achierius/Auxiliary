#include "houghCorners.h"


double dist(double x1, double y1, double x2, int y2)
{
	return hypot ( (x1-x2) , (y1-y2) );
}

vector<pair<int, int> > corners(vector<Vec4i> in, Mat image)
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