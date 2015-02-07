#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <opencv2/highgui/highgui.hpp>
//#include <boost/lexical_cast.hpp>
//#include <thread>
#include <string>

using namespace cv;
using namespace std;

/*void input(string &buffer)
{
	cin>>buffer;
	while(!(buffer == "end" || buffer == "q" || buffer == "quit" || buffer == "stop"))
	{
		cin>>buffer;
		waitKey(5);
	}
}
void processing()
{
	cout<<"da\n";
}*/
int main(int argc, char* argv[])
{
	namedWindow("VidSrm", CV_WINDOW_AUTOSIZE);
	Mat img;
	VideoCapture cap(0);
	if(!cap.isOpened()){cout<<"Error"; return 0;}

	while(true)
	{
		cap>>img;
//		GaussianBlur(img, img, Size(3, 3), 0, 0);
		imshow("VidSRM", img);
		waitKey(1);
	}
}
