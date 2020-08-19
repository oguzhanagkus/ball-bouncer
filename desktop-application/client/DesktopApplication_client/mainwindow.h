#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QtDataVisualization>
#include <QtNetwork>
#include "qcustomplot.h"
using namespace std;
using namespace QtDataVisualization;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void plot();
    void addPoints(double x, double y, double z);
    void startGraph();
    void set3dGraph();
    void set2dGraphs();



private slots:

    void realtimeDataSlot();
    void on_button2d_clicked();
    void on_button3d_clicked();
    void on_button23d_clicked();

    void on_startButton_clicked();
    void on_stopButton_clicked();




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



};
#endif // MAINWINDOW_H
