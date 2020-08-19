#ifndef GWINDOW_H
#define GWINDOW_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QtDataVisualization>
using namespace QtDataVisualization;
namespace Ui {
class gWindow;
}

class gWindow : public QWidget
{
    Q_OBJECT

public:
    explicit gWindow(QWidget *parent = nullptr);
    ~gWindow();
signals:
    void firstWindow();

private slots:
    void loading();

    void on_pushButton_clicked();

public slots:
    void processPendingDatagrams();
private:
    QTimer * dataTimer;
    Ui::gWindow *ui;
    Q3DScatter *graph;
    QWidget *container;
    int loadLabelNumber = 0;
    MainWindow *mainwindow;
    QUdpSocket udpClient;
    QTimer timer;

};

#endif // GWINDOW_H
