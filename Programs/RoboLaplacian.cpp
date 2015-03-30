Mat laplacian(Mat image, Mat * channels, int ddepth, int sharpen_ksize, int scale, int delta)
{
	Mat image_gray, dst, abs_dst;

	cvtColor(image, image_gray, COLOR_RGB2GRAY); // HSV to grayscale
  	Laplacian(image_gray, dst, ddepth, sharpen_ksize, scale, delta, BORDER_DEFAULT);
  	convertScaleAbs(dst, abs_dst);
  		channels[0] = abs_dst;
		channels[1] = abs_dst;
		channels[2] = abs_dst;
	merge(channels, 3, abs_dst);
	addWeighted(image, 1, abs_dst, 2, 0, image); 
	return image;
}
