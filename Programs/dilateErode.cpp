
Mat dilateErode(Mat in, int holes, int noise, Mat element)
{
	dilate(in, in, element, Point(-1, -1), holes);
	erode(in, in, element, Point(-1, -1), holes+noise); //Can use cv::Mat() instead of element for the kernel matrix being used as the third argument 
	dilate(in, in, element, Point(-1, -1), noise);
	return in;
}
