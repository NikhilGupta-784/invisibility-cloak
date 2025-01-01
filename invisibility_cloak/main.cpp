#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>

#include <cloth.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace cv;


Mat clothhsv, bgimg;
int Hmin, Smin, Vmin;
int Hmax, Smax, Vmax;

Mat backgroundimage()
{
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "Error opening video stream or file" << endl;
        return Mat();
    }
    Mat frame;
    cap >> frame;
    if (frame.empty())
    {
        cout << "No captured frame" << endl;
        return Mat();
    }
    imwrite("resource/background.jpg", frame);
    cout << "Background image captured" << endl;
    return frame;
}

int main()
{

    waitKey(3000);
	cout << "Welcome to the Invisibility Cloak!!" << endl;
	waitKey(1000);
	cout << "Please wait for the background image to be captured" << endl;
	waitKey(1500);
	cout << "Please make sure that the background is static and there is no movement in the background" << endl;
	waitKey(1500);
    cout << "Capturing background image in..." << endl;
    
    for (int i = 3; i >= 1; i--)
    {
        cout << i << endl;
        waitKey(1500);
    }

    bgimg = backgroundimage();
	if (bgimg.empty())
	{
		cout << "Error in capturing background image" << endl;
		return -1;
	}
	else
	{
		cout << "Background image captured" << endl;
	}

	

    /*imshow("Background Image", img);
    waitKey(0);*/

	cout << "Please make sure that the cloak is not of the same color as the background by default cloak is Blue" << endl;

	cloth cl;
	vector<int> hsvcl = cl.setcloth(); //by default the color of cloak is blue// To change the color of the cloak, 
									   //use the setcloth function with the path of the image as the argument
    Hmin = hsvcl[0], Hmax = hsvcl[1];
	Smin = hsvcl[2], Smax = hsvcl[3];
	Vmin = hsvcl[4], Vmax = hsvcl[5];
    

	//creating invisilibity cloak

	waitKey(3000);
	cout << "Invisibility cloak is ready" << endl;
	waitKey(1000);
	cout << "Please wear the cloak" << endl;
	waitKey(1000);

	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "Error opening video stream or file" << endl;
		return -1;
	}
    while(true)
	{
		Mat frame;
		cap >> frame;
		if (frame.empty())
		{
			cout << "No captured frame" << endl; //camera 
			break;
		}

		Mat hsv;
		cvtColor(frame, hsv, COLOR_BGR2HSV);
		Mat mask;
		inRange(hsv, Scalar(Hmin, Smin, Vmin), Scalar(Hmax, Smax, Vmax), mask);
		Mat result;
		bitwise_and(frame, frame, result, mask);  //superimposing the frame on the frame
		bitwise_and(bgimg, bgimg, frame, mask);   //superimposing the background image on the frame
        
		
		imshow("Frame", frame);
		imshow("Mask", mask);
		imshow("Result", result);


		auto key = waitKey(1);

		if (key == int("Q") || key == int('q')) //press q to exit
		{
			cap.release();
			destroyAllWindows();
			break;
		}

	}
    return 0;
}