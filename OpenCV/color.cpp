#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
// ??? #include <opencv2/improc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <boost/lexical_cast.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat img;
	Mat fil;
	int i;
	VideoCapture cap(0);
        if(!cap.isOpened()){cout<<"Error"; return 0;}
	while(true)
	{	
		try
		{
			cap>>img;

		/*for(MatConstIterator_<VT> it = img.begin<VT>(); it != it_end; ++it)
			{
				
			}*/
			inRange(img, Scalar(150, 0, 0), Scalar(255, 255, 255), fil);
			Mat* channels = new Mat [3];
			split(img, channels);
			cout<<channels[0].rows<<"\n";	
			cout<<"Split:  Channels-"<<channels[0].channels()<<" Depth-"<<channels[0].depth()<<"  Length-"<<channels[0].cols<<"  Height-"<<channels[0].rows<<"\n";
			cout<<"Whole:  Channels-"<<img.channels()<<"  Depth-"<<img.depth()<<"  Length-"<<img.cols<<"  Height-"<<img.rows<<"\n";
			cout<<"Filter:  Channels-"<<fil.channels()<<"  Depth-"<<fil.depth()<<"  Length-"<<fil.cols<<"  Height-"<<fil.rows<<"\n";
			//cvtColor(fil, fil,
			Mat* channels2 = new Mat [3];
			Mat nfil;
			fil.convertTo(fil, CV_32FC1);
			transpose(fil, nfil);
			cout<<"ConvertedFilter:  Channels-"<<fil.channels()<<"  Depth-"<<fil.depth()<<"  Length-"<<fil.cols<<"  Height-"<<fil.rows<<"\n";

			/*for(int i = 0; i < 3; i++)
			{
				channels[i].convertTo(channels[i], CV_32FC1);			
				channels[i] = channels[i]*nfil;
			}*/
			channels[0].convertTo(channels[0], CV_32FC1);
			channels[0] = channels[0]*nfil;
			//channels[0] = fil.clone();
			cout<<"Converted:  Channels-"<<channels[0].channels()<<" Depth-"<<channels[0].depth()<<"  Length-"<<channels[0].cols<<"  Height-"<<channels[0].rows<<"\n";
			cout<<"Modified:  Channels-"<<channels2[0].channels()<<" Depth-"<<channels2[0].depth()<<"\n";
			merge(channels, 3, img);
			//Mat rfil=fil.reshape(3, 0);
			//int fromTo[] = { 0,0, 0,1, 0,2 };
			//mixChannels(fil, 1, img, 1, fromTo, 3);
			//cout<<"Camera: "<<static_cast<int>(img.channels())<<" "<<img.size().width<<" "<<img.size().height<<"\n";
			//cout<<"Filtered: "<<static_cast<int>(fil.channels())<<" "<<fil.size().width<<" "<<fil.size().height<<"\n";
			//cout<<"Reshaped Filtered: "<<static_cast<int>(rfil.channels())<<" "<<rfil.size().width<<" "<<rfil.size().height<<"\n";
			//gemm(img, fil, 1, );
			//img = img.mul(fil);
			//addWeighted(img, 1, fil, 1, 0, img);
			//log(img, img);
			imshow("Image", img);
			waitKey(1);
			delete[] channels;
			delete[] channels2;
		}
		catch( cv::Exception& e )
		{
			const char* err_msg = e.what();
			std::cout<<"ExceptionJA: "<<err_msg<<"\n";
		}
	}
}
