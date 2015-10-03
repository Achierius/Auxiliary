/**
 * @file camPortCarousel.cpp
 * @author minhoolee
 * @date October 3, 2015
 * @brief Program allows user to determine port number of camera they desire
 *
 * Port number for camera starts at 0 and moves on
 * User presses space to move onto next camera
 */

#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    int camPort = 0;

    while (1)
    {
        //std::cout << "Enter number for camera : ";
        //std::cin >> camPort;

        VideoCapture cap (camPort);

        if ( !cap.isOpened() )  // if not success, exit program
        {
             cout << "Cannot open the camera" << endl;
             return -1;
        }

        namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

        while(1)
        {
            Mat frame;

            bool bSuccess = cap.read(frame); // read a new frame from video

            if (!bSuccess) //if not success, break loop
            {
                cout << "Cannot read the frame from camera" << endl;
                break;
            }

            imshow("MyVideo", frame); //show the frame in "MyVideo" window

            if (waitKey(30) == 32) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
            {
                camPort++;
                break; 
            }
        }
    }
    return 0;
}
