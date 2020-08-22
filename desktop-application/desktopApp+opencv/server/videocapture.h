#ifndef VIDEOCAPTURE_H
#define VIDEOCAPTURE_H

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<math.h>
#include<QThread>
#include<QPixmap>
#include<QImage>
#define ID_CAMERA 0
using namespace cv;
using namespace std;

class videoCapture : public QThread
{
    Q_OBJECT
public:
    videoCapture(QObject * parent = nullptr);

    QPixmap pixmap()const
    {
        return mPixmap;

    }
public slots:
    void setValue(int value);
 signals:
    void newPixmapCaptured();
    void dataFromImageProcessing();
    void x_value();
    void valueChanged(double newValue);
protected:
    void run() override;
private:
    QPixmap mPixmap;
    cv::Mat mframe;
    cv::VideoCapture mVideoCap;
    QPixmap cvMatToQPixmap( const cv::Mat &inMat );
    QImage cvMatToQImage( const cv::Mat &inMat );

public:
    double x = 0;
    double y = 0;
    double height = 0;
};

#endif // VIDEOCAPTURE_H
