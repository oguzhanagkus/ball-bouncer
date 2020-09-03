#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChar>
#include <QList>
#include <QTimer>
#include <QDebug>
#include <QVector>
#include <QtNetwork>
#include <QDataStream>
#include <QSerialPort>
#include <QtDataVisualization>

#include <math.h>
#include <unistd.h>
#include <colortracker.h>
#include "qcustomplot.h"

using namespace std;
using namespace QtDataVisualization;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum viewType {view_2d, view_3d, view_camera, view_all};

class videoCapture;
class colorTracker;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, QString portName = "", int cameraIndex = 0);
    ~MainWindow();

    void plot();
    void addPoints(double y, double x, double z);
    void set2dGraphs();
    void set3dGraph();
    void GraphContainer();

private slots:
    void on_button2d_clicked();
    void on_button3d_clicked();
    void on_button23d_clicked();

    void on_balance_button_clicked();
    void on_circle_button_clicked();
    void on_stop_button_clicked();

    void sendDatagram();
    void dataFromImageProcesssing();

    // Simulation
    void changeAngleRobot1();
    void changeAngleRobot2();
    void changeAngleRobot3();
    void changeAngleRobot4();
    void giveArmsAngle(double degree_arm1, double degree_arm2, double degree_arm3, double degree_arm4);
    void changeBallsCoordinates(double x, double y, double z);
    void go();

private:
    void initGraphs();
    void initSimulation();
    void initSerialPort(QString portName);
    void initImageProcessing(int cameraIndex);
    void connectAllModules();

private:
    Ui::MainWindow *ui;

    // View type
    int numberOfGraphs = 5;             // The number of old points that are going to be displayed at the 3D graph
    int pointCount = 1;                 // The number of current points displayed at the 3D graph
    int flagLayout = 1;                 // Layout: 2D, 3D, 2D and 3D
    int ballRadius = 2;                 // ?
    viewType currentViewType = view_3d; // Default view

    /*
     * To add custom plot a point the class needs a QVector object
     * The x,y,z values are kept in the vectors first element.qv_x
     * Previous dropped vectors are used to keep the previous location where the ball droped
     * The x,y,z values are kept in the vectors first element.qv_x_previous_dropped
     * Previous vectors are used to keep the previous location
     * The x,y,z values are kept in the vectors first element.qv_z_pre
     */
    QVector<double> qv_x;
    QVector<double> qv_y;
    QVector<double> qv_z;
    QVector<double> qv_x_previous_dropped;
    QVector<double> qv_y_previous_dropped;
    QVector<double> qv_x_pre;
    QVector<double> qv_y_pre;
    QVector<double> qv_z_pre;

    // 2D graphs
    QCustomPlot * graph_xy;
    QCustomPlot * graph_xz;

    // 3D graph
    Q3DScatter *graph;
    QWidget *container;
    QWidget *container2;

    // Camera image
    QLabel *cameraImage;
    double height_img=0;
    double x_img=0;
    double y_img=0;

    // Image processing
    videoCapture *mOpencv_videoCapture;
    colorTracker *mOpencv_colorTracker;
    int cameraIndex;

    // Network
    QUdpSocket udpServer;
    QString message;
    QTimer timer;
    int number = 1; // ?

    // Serial port
    QSerialPort serialPort;

    // Simulation
    QTimer timer_robot1;
    QTimer timer_robot2;
    QTimer timer_robot3;
    QTimer timer_robot4;

    QTimer tmr;
    clock_t clk;

    double t, dt;
    int i = -90;
    int j = 0;

    int armNumber = 0;
    double orj_angle_robot1 = 0;
    double angle_robot1  = -50;
    double angle2_robot1 = 10;
    double angle3_robot1 = 10;
    int flag_robot1 = 0;
    int flag2_robot1 = 0;
    int flag3_robot1 = 0;

    double orj_angle_robot2 = 40;
    double angle_robot2 = -50;
    double angle2_robot2 = 10;
    double angle3_robot2 = 10;
    int flag_robot2 = 0;
    int flag2_robot2 = 0;
    int flag3_robot2 = 0;

    double orj_angle_robot3 = 40;
    double angle_robot3 = -50;
    double angle2_robot3 = 10;
    double angle3_robot3 = 10;
    int flag_robot3 = 0;
    int flag2_robot3 = 0;
    int flag3_robot3 = 0;

    double orj_angle_robot4 = 40;
    double angle_robot4 = -50;
    double angle2_robot4 = 10;
    double angle3_robot4 = 10;
    int flag_robot4 = 0;
    int flag2_robot4 = 0;
    int flag3_robot4 = 0;
};

#endif // MAINWINDOW_H
