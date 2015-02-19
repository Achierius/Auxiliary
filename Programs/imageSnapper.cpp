#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string>
#include <boost/lexical_cast.hpp>
 
using namespace cv;
using namespace std;

int main() {

	Mat image;
	char x = ' ';
	string text = "image";
	string numWord = ""; // string version of number
	string word = ""; // file name excluding .jpg
	string word2 = ".jpg";
	string word3 = ""; // complete file name
	int number = 1;

	VideoCapture cap (0);
	if (!cap.isOpened()) { 
		cout << "Error \n";
		return 0;
	}

	while (true) {
		cap >> image;
		imshow("Video", image);
		x = waitKey(10);
		if (x == 'a') {
			if (number == 1) // first time
				imwrite(text + "1" + word2, image);	
			else 
				imwrite(word3, image);
			numWord = boost::lexical_cast<string>(number); // convert int to string
			word = text + numWord; // image<number>
			number++; // number increases
			word3 = word + word2; // complete file name
			cout << word << ", " + word2 + ", " << word3 << "; ";
		}

		else if (x == 'x') {				
			cout << "Exit Successful \n";
			break;	
		}	
	}
	return 0;
}

