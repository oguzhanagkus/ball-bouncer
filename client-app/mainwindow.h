#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QVector>
#include <QtNetwork>
#include <QMainWindow>
#include <QtDataVisualization>
#include <math.h>
#include <unistd.h>
#include <iostream>
#include "qcustomplot.h"

#define PI 3.14159265

using namespace std;
using namespace QtDataVisualization;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum viewType {view_2d, view_3d, view_camera, view_all};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void plot();
    void set3dGraph();
    void set2dGraphs();
    void addPoints(double y, double x, double z);
    void addNewPointToGraphs(QString message);
    void GraphContainer();

private slots:
    void on_button2d_clicked();
    void on_button3d_clicked();
    void on_button23d_clicked();

public slots:
    void processPendingDatagrams();

private:
    Ui::MainWindow *ui;
    QVector<double> qv_x, qv_y, qv_z,qv_x_previous_dropped,qv_y_previous_dropped,qv_x_pre, qv_y_pre,qv_z_pre;

    QTimer *dataTimer;
    Q3DScatter *graph;
    QWidget *container;
    QWidget *container2;
    QWidget *container3;

    int count = 0;
    int count2 = 0;
    int newSeries = 0;
    int pointCount = 1;
    double x = 0;
    int numberOfGraphs = 10;
    int flag=0;
    int flag3d = 1;
    int ballRadius = 2;

    QCustomPlot * graph_xy;
    QCustomPlot * graph_xz;
    QUdpSocket udpClient;
    QTimer timer;

    viewType currentViewType= view_3d;
};
#endif // MAINWINDOW_H
