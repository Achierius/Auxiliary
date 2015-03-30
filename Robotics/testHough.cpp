int main(int argc, char** argv)
{
	VideoCapture cap(0);
	if(!cap.isOpened())
	{
		cout << "can not open camera\n";
		return -1;
	}
	Mat dst, cdst, src;
	while(true)
	{
		cap>>src;
		Canny(src, dst, 50, 200, 3);
		cvtColor(dst, cdst, COLOR_GRAY2BGR);
		vector<Vec4i> lines;
		HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
		for( size_t i = 0; i < lines.size(); i++ )
		{
			Vec4i l = lines[i];
			line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3);
		}
		imshow("source", src);
		imshow("detected lines", cdst);
		waitKey(1);
	}
	return 0;
}
