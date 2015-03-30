Mat colorFilter(Mat in, int hMin = 0, int hMax = 255, int sMin = 0, int sMax = 255, int vMin = 0, int vMax = 255, bool DEBUG = false, bool DEBUGPRE = false, int primary = 0)
{
	if(DEBUG) imshow("PreFiltered", in);
	cvtColor(in, in, CV_BGR2HSV);
	Mat * channels = new Mat [3];
	split(in, channels);
	if(hMin != 0 || hMax != 255)
	{
		if(DEBUGPRE) imshow("Hue-Unfiltered", channels[0]);
		inRange(channels[0], Scalar(hMin), Scalar(hMax), channels[0]);
		if(DEBUG) imshow("Hue-Filtered", channels[0]);
	}
	if(sMin != 0 || sMax != 255)
	{
		if(DEBUGPRE) imshow("Saturation-Unfiltered", channels[1]);
		inRange(channels[1], Scalar(sMin), Scalar(sMax), channels[1]);
		if(DEBUG) imshow("Saturation-Filtered", channels[1]);
	}
	if(vMin != 0 || vMax != 255)
	{
		if(DEBUGPRE) imshow("Value-Unfiltered", channels[2]);
		inRange(channels[2], Scalar(vMin), Scalar(vMax), channels[2]);
		if(DEBUG) imshow("Value-Filtered", channels[2]);
	}


	/*if((hMin != 0 || hMax != 255) && (sMin != 0 || sMin != 255))
	{
		bitwise_and(channels[0], channels[1], channels[0]);
		channels[1] = channels[0];
		
	} 
	if((hMin != 0 || hMax != 255) && (vMin != 0 || vMin != 255))
	{
		bitwise_and(channels[0], channels[2], channels[0]);
		channels[2] = channels[0];
	}
	if((vMin != 0 || vMax != 255) && (sMin != 0 || sMin != 255))
	{
		bitwise_and(channels[2], channels[1], channels[2]);
		channels[1] = channels[2];
	}*/
	
	bitwise_and(channels[0], channels[1], channels[0]);
	channels[2] = channels[0].clone();
	
	merge(channels, 3, in);
	cvtColor(in, in, CV_HSV2BGR);
	delete[] channels;
	return in;
}
Mat binaryAnd(int channel1, int channel2, Mat image, bool fill = false) //Not working?
{
	Mat * channels = new Mat [3];
	split(image, channels);
	bitwise_and(channels[channel1], channels[channel2], channels[channel1]);
	channels[channel2] = channels[channel1].clone();
	for(int i = 0; fill == true && i < image.channels(); i++)
	{
		channels[i] = channels[channel1].clone();
	}
	merge(channels, 3, image);
	imshow("binaryand", image);
	delete[] channels;
	return image;
}
int main(int argc, char** argv)
{
	int erosion_size = 1;
	VideoCapture camera(0);
	Mat pre;
	Mat image;
	Mat src;
	int lineMin= 50;
	int threshold = 50;
	int maxGap = 10;
	int blurSize = 7;
	namedWindow("Window", WINDOW_AUTOSIZE);
	namedWindow("Image", WINDOW_AUTOSIZE);
	namedWindow("Blurred", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "Window", &threshold, 199);
	createTrackbar("LineMin", "Window", &lineMin, 399);
	createTrackbar("MaxGap", "Window", &maxGap, 399);
	createTrackbar("BlurSize", "Blurred", &blurSize, 19);
	createTrackbar("Erosion", "Image", &erosion_size, 6);
	while(true)
	{
		camera>>src;
		pre = src.clone();
		pre = colorFilter(pre, 19, 31, 170, 255, 0, 255, true);
		//binaryAnd(0, 1, pre, true);
		imshow("img", pre);
		Mat element = getStructuringElement( MORPH_RECT, Size( 2*(1+erosion_size), 2*(1+erosion_size) ), Point( erosion_size+1, erosion_size+1 ) );
		cout<<enumCvType(image)<<"\n";
		dilate(pre, pre, element);
		dilate(pre, pre, element);
		dilate(pre, pre, element);
		imshow("dilated", pre);
		erode(pre, pre, element);
		erode(pre, pre, element);
		erode(pre, pre, element);
		imshow("Image", pre);
		blur(pre, pre, cvSize(blurSize+1, blurSize+1));
		imshow("Blurred", pre);
		Canny(pre, image, 75, 225, 3);
		vector<Vec4i> lines;
		//imshow("Image", image);
		cout<<enumCvType(image)<<"\n";
		HoughLinesP(image, lines, 1, CV_PI/180, threshold+1, lineMin+1, maxGap+1 );
		for( size_t i = 0; i < lines.size(); i++ )
		{
			Vec4i l = lines[i];
			line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
		}
		imshow("Window", src);
		waitKey(5);
	}
	return 0;
}	
