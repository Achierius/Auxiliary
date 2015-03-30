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
		Mat * channels = new Mat [3];
		cvtColor(src, src, CV_BGR2HSV);
		GaussianBlur(src, src, cvSize(7,7), 1);
		split(src, channels);
		inRange(channels[0], Scalar(15), Scalar(45), channels[0]);
		inRange(channels[1], Scalar(123), Scalar(255), channels[1]);
		imshow("posthue", channels[0]);
		imshow("postsat", channels[1]);
		bitwise_and(channels[0], channels[1], channels[0]);
		channels[1] = channels[0];
		channels[2] = channels[0];
		merge(channels, 3, src);
		cvtColor(src, src, CV_HSV2BGR);
		Canny(src, dst, 50, 200, 3);
		//cvtColor(dst, cdst, COLOR_GRAY2BGR);
		vector<Vec4i> lines;
		HoughLinesP(dst, lines, 1, CV_PI/90, 50, 50, 10 );
		for( size_t i = 0; i < lines.size(); i++ )
		{
			Vec4i l = lines[i];
			//line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3);
			line( src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3);
		}
		imshow("source", src);
		imshow("detected lines", cdst);
		delete[] channels;
		waitKey(1);
	}
	return 0;
}
