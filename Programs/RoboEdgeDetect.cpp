
Mat edgeDetect(Mat image, Mat * channels, int edge_ksize, int threshLow, int threshHigh)
{
	split(image, channels);
	Canny(image, channels[1], threshLow, threshHigh);
		channels[0] = channels[1];
		channels[2] = channels[0];	
	merge(channels, 3, image);
	return image;
}
