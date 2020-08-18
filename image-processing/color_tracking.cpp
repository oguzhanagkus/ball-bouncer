#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <math.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	// Capture the video from Integrated Webcam
	VideoCapture cap("http://192.168.1.6:4747/mjpegfeed?640x480");
	//VideoCapture cap("2.mp4");


	// If not success, exit program
	if (!cap.isOpened())
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	// Create a Control Window and Trackbars
	// namedWindow("Control", CV_WINDOW_AUTOSIZE);		// Control Window
	namedWindow("Control");		// Control Window

	int iLowH = 0;
	int iHighH = 21;

	int iLowS = 100;
	int iHighS = 255;

	int iLowV = 100;
	int iHighV = 255;

	// Create Trackbars in Control Window
	createTrackbar("LowH", "Control", &iLowH, 179);		//Hue (0 - 179)
	createTrackbar("HighH", "Control", &iHighH, 179);

	createTrackbar("LowS", "Control", &iLowS, 255);		//Saturation (0 - 255)
	createTrackbar("HighS", "Control", &iHighS, 255);

	createTrackbar("LowV", "Control", &iLowV, 255);		//Value (0 - 255)
	createTrackbar("HighV", "Control", &iHighV, 255);

	//// Capture a Temporary Image from the camera
	//Mat imgTmp;
	//cap.read(imgTmp);
	//// Create a Black Image with the size as the camera output
	//Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);;

	while (true)
	{
		Mat imgOriginal;
		bool blnFrameReadSuccessfully = cap.read(imgOriginal);

		if (!blnFrameReadSuccessfully || imgOriginal.empty()) {				// if frame read unsuccessfully
			std::cout << "error: frame can't read \n";						// print error message
			break;															// jump out of loop
		}

		// Convert the captured frame from BGR to HSV
		Mat imgHSV;
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

		// Create the Thresholded Image
		Mat imgThresholded;
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);

		// Noise Reduction using Mathematical Morphology
		// Morphological Opening (Removes small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		// Morphological Closing (Removes small holes from the foreground)
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		// Calculate the Moments of the Thresholded Image
		Moments oMoments = moments(imgThresholded);

		double dM01 = oMoments.m01;
		double dM10 = oMoments.m10;
		double dArea = oMoments.m00;

		// If the area <= 10000, consider that it's because of the noise
		if (dArea > 10000)
		{
			// Calculate the Centroid of the Object
			int posX = dM10 / dArea;
			int posY = dM01 / dArea;
			int R = sqrt((dArea / 255) / 3.14);

			int realR = 4;
			int f = -10;
			int fpx = 750;
			int d = (realR*fpx) / R + f;

			double area = R*R*M_PI;

			double distance = 6*pow(10,-9)*pow(area,2) - 0.0006*area + 22.005 ;

			if (posX >= 0 && posY >= 0)
			{
				std::cout << "Ball position X = "<< posX			
				<<",\tY = "<< posY								
				<<",\tRadius = "<< R
				<<",\tArea = "<< area
				<<",\tDistance = "<< distance <<"\n";	
				circle(imgOriginal, Point(posX, posY), R, Scalar(0, 0, 255), 2);
			}

		}

		cv::namedWindow("Original", 0);
		cv::namedWindow("Thresholded Image", 0);

		cv::resizeWindow("Original",500,500);
		cv::resizeWindow("Thresholded Image",500,500);

		// Show the Thresholded Image
		imshow("Thresholded Image", imgThresholded);

		// Show the Tracked Image
		// imgOriginal = imgOriginal + imgLines;
		imshow("Original", imgOriginal);

		// Wait for key is pressed then break loop
		if (waitKey(5) == 27)			//ESC 27, ENTER 13, SPACE 32
		{
			break;
		}
	}

	return 0;
}
