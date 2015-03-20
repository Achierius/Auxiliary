#include "opencv3/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

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

Mat distance() {
	
}

int main()
{
	// distance() parameters
	public final int RATIO = n; // idk where to put fields
	
	int x;
	int y;

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
		camera>>image;
		orig = image.clone();
		Mat * channels = new Mat[3];
		image = houghLines(image, rho, theta, threshold, lineMin, maxGap);
		imshow("All Filtered", image);
		image = distance(x, y);
		addWeighted(image, weight1, orig, weight2, 3, image);
		imshow("Final Weighted Average", image);
//		imshow("Original", orig);
		delete [] channels;
		kill = waitKey(5);
	}
	return 0;
}

