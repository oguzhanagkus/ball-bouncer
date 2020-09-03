#include "colortracker.h"
#include<QDebug>
#include<QThread>
#include<QMetaObject>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
colorTracker::colorTracker(QObject * parent)
       :QThread { parent }
       ,mVideoCap{ID_CAMERA}
{

}

void colorTracker::run()
{
    mVideoCap = VideoCapture("/home/mel/Desktop/son hal/ekler/MOV3.mp4");


    // Create a Control Window and Trackbars
        // namedWindow("Control", CV_WINDOW_AUTOSIZE);		// Control Window
   //     namedWindow("Control");		// Control Window

        int iLowH = 0;
        int iHighH = 21;

        int iLowS = 100;
        int iHighS = 255;

        int iLowV = 100;
        int iHighV = 255;

        // Create Trackbars in Control Window
    /*    createTrackbar("LowH", "Control", &iLowH, 179);		//Hue (0 - 179)
        createTrackbar("HighH", "Control", &iHighH, 179);

        createTrackbar("LowS", "Control", &iLowS, 255);		//Saturation (0 - 255)
        createTrackbar("HighS", "Control", &iHighS, 255);

        createTrackbar("LowV", "Control", &iLowV, 255);		//Value (0 - 255)
        createTrackbar("HighV", "Control", &iHighV, 255);*/

        //// Capture a Temporary Image from the camera
        //Mat imgTmp;
        //cap.read(imgTmp);
        //// Create a Black Image with the size as the camera output
        //Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);;

        while ( mVideoCap.isOpened()) {				// until the Esc is pressed or webcam connection is lost

            mVideoCap >> mframe;
            if(!mframe.empty()){
                mPixmap = cvMatToQPixmap(mframe);
                emit newPixmapCaptured();

            }



           // Mat imgOriginal;
            bool blnFrameReadSuccessfully= 1;// = cap.read(imgOriginal);

            if (!blnFrameReadSuccessfully || mframe.empty()) {				// if frame read unsuccessfully
                std::cout << "error: frame can't read \n";						// print error message
                break;															// jump out of loop
            }

            // Convert the captured frame from BGR to HSV
            Mat imgHSV;
            cvtColor(mframe, imgHSV, COLOR_BGR2HSV);

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
                    std::cout << "Ball position X = "<< posX* 0.026458333
                    <<",\tY = "<< posY* 0.026458333
                    <<",\tRadius = "<< R* 0.026458333
                    <<",\tArea = "<< area
                    <<",\tDistance = "<< distance <<"\n";
                    circle(mframe, Point(posX, posY), R, Scalar(0, 0, 255), 2);

                    x = posX * 0.026458333;
                    y = posY * 0.026458333;
                    height =distance; //* 0.026458333;

                    emit dataFromImageProcessing();

                }

            }

       /*     cv::namedWindow("Original", 0);
            cv::namedWindow("Thresholded Image", 0);

            cv::resizeWindow("Original",500,500);
            cv::resizeWindow("Thresholded Image",500,500);

            // Show the Thresholded Image
            imshow("Thresholded Image", imgThresholded);

            // Show the Tracked Image
            // imgOriginal = imgOriginal + imgLines;
            imshow("Original", mframe);

            // Wait for key is pressed then break loop
            if (waitKey(5) == 27)			//ESC 27, ENTER 13, SPACE 32
            {
                break;
            }*/
        }
}


QImage  colorTracker::cvMatToQImage( const cv::Mat &inMat )
   {
      switch ( inMat.type() )
      {
         // 8-bit, 4 channel
         case CV_8UC4:
         {
            QImage image( inMat.data,
                          inMat.cols, inMat.rows,
                          static_cast<int>(inMat.step),
                          QImage::Format_ARGB32 );

            return image;
         }

         // 8-bit, 3 channel
         case CV_8UC3:
         {
            QImage image( inMat.data,
                          inMat.cols, inMat.rows,
                          static_cast<int>(inMat.step),
                          QImage::Format_RGB888 );

            return image.rgbSwapped();
         }

         // 8-bit, 1 channel
         case CV_8UC1:
         {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
            QImage image( inMat.data,
                          inMat.cols, inMat.rows,
                          static_cast<int>(inMat.step),
                          QImage::Format_Grayscale8 );
#else
            static QVector<QRgb>  sColorTable;

            // only create our color table the first time
            if ( sColorTable.isEmpty() )
            {
               sColorTable.resize( 256 );

               for ( int i = 0; i < 256; ++i )
               {
                  sColorTable[i] = qRgb( i, i, i );
               }
            }

            QImage image( inMat.data,
                          inMat.cols, inMat.rows,
                          static_cast<int>(inMat.step),
                          QImage::Format_Indexed8 );

            image.setColorTable( sColorTable );
#endif

            return image;
         }

         default:
            qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
            break;
      }

      return QImage();
   }

QPixmap colorTracker:: cvMatToQPixmap( const cv::Mat &inMat )
{
      return QPixmap::fromImage( cvMatToQImage( inMat ) );
}

void colorTracker::setValue(int value)
{
    x = value;
    emit valueChanged(value);
}
