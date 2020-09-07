#include "colortracker.h"

#define BOUNCERUP 30
#define CENTER_X 320.0
#define CENTER_Y 240.0
#define NUMBERPOINT 4
#define DURATIONPERIOD 400
#define MOTOR_0_OFFSET 10
#define JUMP 30

int cornerCenterX[NUMBERPOINT] = {320, 430, 310, 175};
int cornerCenterY[NUMBERPOINT] = {375, 240, 80, 240};

/* -------------------------------------------------- */

colorTracker::colorTracker(QObject *parent, int cameraIndex) : QThread {parent} , mVideoCap{}
{
    this->flag = -1;
    this->cameraIndex = cameraIndex;
    memcpy(command.key, key, sizeof (key));
}

/* -------------------------------------------------- */

void colorTracker::run()
{
    qDebug() << "burasiKadikoy";
    mVideoCap = VideoCapture(cameraIndex);
    qDebug() << "ssdfsd";
    if (!mVideoCap.isOpened())
    {
        cout << "Webcam cannot opened!\n";
        return;
    }

    /* -------------------- */

    int iLowH, iHighH, iLowS, iHighS, iLowV, iHighV; // Color tracking
    int lastS1, lastS2, lastS3, lastS4; // Last angles
    int realDistance, indexPoint, lastSecond;
    int posX, posY, R;
    int durationSecond;
    double distance;
    double dM01, dM10, dArea;
    bool blnFrameReadSuccessfully;
    auto start = high_resolution_clock::now();
    int even = 0;

    /* -------------------- */

    // For tracking color
    iLowH = 0;
    iHighH = 21;
    iLowS = 30;
    iHighS = 255;
    iLowV = 200;
    iHighV = 255;

    lastS1 = 0;
    lastS2 = 0;
    lastS3 = 0;
    lastS4 = 0;

    realDistance = 72; // Distance between plate and camera sensor in cm
    indexPoint = 0;
    lastSecond = 0;

    /* -------------------- */
    // TODO Memory leak
    PID *pidServoX = nullptr;
    PID *pidServoY = nullptr;

    /* -------------------- */
    while (true)
    {
        mVideoCap >> mframe;

        if (!mframe.empty())
        {
            mPixmap = cvMatToQPixmap(mframe);

            // Sends signal to mainwindow, displays current image
            emit newPixmapCaptured();
        }

        /* -------------------- */

        Mat imgOriginal;
        blnFrameReadSuccessfully = mVideoCap.read(imgOriginal);

        if (!blnFrameReadSuccessfully || imgOriginal.empty())
        {
            cout << "Frame cannot read!\n";
            break;
        }

        // Convert the captured frame from BGR to HSV
        Mat imgHSV;
        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

        // Create the thresholded image
        Mat imgThresholded;
        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);

        // Noise reduction using Mathematical Morphology
        // Morphological Opening (Removes small objects from the foreground)
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

        // Morphological Closing (Removes small holes from the foreground)
        dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

        // Calculate the Moments of the Thresholded Image
        Moments oMoments = moments(imgThresholded);

        dM01 = oMoments.m01;
        dM10 = oMoments.m10;
        dArea = oMoments.m00;

        if (dArea > 100000)
        {
            // Calculate the centroid of the object
            posX = dM10 / dArea;
            posY = dM01 / dArea;
            R = sqrt((dArea / 255) / 3.14);
            distance = 7350 * 0.4 / R;

            // Info
            x = posX;
            y = posY;
            height = realDistance - distance;

            if (height < 0) // Optimization
            {
                height = 0;
            }

            /* -------------------- */

            if (flag != -1)
            {
                command.angle_0 = 0;
                command.angle_1 = 0;
                command.angle_2 = 0;
                command.angle_3 = 0;
            }

            /* -------------------- */

            if (flag == 0)  // Stop button clicked
            {
                command.angle_0 = MOTOR_0_OFFSET;
                command.angle_1 = 0;
                command.angle_2 = 0;
                command.angle_3 = 10;
            }
            else if (flag == 1)  // Balance button clicked
            {
                if(!pidServoX){
                    pidServoX = new PID("./pid/pidServoX_config");
                    if (pidServoX->fail())
                    {
                        cerr << pidServoX->getErrorStr() << endl;
                        exit( EXIT_FAILURE );
                    }
                }
                if(!pidServoY){
                    pidServoY = new PID("./pid/pidServoY_config");
                    if (pidServoY->fail())
                    {
                        cerr << pidServoY->getErrorStr() << endl;
                        exit( EXIT_FAILURE );
                    }
                }


                /*even = (even+1)%2;
                command.angle_0 = even*JUMP + MOTOR_0_OFFSET;
                command.angle_1 = even*JUMP;
                command.angle_2 = even*JUMP;
                command.angle_3 = even*JUMP + 10;*/
                pidServoX->compute(CENTER_X - posX);
                pidServoY->compute(CENTER_Y - posY);

                if(pidServoY->getOutput() < 0)
                {
                    command.angle_0 = - pidServoY->getOutput();
                }
                else
                {
                    command.angle_2 = pidServoY->getOutput();
                }

                if(pidServoX->getOutput() < 0)
                {
                    command.angle_1 = - pidServoX->getOutput();
                }
                else
                {
                    command.angle_3 = pidServoX->getOutput();
                }

                command.angle_0 += MOTOR_0_OFFSET;
                command.angle_3 += 10;
            }
            else if (flag == 2) // Circle button clicked
            {
                if(!pidServoX){
                    pidServoX = new PID("./pid/pidServoX_config_circle");
                    if (pidServoX->fail())
                    {
                        cerr << pidServoX->getErrorStr() << endl;
                        exit( EXIT_FAILURE );
                    }
                }
                if(!pidServoY){
                    pidServoY = new PID("./pid/pidServoY_config_circle");
                    if (pidServoY->fail())
                    {
                        cerr << pidServoY->getErrorStr() << endl;
                        exit( EXIT_FAILURE );
                    }
                }

                auto end = high_resolution_clock::now();
                durationSecond = duration_cast<milliseconds>(end - start).count();

                pidServoX->compute(cornerCenterX[indexPoint % NUMBERPOINT] - posX);
                pidServoY->compute(cornerCenterY[indexPoint % NUMBERPOINT] - posY);

                if (pidServoY->getOutput() < 0)
                {
                    command.angle_0 = - pidServoY->getOutput();
                }
                else
                {
                    command.angle_2 = pidServoY->getOutput();
                }

                if (pidServoX->getOutput() < 0)
                {
                    command.angle_1 = - pidServoX->getOutput();
                }
                else
                {
                    command.angle_3 = pidServoX->getOutput();
                }

                command.angle_0 += MOTOR_0_OFFSET;
                command.angle_3 += 10;

                if(durationSecond-lastSecond > DURATIONPERIOD)
                {
                    indexPoint++;
                    lastSecond = durationSecond;
                }

                if(pidServoX->fail())
                {
                    cerr << pidServoX->getErrorStr() << endl;
                    exit( EXIT_FAILURE );
                }

                if( pidServoY->fail() )
                {
                    cerr << pidServoY->getErrorStr() << endl;
                    exit( EXIT_FAILURE );
                }

            }

            //TODO command send before sleep
            emit dataFromImageProcessing();

            if (flag != -1)
            {
                QThread::usleep(sleepCalculation(lastS1, lastS2, lastS3, lastS4, command.angle_0, command.angle_1, command.angle_2, command.angle_3));

                lastS1 = command.angle_0;
                lastS2 = command.angle_1;
                lastS3 = command.angle_2;
                lastS4 = command.angle_3;
            }
        }
    }
}

/* -------------------------------------------------- */

QImage colorTracker::cvMatToQImage(const cv::Mat &inMat)
{
    switch (inMat.type())
    {
        // 8-bit, 4 channel
        case CV_8UC4:
        {
            QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_ARGB32);
            return image;
        }

        // 8-bit, 3 channel
        case CV_8UC3:
        {
            QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_RGB888);
            return image.rgbSwapped();
        }

        // 8-bit, 1 channel
        case CV_8UC1:
        {
            #if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
                QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_Grayscale8);
            #else
                static QVector<QRgb>  sColorTable;

                // Only create our color table the first time
                if (sColorTable.isEmpty())
                {
                   sColorTable.resize(256);

                   for (int i = 0; i < 256; ++i)
                   {
                      sColorTable[i] = qRgb( i, i, i );
                   }
                }

                QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_Indexed8);
                image.setColorTable(sColorTable);
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
    return QPixmap::fromImage(cvMatToQImage(inMat));
}

int colorTracker::sleepCalculation(int lastS1, int lastS2, int lastS3, int lastS4, int cur1, int cur2, int cur3, int cur4)
{
    int max = abs(cur1 - lastS1);

    if (max < abs(lastS2 - cur2))
    {
        max = abs(lastS2 - cur2);
    }
    if (max < abs(lastS3 - cur3))
    {
        max = abs(lastS3 - cur3);
    }
    if (max < abs(lastS4 - cur4))
    {
        max = abs(lastS4 - cur4);
    }

    return ((max * 140000) / 60);
}

/* -------------------------------------------------- */
