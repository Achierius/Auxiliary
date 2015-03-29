int main( int argc, char* argv[]) {

	hueTest();
	return 0;

}

void hueTest() {
	
	Mat image;
	int MinH = 30;
	int MaxH = 60;
	int MinS = 180;
	int MaxS = 255;
	Mat * channels = new Mat [3];

	VideoCapture cap (0);
	if(!cap.isOpened()) {
		cout<<"Error";
		return;
	}

	while (true)
	{
		cap >> image;
		cvtColor(image, image, CV_BGR2HSV);
		imshow("Pre", image); // pure feed
		split(image, channels);
		imshow("PreHue", channels[0]); // hue of feed
		inRange(channels[0], Scalar(MinH), Scalar(MaxH), channels[0]);	
		imshow("Hue", channels[0]); // hue of feed after non-yellow turns black
		imshow("PreSat", channels[1]);
		inRange(channels[1], Scalar(MinS), Scalar(MaxS), channels[1]);
		imshow("Sat", channels[1]);
		merge(channels, 3, image);
		imshow("All", image);
	
		waitKey(1);
	}

}
