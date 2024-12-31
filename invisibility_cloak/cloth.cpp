
///ANALYZING THE CLOTH   

#include <cloth.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <string>


using namespace std;
using namespace cv;


Mat cl, clhsv;

//Setting the color range for the cloth
vector<int> cloth::setcloth()
{
	//Blue 
	this->Hmin = 90, this->Hmax = 128;
	this->Smin = 50, this->Smax = 255;
	this->Vmin = 70, this->Vmax = 255;

	return { this->Hmin,
			this->Hmax,
			this->Smin,
			this->Smax,
			this->Vmin,
			this->Vmax };
		
}

vector<int> cloth::setcloth(string path)
{
	Mat cl = imread(path);
	if (cl.empty())
	{
		cerr << "Error : could not load image at " << path << endl;
		return{};
	}
	resize(cl, cl, Size(640, 480));
	cvtColor(cl, clhsv, COLOR_BGR2HSV);
	namedWindow("Trackbars", WINDOW_NORMAL);
			 
	createTrackbar("H Min", "Trackbars", &Hmin, 179);
	createTrackbar("H Max", "Trackbars", &Hmax, 179);
	createTrackbar("S Min", "Trackbars", &Smin, 255);
	createTrackbar("S Max", "Trackbars", &Smax, 255);
	createTrackbar("V Min", "Trackbars", &Vmin, 255);
	createTrackbar("V Max", "Trackbars", &Vmax, 255);

	while (true)
	{	
		//getting the current position of the trackbars
		this->Hmin = getTrackbarPos("H Min", "Trackbars");
		this->Hmax = getTrackbarPos("H Max", "Trackbars");
		this->Smin = getTrackbarPos("S Min", "Trackbars");
		this->Smax = getTrackbarPos("S Max", "Trackbars");
		this->Vmin = getTrackbarPos("V Min", "Trackbars");
		this->Vmax = getTrackbarPos("V Max", "Trackbars");

		//creating a mask for the cloth
		imshow("Clothresize", cl);
		Mat mask;
		inRange(cl, Scalar(Hmin, Smin, Vmin), Scalar(Hmax, Smax, Vmax), mask);
		imshow("Mask", mask);
		Mat result;
		bitwise_and(cl, cl, result, mask);
		imshow("Result", result);
		
		//exit the loop if 'C' is pressed
		char key = waitKey(1);

		if (key == int('C') || key == int('c'))
		{
			destroyWindow("Trackbars");
			destroyWindow("Clothresize");
			destroyWindow("Mask");
			destroyWindow("Result");
			break;
		}

	}
	return { this->Hmin, 
			this->Hmax, 
			this->Smin, 
			this->Smax, 
			this->Vmin, 
			this->Vmax };
}
