
Mat colorFilter(Mat in, int hMin = 0, int hMax = 255, int sMin = 0, int sMax = 255, int vMin = 0, int vMax = 255, bool DEBUG = false, bool DEBUGPRE = false, bool bitAnd = true)
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
	//	b
	//	b
//	delete[] channels;
	cvtColor(in, in, CV_HSV2BGR);
	return in;
}
