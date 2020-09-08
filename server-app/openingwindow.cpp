#include "openingwindow.h"
#include "ui_openingwindow.h"

/* -------------------------------------------------- */

gWindow::gWindow(QWidget *parent) : QWidget(parent), ui(new Ui::gWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Ball Bouncer - Server");

    initSerialPort();
    updateAvailablePortList();
    updateAvailableCameraList();

    controllerConnected = false;
    cameraConnected = false;
}

gWindow::~gWindow()
{
    serialPort.close();
    delete ui;
}

/* -------------------------------------------------- */

void gWindow::on_controllerList_activated(int index)
{
    serialPort.setPortName(portNames[index]);
}

void gWindow::on_controllerRefresh_clicked()
{
    if (serialPort.isOpen() == true)
    {
        controllerConnected = false;
        serialPort.close();
    }

    ui->controllerLabel->setText("Select controller!");
    ui->controllerLabel->setStyleSheet(whiteText);
    ui->controllerLabel->repaint();

    ui->controllerList->clear();
    portNames.clear();
    availablePorts.clear();
    updateAvailablePortList();
}

void gWindow::on_controllerConnect_clicked()
{
    char buffer[4];
    int bytes_read;

    bytes_read = 0;
    ui->controllerLabel->setText("Connecting...");
    ui->controllerLabel->setStyleSheet(yellowText);
    ui->controllerLabel->repaint();

    if (serialPort.isOpen() == true)
    {
        controllerConnected = false;
        serialPort.close();
    }

    if (serialPort.open(QIODevice::ReadWrite)) // Port opened
    {
        serialPort.write(key, sizeof (key)); // Send key

        if (serialPort.waitForReadyRead(5000)) // Wait for reply during 5 seconds
        {
            bytes_read = serialPort.read(buffer, sizeof (buffer)); // Read reply

            if (bytes_read == sizeof (buffer) && strcmp(buffer, key) == 0) // Check reply
            {

                ui->controllerLabel->setText("Connected!");
                ui->controllerLabel->setStyleSheet(greenText);
                ui->controllerLabel->repaint();

                controllerConnected = true;
            }
        }
    }

    if (!controllerConnected) // Cannot connect because of (one of) them: port cannot opened
    {
        if (serialPort.error() != QSerialPort::NoError) // Connection problem
        {
            // qDebug() << serialPort.error();
            ui->controllerLabel->setText("Error occured!");
            ui->controllerLabel->setStyleSheet(redText);
            ui->controllerLabel->repaint();
        }
        else // Authentication problem
        {
            serialPort.close();
            ui->controllerLabel->setText("Connection failed!");
            ui->controllerLabel->setStyleSheet(redText);
            ui->controllerLabel->repaint();
        }
    }
}

/* -------------------------------------------------- */

void gWindow::on_cameraList_activated(int index)
{
    setCameraIndex(index);
}

void gWindow::on_cameraRefresh_clicked()
{
    cameraConnected = false;

    ui->cameraLabel->setText("Select camera!");
    ui->cameraLabel->setStyleSheet(whiteText);
    ui->cameraLabel->repaint();

    ui->cameraList->clear();
    cameraNames.clear();
    availableCameras.clear();
    updateAvailableCameraList();
}

void gWindow::on_cameraConnect_clicked()
{
    // No availabilty check, if camera not available, it will exit in new window

    ui->cameraLabel->setText("Connected!");
    ui->cameraLabel->setStyleSheet(greenText);
    ui->cameraLabel->repaint();

    cameraConnected = true;
}

/* -------------------------------------------------- */

void gWindow::on_continueButton_clicked()
{
    if (!(controllerConnected && cameraConnected))
    {
        ui->statusLabel->setText("Make sure your devices are connected!");
        ui->statusLabel->setStyleSheet(redText);
        ui->statusLabel->repaint();
        return;
    }

    serialPort.close();
    mainwindow = new MainWindow(nullptr, serialPort.portName(), cameraIndex);
    mainwindow->show();
    this->close();
}

/* -------------------------------------------------- */

void gWindow::initSerialPort()
{
    serialPort.setBaudRate(QSerialPort::Baud9600);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);
}

void gWindow::updateAvailablePortList()
{
    availablePorts = QSerialPortInfo::availablePorts();

    if (availablePorts.size() == 0)
    {
        ui->controllerLabel->setText("No device detected!");
        ui->controllerLabel->setStyleSheet(redText);
        ui->controllerLabel->repaint();

        ui->controllerConnect->setEnabled(false);
    }
    else
    {
        for (int i = 0; i < availablePorts.size(); i++)
        {
            portNames.append(availablePorts[i].portName());
            ui->controllerList->addItem(availablePorts[i].description() + " (" + availablePorts[i].portName() + ")");
        }

        serialPort.setPortName(portNames[0]);
        ui->controllerConnect->setEnabled(true);
    }
}

void gWindow::updateAvailableCameraList()
{
    availableCameras = QCameraInfo::availableCameras();

    if (availableCameras.size() == 0)
    {
        ui->cameraLabel->setText("No camera detected!");
        ui->cameraLabel->setStyleSheet(redText);
        ui->cameraLabel->repaint();

        ui->cameraConnect->setEnabled(false);
    }
    else
    {
        for (int i = 0; i < availableCameras.size(); i++)
        {
            cameraNames.append(availableCameras[i].deviceName());
            ui->cameraList->addItem(availableCameras[i].description() + " (" + availableCameras[i].deviceName() + ")");
        }

        setCameraIndex(0);
        ui->cameraConnect->setEnabled(true);
    }
}

void gWindow::setCameraIndex(int index)
{
    #ifdef Q_OS_LINUX
        cameraIndex = QChar::digitValue(cameraNames[index].back().unicode());
    #elif defined(Q_OS_WIN32)
        cameraIndex = index;
    #endif
}

/* -------------------------------------------------- */
