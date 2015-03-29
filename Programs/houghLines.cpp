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

