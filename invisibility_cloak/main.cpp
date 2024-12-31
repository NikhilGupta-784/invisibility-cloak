#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


Mat cloth, clothhsv, bgimg;
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
    cout << "Capturing background image in..." << endl;
    
    for (int i = 3; i >= 1; i--)
    {
        cout << i << endl;
        waitKey(1000);
    }

    bgimg = backgroundimage();
	cout << "Background image captured" << endl;



    /*imshow("Background Image", img);
    waitKey(0);*/

    ///ANALYZING THE CLOTH    

    cloth = imread("resource/Cloth.jpg");
    resize(cloth, cloth, Size(640, 480)); 
    cvtColor(cloth, clothhsv, COLOR_BGR2HSV);

	/*namedWindow("Trackbars", WINDOW_NORMAL);
    createTrackbar("H Min", "Trackbars", &Hmin, 179);
    createTrackbar("H Max", "Trackbars", &Hmax, 179);
    createTrackbar("S Min", "Trackbars", &Smin, 255);
    createTrackbar("S Max", "Trackbars", &Smax, 255);
    createTrackbar("V Min", "Trackbars", &Vmin, 255);
    createTrackbar("V Max", "Trackbars", &Vmax, 255);

	while (true)
	{
        imshow("Clothresize", cloth);
		Mat mask;
		inRange(clothhsv, Scalar(Hmin, Smin, Vmin), Scalar(Hmax, Smax, Vmax), mask);
		imshow("Mask", mask);
		Mat result;
		bitwise_and(cloth, cloth, result, mask);
		imshow("Result", result);
		waitKey(1);
	}*/

	//Final values of the cloth is (blue)
    Hmin = 90, Hmax = 128;
    Smin = 50, Smax = 255;
    Vmin = 70, Vmax = 255;



	//creating invisilibity cloak

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
			cout << "No captured frame" << endl;
			break;
		}

		Mat hsv;
		cvtColor(frame, hsv, COLOR_BGR2HSV);
		Mat mask;
		inRange(hsv, Scalar(Hmin, Smin, Vmin), Scalar(Hmax, Smax, Vmax), mask);
		Mat result;
		bitwise_and(frame, frame, result, mask);
		bitwise_and(bgimg, bgimg, frame, mask);   
        
		imshow("Frame", frame);
		imshow("Mask", mask);
		imshow("Result", result);


		auto key = waitKey(1);

		if (key == int("Q") || key == int('q'))
		{
			cap.release();
			destroyAllWindows();
			break;

		}

	}
    return 0;
}