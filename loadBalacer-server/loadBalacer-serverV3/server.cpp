#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h> // File control
#include <termios.h> // POSIX terminal control
#include <unistd.h> // UNIX standard
#include <errno.h> // Error number
#include "pid.hpp"

using namespace cv;
using namespace std;

//int cornerCenterX[12] = {160,170,195,270,340,185,390,380,150,280,195,155};
//int cornerCenterY[12] = {220,280,330,345,355,320,230,165,125,115,335,175};
int cornerCenterX[12] = {215,230,235,280,340,375,380,365,350,295,260,215};
int cornerCenterY[12] = {215,270,290,300,300,270,210,170,130,130,130,165};


struct command {
  uint8_t angle_0 = 0;
  uint8_t angle_1 = 0;
  uint8_t angle_2 = 0;
  uint8_t angle_3 = 0;
};


/*Midpoint coordinates*/
#define CENTER_X 320.0
#define CENTER_Y 240.0

struct Angles{
    int motor1 = 0;    /*Left Motor*/
    int motor2 = 0;    /*Righ Motor*/
    int motor3 = 0;    /*Upper Motor*/
    int motor4 = 0;    /*Lower Motor*/
};


int sleepCalculation(int lastS1,int lastS2,int lastS3,int lastS4,
    			int cur1,int cur2,int cur3,int cur4);
int main(int argc, char** argv)
{
	// Capture the video from Integrated Webcam
	//VideoCapture cap("http://192.168.43.31:4747/mjpegfeed?640x480");
	VideoCapture cap(3);
	struct Angles *a=(struct Angles*)malloc(sizeof(struct Angles));
	//cap.set(3,320);
	//cap.set(4,240);
	a->motor1=0;
	a->motor2=0;
	a->motor3=0;
	a->motor4=0;

    //printf("%.4f - %.4f - %.4f - %.4f",a->motor1,a->motor2,a->motor3,a->motor4);

	/* ---------- Opening serial port and configration ---------- */

	  char port_name[] = "/dev/ttyACM0"; // Port name that board connected.
	  int port = open(port_name, O_RDWR | O_NOCTTY | O_NDELAY); // File descriptor

	  if(port == -1) // Error checking
	    printf("Error in opening ttyACM0.\n");
	  else
	    printf("ttyACM1 opened.\n\n");

	  struct termios SerialPortSettings; // Structure

	  tcgetattr(port, &SerialPortSettings); // Current attributes of port
	  cfsetispeed(&SerialPortSettings, B57600); // Baudrate 57600
	  cfsetospeed(&SerialPortSettings, B57600); // Baudrate 57600

	  SerialPortSettings.c_cflag &= ~PARENB; // Disable parity
	  SerialPortSettings.c_cflag &= ~CSTOPB; // Stop bit
	  SerialPortSettings.c_cflag &= ~CSIZE; // Clears the mask for data size
	  SerialPortSettings.c_cflag |=  CS8; // Data bits = 8
	  SerialPortSettings.c_cflag &= ~CRTSCTS; // No hardware flow control
	  SerialPortSettings.c_cflag |= CREAD | CLOCAL; // Enable reciever
	  SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable flow control
	  SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Non connonical mode
	  SerialPortSettings.c_oflag &= ~OPOST; // No output processing
	  SerialPortSettings.c_cc[VMIN] = 5; // Read at least 5 character
	  SerialPortSettings.c_cc[VTIME] = 0; // Wait indefinetly
	  if((tcsetattr(port, TCSANOW, &SerialPortSettings)) != 0) // Set the attributes
	  {
	    printf("Error in setting attributes.\n");
	    return -1;
	  }

	// If not success, exit program
	if (!cap.isOpened())
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}
	
	namedWindow("Control");		// Control Window

	int iLowH = 0;
	int iHighH = 21;

	int iLowS = 30;
	int iHighS = 255;

	int iLowV = 200;
	int iHighV = 255;

	// Create Trackbars in Control Window
	createTrackbar("LowH", "Control", &iLowH, 179);		//Hue (0 - 179)
	createTrackbar("HighH", "Control", &iHighH, 179);

	createTrackbar("LowS", "Control", &iLowS, 255);		//Saturation (0 - 255)
	createTrackbar("HighS", "Control", &iHighS, 255);

	createTrackbar("LowV", "Control", &iLowV, 255);		//Value (0 - 255)
	createTrackbar("HighV", "Control", &iHighV, 255);

	/* Init pid objects*/
	PID * pidServoX = new PID( "pidServoX_config" );	
	if ( pidServoX->fail() )
	{
			cerr << pidServoX->getErrorStr() << endl;
			exit( EXIT_FAILURE );
	}
	PID * pidServoY = new PID( "pidServoY_config" );
	if ( pidServoY->fail() )
	{
			cerr << pidServoY->getErrorStr() << endl;
			exit( EXIT_FAILURE );
	}

	int onoff = 0;
	int sleepV = 0;
	int lastS1 = 0,lastS2 = 0,lastS3 = 0,lastS4 = 0;
	int index = 0;
	int spaceIndex;

	int selection;
	printf("1'e bas denge için\n");
	printf("2'e bas zıplatma için\n");
	cin>>selection;
	int indexPoint = 0;
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

		
		/* Init pid objects end */


		// If the area <= 10000, consider that it's because of the noise
		if (dArea > 100000)
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
			a->motor1 = 0;
			a->motor2 = 0;
			a->motor3 = 0;
			a->motor4 = 0;
			
			double distance = 6*pow(10,-9)*pow(area,2) - 0.0006*area + 22.005 ;
    		
			/* Selman Start*/
			//cout << "errorX: " << CENTER_X - posX << endl;
			//cout << "errorY: " << CENTER_Y - posY << endl;

    		if (selection == 1 )
    		{
    			pidServoX->compute( CENTER_X - posX );
				pidServoY->compute( CENTER_Y - posY );

				cout << "signalX: " << pidServoX->getOutput() << endl;
				cout << "signalY: " << pidServoY->getOutput() << endl;

				//a->motor1 = - pidServoX.getOutput();
				if (pidServoY->getOutput() < 0)
					a->motor4 = - pidServoY->getOutput();
				else
					a->motor2 = pidServoY->getOutput();

				if (pidServoX->getOutput() < 0)
					a->motor1 = - pidServoX->getOutput();
				else
					a->motor3 = pidServoX->getOutput();


	    		printf("%d - %d - %d - %d ----\n",a->motor1,a->motor2,a->motor3,a->motor4);

				/* Selman End */
		   		struct command temp;
				char buffer[5];

				buffer[4] = '\0';

				temp.angle_0 = (uint8_t)a->motor1+5;
				temp.angle_1 = (uint8_t)a->motor2;
				temp.angle_2 = (uint8_t)a->motor3;
				temp.angle_3 = (uint8_t)a->motor4+10;
				lastS1 = temp.angle_0;
				lastS2 = temp.angle_1;
				lastS3 = temp.angle_2;
				lastS4 = temp.angle_3;

			
				write(port, &temp, sizeof(temp));
				tcflush(port, TCIFLUSH);
				sleepCalculation(lastS1,lastS2,lastS3,lastS4,temp.angle_0,temp.angle_1,temp.angle_2,temp.angle_3);

    		}else if(selection == 2){

    			pidServoX->compute( cornerCenterX[indexPoint%12] - posX );
				pidServoY->compute( cornerCenterY[indexPoint%12] - posY );

				//cout << "signalX: " << pidServoX->getOutput() << endl;
				//cout << "signalY: " << pidServoY->getOutput() << endl;

				//a->motor1 = - pidServoX.getOutput();
				if (pidServoY->getOutput() < 0)
					a->motor4 = - pidServoY->getOutput();
				else
					a->motor2 = pidServoY->getOutput();

				if (pidServoX->getOutput() < 0)
					a->motor1 = - pidServoX->getOutput();
				else
					a->motor3 = pidServoX->getOutput();

	    		//printf("%d - %d - %d - %d ----\n",a->motor1,a->motor2,a->motor3,a->motor4);

				/* Selman End */
		   		struct command temp;
				char buffer[5];

				buffer[4] = '\0';

				temp.angle_0 = (uint8_t)a->motor1+5;
				temp.angle_1 = (uint8_t)a->motor2;
				temp.angle_2 = (uint8_t)a->motor3;
				temp.angle_3 = (uint8_t)a->motor4+10;
				lastS1 = temp.angle_0;
				lastS2 = temp.angle_1;
				lastS3 = temp.angle_2;
				lastS4 = temp.angle_3;
			
				write(port, &temp, sizeof(temp));
				tcflush(port, TCIFLUSH);
				sleepCalculation(lastS1,lastS2,lastS3,lastS4,temp.angle_0,temp.angle_1,temp.angle_2,temp.angle_3);

				if ((abs(cornerCenterX[indexPoint%12]-posX)<100) && (abs(cornerCenterY[indexPoint%12]-posY)<100))
				{
					indexPoint++;
					//pidServoX = new PID( "pidServoX_config" );
					if ( pidServoX->fail() )
					{
							cerr << pidServoX->getErrorStr() << endl;
							exit( EXIT_FAILURE );
					}
					//pidServoY = new PID( "pidServoY_config" );
					if ( pidServoY->fail() )
					{
							cerr << pidServoY->getErrorStr() << endl;
							exit( EXIT_FAILURE );
					}
					cout<<"Safe circle --> "<<indexPoint<<endl;
				}
    		}
				
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
	struct command temp;
	temp.angle_0 = 0 + 5;
	temp.angle_1 = 0;
	temp.angle_2 = 0;
	temp.angle_3 = 0 +10;
	write(port, &temp, sizeof(temp));
	tcflush(port, TCIFLUSH);
	free(a);
	close(port);
	printf("\nttyACM1 closed.\n");

	return 0;
}

int sleepCalculation(int lastS1,int lastS2,int lastS3,int lastS4,
    			int cur1,int cur2,int cur3,int cur4){

	int max = abs(lastS1-cur1);
	if (max<abs(lastS2-cur2))
	{
		max = abs(lastS2-cur2); 
	}else if (max<abs(lastS3-cur3))
	{
		max = abs(lastS3-cur3); 
	}if (max<abs(lastS4-cur4))
	{
		max = abs(lastS4-cur4); 
	}
	return ((max*160000)/60);
}