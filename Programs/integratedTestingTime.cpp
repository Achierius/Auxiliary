Mat gaussianBlur(Mat in, int blur_ksize, int sigmaX, int sigmaY) 
{
	if ((blur_ksize%2 != 1) && (blur_ksize > 1)) // kernel size must be odd and positive
		blur_ksize = blur_ksize*2+1;
	GaussianBlur(in, in, Size(blur_ksize, blur_ksize), sigmaX, sigmaY, BORDER_DEFAULT);
	return in;
}

Mat colorFilter(Mat in, int hMin = 20, int hMax = 60, int sMin = 60, int sMax = 140, int vMin = 190, int vMax = 255,  bool DEBUG = false, bool DEBUGPRE = false, bool bitAnd = true)
{
 
        bool hueAltered = false;
	bool satAltered = false;
	bool valAltered = false;

//	if(DEBUG) imshow("PreFiltered", in);
        cvtColor(in, in, CV_BGR2HSV);
        Mat * channels = new Mat [3];
        split(in, channels);

        if(hMin != 0 || hMax != 255)
        {
		hueAltered = true;
//                if(DEBUGPRE) imshow("Hue-Unfiltered", channels[0]);
                inRange(channels[0], Scalar(hMin), Scalar(hMax), channels[0]);
                if(DEBUG) imshow("Hue-Filtered", channels[0]);
        }
        if(sMin != 0 || sMax != 255)
        {
		satAltered = true;
//                if(DEBUGPRE) imshow("Saturation-Unfiltered", channels[1]);
                inRange(channels[1], Scalar(sMin), Scalar(sMax), channels[1]);
                if(DEBUG) imshow("Saturation-Filtered", channels[1]);
		if(hueAltered && bitAnd)
		{
			bitwise_and(channels[0], channels[1], channels[0]);
			channels[1] = channels[0].clone();
		}
        }
        if(vMin != 0 || vMax != 255)
        {
		valAltered = true;
//               if(DEBUGPRE) imshow("Value-Unfiltered", channels[2]);
                inRange(channels[2], Scalar(vMin), Scalar(vMax), channels[2]);
                if(DEBUG) imshow("Value-Filtered", channels[2]);
        }
	if(bitAnd)
	{
		if(hueAltered && valAltered && satAltered) //Sat, Value, Hue
		{
			bitwise_and(channels[0], channels[1], channels[0]);
			bitwise_and(channels[0], channels[2], channels[0]);
			channels[1] = channels[0].clone();
			channels[2] = channels[0].clone();
		}
		else if(valAltered && hueAltered) //Value, Hue
		{
			bitwise_and(channels[0], channels[2], channels[0]);
			channels[2] = channels[0].clone();
			channels[1] = channels[0].clone();
		}
		else if(hueAltered && satAltered) //Sat, Hue
		{
			bitwise_and(channels[0], channels[1], channels[0]);
			channels[2] = channels[0].clone();
			channels[1] = channels[0].clone();
		}
		else if(satAltered && valAltered) //Sat, Val
		{
			bitwise_and(channels[2], channels[1], channels[1]);
			channels[2] = channels[1].clone();
			channels[0] = channels[1].clone();
		}
		else if(valAltered) //Only Value
		{
			channels[1] = channels[2].clone();
			channels[0] = channels[2].clone();
		}
		else if(satAltered) //Only Sat
		{
			channels[2] = channels[1].clone();
			channels[0] = channels[1].clone();
		}
		else if(hueAltered) //Only Hue
		{
			channels[1] = channels[0].clone();
			channels[2] = channels[0].clone();
		}
	}
	merge(channels, 3, in);
//	delete[] channels;
	cvtColor(in, in, CV_HSV2BGR);
	return in;
}

Mat edgeDetect(Mat image, Mat * channels, int edge_ksize, int threshLow, int threshHigh)
{
	split(image, channels);
	Canny(image, channels[1], threshLow, threshHigh);
		channels[0] = channels[1];
		channels[2] = channels[0];	
	merge(channels, 3, image);
	return image;
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

int main()
{
	// other debug stuff
	bool  blur, color, dilate_erode, edge, sharpen, hough = true; // ability to do efficient code
/*	namedWindow("Efficiency Editor", WINDOW_AUTOSIZE);
	createTrackbar("Blur Filter", "Efficiency Editor", &blur, 1);
	createTrackbar("Color Filter", "Efficiency Editor", &color, 1);
	createTrackbar("Edge Filter", "Efficiency Editor", &edge, 1);
	createTrackbar("Hough Line Filter", "Efficiency Editor", &hough, 1);

	namedWindow("Blur Editor", WINDOW_AUTOSIZE);
	namedWindow("Color Filter Editor", WINDOW_AUTOSIZE);
	namedWindow("Edge Editor", WINDOW_AUTOSIZE);
	namedWindow("Hough Lines Editor", WINDOW_AUTOSIZE);	
	namedWindow("AddWeighted Editor", WINDOW_AUTOSIZE);

	// doesn't work because program is simply passing by; need to put in while loop or something -Min Hoo 3/2/15
	if (blur == 1) 
		namedWindow("Blur Editor", WINDOW_AUTOSIZE);
	if (color == true) 
		namedWindow("Color Filter Editor", WINDOW_AUTOSIZE);
	if (edge == true)
		namedWindow("Edge Editor", WINDOW_AUTOSIZE);
	if (hough == true)
		namedWindow("Hough Lines Editor", WINDOW_AUTOSIZE);	

	// gaussianBlur parameters
	int blur_ksize = 1;
	int sigmaX = 0;
	int sigmaY = 0;
	createTrackbar("Kernel Size", "Blur Editor", &blur_ksize, 10);
	createTrackbar("Sigma X", "Blur Editor", &sigmaX, 100);
	createTrackbar("Sigma Y", "Blur Editor", &sigmaY, 100);

	// colorTest parameters
	int hMin = 0;
	int hMax = 255;
	int sMin = 0;
	int sMax = 255;
	int vMin = 0;
	int vMax = 255;
*/	int debugMode = 0; //0 is none, 1 is debug, 2 is debug and debugpre	
/*	createTrackbar("Hue Min", "Color Filter Editor", &hMin, 255);
	createTrackbar("Hue Max", "Color Filter Editor", &hMax, 255);
	createTrackbar("Sat Min", "Color Filter Editor", &sMin, 255);
	createTrackbar("Sat Max", "Color Filter Editor", &sMax, 255);
	createTrackbar("Val Min", "Color Filter Editor", &vMin, 255);
	createTrackbar("Val Max", "Color Filter Editor", &vMax, 255);
	createTrackbar("Debug Mode", "Color Filter Editor", &debugMode, 2);
	
	// edgeDetect parameters
	int threshLow = 0;
	int threshHigh = 255;
	int edge_ksize = 1;
	createTrackbar("Kernel Size", "Edge Editor", &edge_ksize, 7);
	createTrackbar("Bottom Threshold", "Edge Editor", &threshLow, 255);
	createTrackbar("Upper Threshold", "Edge Editor", &threshHigh, 255);
	
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
*/
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
/*	createTrackbar("Filtered", "AddWeighted Editor", &weight1);
	createTrackbar("Original", "AddWeighted Editor", &weight2);
*/
	char kill = ' ';
	long time1 = 0;
	long time2 = 0;
	long timeTaken = 0;

//	typedef duration <int, std::ratio<60*60*24>> days_type;
//	time_point<system_clock,days_type> today = time_point_cast<days_type>(system_clock::now());

	system_clock::time_point tp_epoch;
	time_point<system_clock,duration<int>> tp_seconds (duration<int>(1));
	system_clock::time_point tp (tp_seconds);
	
	while(kill != 's' && kill != 'q')
	{
		camera>>image;
		orig = image.clone();
		Mat * channels = new Mat[3];
		time1 = tp.time_since_epoch().count();

		image = gaussianBlur(image, 5, 10, 10);
//		imshow("Blur Output", image);
		image = colorFilter(image, 20, 60, 60, 190, 140, 255, debugMode>0, debugMode>1);
//		imshow("Color Filter Output", image);
		image = edgeDetect(image, channels, 5, 0, 255);
//		imshow("Edge Detection Output", image);
		image = houghLines(image, 1, 180, 49, 9, 49);
//		imshow("Hough Lines Output", image);		
//		imshow("All Filtered", image);
		addWeighted(image, weight1, orig, weight2, 3, image);
		imshow("Final Weighted Average", image);
//		imshow("Original", orig);
		
		time2 = tp.time_since_epoch().count();
		timeTaken = time2 - time1;
		cout<<timeTaken;
		
		delete [] channels;
		kill = waitKey(5);
		
	}
	return 0;
}

