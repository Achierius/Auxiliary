#include "RoboColorFilter.h"

cv::Mat roboColorFilter(cv::Mat in, int hMin = 0, int hMax = 255, int sMin = 0, int sMax = 255, int vMin = 0, int vMax = 255, bool DEBUG = false, bool DEBUGPRE = false, bool bitAnd = true)
{
        bool hueAltered = false;
	bool satAltered = false;
	bool valAltered = false;

//	if(DEBUG) imshow("PreFiltered", in);
        cv::cvtColor(in, in, CV_BGR2HSV);
        cv::Mat * channels = new cv::Mat[3];
        cv::split(in, channels);

        if(hMin != 0 || hMax != 255)
        {
		hueAltered = true;
//                if(DEBUGPRE) imshow("Hue-Unfiltered", channels[0]);
                cv::inRange(channels[0], cv::Scalar(hMin), cv::Scalar(hMax), channels[0]);
                if(DEBUG) cv::imshow("Hue-Filtered", channels[0]);
        }
        if(sMin != 0 || sMax != 255)
        {
		satAltered = true;
//                if(DEBUGPRE) imshow("Saturation-Unfiltered", channels[1]);
                cv::inRange(channels[1], cv::Scalar(sMin), cv::Scalar(sMax), channels[1]);
                if(DEBUG) 
			cv::imshow("Saturation-Filtered", channels[1]);
		if(hueAltered && bitAnd)
		{
			cv::bitwise_and(channels[0], channels[1], channels[0]);
			channels[1] = channels[0].clone();
		}
        }
        if(vMin != 0 || vMax != 255)
        {
		valAltered = true;
//               if(DEBUGPRE) imshow("Value-Unfiltered", channels[2]);
                cv::inRange(channels[2], cv::Scalar(vMin), cv::Scalar(vMax), channels[2]);
                if(DEBUG)
			cv::imshow("Value-Filtered", channels[2]);
        }
	if(bitAnd)
	{
		if(hueAltered && valAltered && satAltered) //Sat, Value, Hue
		{
			cv::bitwise_and(channels[0], channels[1], channels[0]);
			cv::bitwise_and(channels[0], channels[2], channels[0]);
			channels[1] = channels[0].clone();
			channels[2] = channels[0].clone();
		}
		else if(valAltered && hueAltered) //Value, Hue
		{
			cv::bitwise_and(channels[0], channels[2], channels[0]);
			channels[2] = channels[0].clone();
			channels[1] = channels[0].clone();
		}
		else if(hueAltered && satAltered) //Sat, Hue
		{
			cv::bitwise_and(channels[0], channels[1], channels[0]);
			channels[2] = channels[0].clone();
			channels[1] = channels[0].clone();
		}
		else if(satAltered && valAltered) //Sat, Val
		{
			cv::bitwise_and(channels[2], channels[1], channels[1]);
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
	cv::merge(channels, 3, in);
	//	b
	//	b
//	delete[] channels;
	cv::cvtColor(in, in, CV_HSV2BGR);
	return in;
}
