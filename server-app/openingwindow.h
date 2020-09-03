#ifndef OPENINGWINDOW_H
#define OPENINGWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCamera>
#include <QCameraInfo>
#include <QSerialPort>
#include <QSerialPortInfo>

// Colors
#define whiteText "color: rgb(238, 238, 236)"
#define yellowText "color: rgb(196, 160, 0)"
#define greenText "color: rgb(78, 154, 6)"
#define redText "color: rgb(164, 0, 0)"

QT_BEGIN_NAMESPACE
namespace Ui { class gWindow; }
QT_END_NAMESPACE

class gWindow : public QWidget
{
    Q_OBJECT

public:
    explicit gWindow(QWidget *parent = nullptr);
    ~gWindow();

signals:
    void firstWindow();

private slots:
    void on_controllerList_activated(int index);
    void on_controllerRefresh_clicked();
    void on_controllerConnect_clicked();

    void on_cameraList_activated(int index);
    void on_cameraRefresh_clicked();
    void on_cameraConnect_clicked();

    void on_continueButton_clicked();

private:
    void initSerialPort();
    void updateAvailablePortList();
    void updateAvailableCameraList();
    void setCameraIndex(int index);

private:
    Ui::gWindow *ui;
    MainWindow *mainwindow;

    QStringList portNames;
    QList<QSerialPortInfo> availablePorts;
    QSerialPort serialPort;

    QStringList cameraNames;
    QList<QCameraInfo> availableCameras;

    int cameraIndex;
    bool controllerConnected;
    bool cameraConnected;
};

#endif // OPENINGWINDOW_H
