#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<math.h>
#include<QThread>

using namespace cv;
using namespace std;
/*
TRACK A YELLOW BALL - OBJECT DETECTION METHOD USING COLOR SEPERATION OPEN CV 3.1.0
author - Rachit Gulati
*/

class imageProcessing : public QThread
{
        Q_OBJECT

public:
    imageProcessing();
    int hough_transform();
    QImage  cvMatToQImage( const cv::Mat &inMat );
};

#endif // IMAGEPROCESSING_H
