#include "videocapture.h"
#include<QDebug>
#include<QThread>
#include<QMetaObject>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
videoCapture::videoCapture(QObject * parent)
       :QThread { parent }
       ,mVideoCap{ID_CAMERA}
{

}

void videoCapture::run()
{
    mVideoCap = VideoCapture("/home/mel/Desktop/son hal/ekler/MOV3.mp4");
 /*   if(mVideoCap.isOpened()){
        while(true){

        }
    }*/



  //  Mat imgOriginal;		// Input image
    Mat hsvImg;				// HSV Image
    Mat threshImg;			// Thresh Image

    vector<cv::Vec3f> v3fCircles;		// 3 element vector of floats, this will be the pass by reference output of HoughCircles()

    char charCheckForEscKey = 0;

    int lowH = 0;							// Set Hue
    int highH = 21;

    int lowS = 100;							// Set Saturation
    int highS = 255;

    int lowV = 100;						// Set Value
    int highV = 255;
    // HUE for YELLOW is 21-30.
    // Adjust Saturation and Value depending on the lighting condition of the environment as well as the surface of the object.


    while (charCheckForEscKey != 27 && mVideoCap.isOpened()) {				// until the Esc is pressed or webcam connection is lost

        mVideoCap >> mframe;
        if(!mframe.empty()){
            mPixmap = cvMatToQPixmap(mframe);
            emit newPixmapCaptured();

        }

       // bool blnFrameReadSuccessfully = mVideoCap.read(imgOriginal);		// get next frame
        bool blnFrameReadSuccessfully=1;
       // imgOriginal = mframe;

        if (!blnFrameReadSuccessfully || mframe.empty()) {				// if frame read unsuccessfully
            std::cout << "error: frame can't read \n";						// print error message
            break;															// jump out of loop
        }

        cv::medianBlur(mframe, mframe, 3);

        cv::cvtColor(mframe, hsvImg, COLOR_BGR2HSV);						// Convert Original Image to HSV Thresh Image

        cv::inRange(hsvImg, cv::Scalar(lowH, lowS, lowV), cv::Scalar(highH, highS, highV), threshImg);

        cv::GaussianBlur(threshImg, threshImg, cv::Size(3, 3), 0);			//Blur Effect
        cv::dilate(threshImg, threshImg, 0);								// Dilate Filter Effect
        cv::erode(threshImg, threshImg, 0);								// Erode Filter Effect

        // fill circles vector with all circles in processed image
        cv::HoughCircles(threshImg,v3fCircles, HOUGH_GRADIENT,2,threshImg.rows/4,100,50,10,800);  // algorithm for detecting circles

        for (int i = 0; i < v3fCircles.size(); i++) {						// for each circle

            std::cout << "Ball position X = "<< v3fCircles[i][0]*0.026458333			// x position of center point of circle
                <<",\tY = "<< v3fCircles[i][1]*0.026458333								// y position of center point of circle
                <<",\tRadius = "<< v3fCircles[i][2]*0.026458333 					// radius of circle
                <<",\tArea = "<< v3fCircles[i][2]*v3fCircles[i][2]*M_PI << "\n";


            x = v3fCircles[i][0] * 0.026458333;
            y = v3fCircles[i][1] * 0.026458333;
            height = v3fCircles[i][2] * 0.026458333; //şu anlık radius gönderiyorum height yerine


            emit dataFromImageProcessing();

                                                                                // draw small green circle at center of object detected
            cv::circle(mframe,												// draw on original image
                cv::Point((int)v3fCircles[i][0], (int)v3fCircles[i][1]),		// center point of circle
                3,																// radius of circle in pixels
                cv::Scalar(0, 255, 0),											// draw green
                FILLED);														// thickness

                                                                                // draw red circle around object detected
            cv::circle(mframe,												// draw on original image
                cv::Point((int)v3fCircles[i][0], (int)v3fCircles[i][1]),		// center point of circle
                (int)v3fCircles[i][2],											// radius of circle in pixels
                cv::Scalar(0, 0, 255),											// draw red
                3);																// thickness


        }

        // declare windows
        cv::namedWindow("imgOriginal", 0);
        cv::namedWindow("threshImg", 0);

        cv::createTrackbar("LowH", "threshImg", &lowH, 179);	//Hue (0 - 179)
        cv::createTrackbar("HighH", "threshImg", &highH, 179);

        cv::createTrackbar("LowS", "threshImg", &lowS, 255);	//Saturation (0 - 255)
        cv::createTrackbar("HighS", "threshImg", &highS, 255);

        cv::createTrackbar("LowV", "threshImg", &lowV, 255);	//Value (0 - 255)
        cv::createTrackbar("HighV", "threshImg", &highV, 255);


        cv::resizeWindow("imgOriginal",800,800);
        cv::resizeWindow("threshImg",800,800);

        cv::imshow("imgOriginal", mframe);					// show windows
        cv::imshow("threshImg", threshImg);

      //  charCheckForEscKey = cv::waitKey(1);					// delay and get key press
    }
}


QImage  videoCapture::cvMatToQImage( const cv::Mat &inMat )
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

QPixmap videoCapture:: cvMatToQPixmap( const cv::Mat &inMat )
{
      return QPixmap::fromImage( cvMatToQImage( inMat ) );
}

void videoCapture::setValue(int value)
{
    x = value;
    emit valueChanged(value);
}
