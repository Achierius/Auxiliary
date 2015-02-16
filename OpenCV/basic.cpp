#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat image;
	VideoCapture cap(0);
	if(!cap.isOpened())
	{
		std::cout<<"Could not open camera\n";
	}
	namedWindow("Window", WINDOW_AUTOSIZE);
	while(true)
	{
		cap>>image;
		imshow("Window", image);
		waitKey(1);
	}
	return 0;
}
