#ifndef COLORTRACKER_H
#define COLORTRACKER_H

#include <math.h>
#include <chrono>
#include <iostream>

#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QThread>
#include <QMetaObject>

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "pid.hpp"

const char key[] = "K4z";

typedef struct command_t
{
    unsigned char key[4];
    quint8 angle_0;
    quint8 angle_1;
    quint8 angle_2;
    quint8 angle_3;
} Command;

using namespace cv;
using namespace std;
using namespace chrono;

class colorTracker : public QThread
{
    Q_OBJECT

public:
    colorTracker(QObject *parent = nullptr, int cameraIndex = 0);
    QPixmap pixmap() const { return mPixmap; }

signals:
    void newPixmapCaptured();
    void dataFromImageProcessing();

protected:
    void run() override;

private:
    QImage cvMatToQImage(const cv::Mat &inMat);
    QPixmap cvMatToQPixmap(const cv::Mat &inMat);

    int sleepCalculation(int lastS1, int lastS2, int lastS3, int lastS4, int cur1, int cur2, int cur3, int cur4);

private:
    cv::Mat mframe;
    cv::VideoCapture mVideoCap;

    QPixmap mPixmap;

public:
    Command command;

    int cameraIndex;
    int flag;
    double x = 0;
    double y = 0;
    double height = 0;
};

#endif // COLORTRACKER_H
