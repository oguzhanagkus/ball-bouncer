#include "mainwindow.h"
#include "ui_mainwindow.h"

/* -------------------------------------------------- */

MainWindow::MainWindow(QWidget *parent, QString portName, int cameraIndex) : QMainWindow(parent), ui(new Ui::MainWindow), dt(0.0)
{
    ui->setupUi(this);
    this->setWindowTitle("Ball Bouncer - Server");

    initGraphs();
    initSimulation();
    initSerialPort(portName);
    initImageProcessing(cameraIndex);
    connectAllModules();
}

MainWindow::~MainWindow()
{
    serialPort.close();
    delete ui;
}

/* -------------------------------------------------- */

void MainWindow::plot()
{
    graph_xy->graph(0)->setData(qv_x, qv_y);
    graph_xy->graph(1)->setData(qv_x_previous_dropped, qv_y_previous_dropped);
    graph_xy->replot();
    graph_xy->update();

    graph_xz->graph(0)->setData(qv_x, qv_z);
    graph_xz->replot();
    graph_xz->update();
}

void MainWindow::addPoints(double y, double x, double z)
{
    // The first element of the vector gives the points
    qv_x.clear();
    qv_y.clear();
    qv_z.clear();
    qv_x.append(x);
    qv_y.append(y);
    qv_z.append(z);

    // Graph 0 is where the current information is kept
    graph_xy->graph(0)->setData(qv_y, qv_x);

    // Saving the previous position the ball dropped
    if (qv_z[0] == 0)
    {
        qv_x_previous_dropped.clear();
        qv_y_previous_dropped.clear();
        qv_x_previous_dropped.append(qv_y);
        qv_y_previous_dropped.append(qv_x);
        graph_xy->graph(1)->setData(qv_x_previous_dropped, qv_y_previous_dropped);
    }

    graph_xy->axisRect()->setupFullAxesBox();
    graph_xy->replot();
    graph_xy->update();

    graph_xz->graph(0)->setData(qv_y, qv_z);
    graph_xz->replot();
    graph_xz->update();

    qv_x_pre.push_back(x);
    qv_y_pre.push_back(y);
    qv_z_pre.push_back(z);

    for (int i = 0; i < pointCount; i++)
     {
        QScatterDataArray *data = new QScatterDataArray;
        *data << QVector3D(qv_y_pre.at(i), qv_z_pre.at(i), qv_x_pre.at(i));
        graph->seriesList().at(i)->dataProxy()->resetArray(data);
     }

    if (pointCount < numberOfGraphs)
    {
        pointCount++;
    }
    else
    {
        qv_x_pre.pop_front();
        qv_y_pre.pop_front();
        qv_z_pre.pop_front();
    }

    QString *str_x = new QString("Coordinates (x,y): ");
    str_x->append(QString::number(y));
    ui->label1->setText(*str_x);

    QString *str_xy = new QString(" , ");
    str_xy->append(QString::number(x));
    ui->label4->setText(*str_xy);

    QFont font("Bookman Old Style", 8);
    ui->label1->setFont(font);
    ui->label4->setFont(font);

    QString *str_y = new QString("Height: ");
    str_y->append(QString::number(z));
    ui->label2->setText(*str_y);
    ui->label2->setFont(font);
}

void MainWindow::set2dGraphs()
{
    QString *str_x = new QString("Coordinates (x,y): ");

    ui->label1->setText(*str_x);

    QFont font("Bookman Old Style", 8);

    ui->label1->setFont(font);
    ui->label4->setFont(font);

    QPixmap mypix ("./img/position.png");
    const int w =  ui->label1_img->width();
    const int h =  ui->label1_img->height();
    ui->label1_img->setPixmap(mypix.scaled(w,h,Qt::IgnoreAspectRatio));

    QString *str_y = new QString("Height: ");
    ui->label2->setText(*str_y);
    ui->label2->setFont(font);

    QPixmap mypix2 ("./img/height.png");
    const int w2 =  ui->label2_img->width();
    const int h2 =  ui->label2_img->height();
    ui->label2_img->setPixmap(mypix2.scaled(w2,h2,Qt::IgnoreAspectRatio));

    // XY graph
    // Set range
    graph_xy = new QCustomPlot();
    graph_xz = new QCustomPlot();
    graph_xy->xAxis->setRange(0, 640);
    graph_xy->yAxis->setRange(0, 480);

    // Set dark background gradient
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));

    graph_xy->setBackground(QColor(46, 52, 54));
    // Set labels
    graph_xy->xAxis->setLabel("X axis");
    graph_xy->yAxis->setLabel("Y axis");
    graph_xy->yAxis->setLabelFont(QFont("Bookman Old Style", 8));
    graph_xy->yAxis->setLabelColor(Qt::white);
    graph_xy->xAxis->setLabelColor(Qt::white);
    graph_xy->xAxis->setLabelFont(QFont("Bookman Old Style", 8));

    graph_xy->legend->setFont(QFont("Bookman Old Style", 8));
    graph_xy->legend->setRowSpacing(-3);
    graph_xy->legend->setTextColor(Qt::white);
    graph_xy->legend->setVisible(true);
    graph_xy->legend->setBrush(QBrush(gradient));

    graph_xy->xAxis->grid()->setVisible(true);
    graph_xy->yAxis->grid()->setVisible(true);

    // Making the font white
    graph_xy->xAxis->setBasePen(QPen(Qt::white, 1));
    graph_xy->yAxis->setBasePen(QPen(Qt::white, 1));
    graph_xy->xAxis->setTickPen(QPen(Qt::white, 1));
    graph_xy->yAxis->setTickPen(QPen(Qt::white, 1));
    graph_xy->xAxis->setSubTickPen(QPen(Qt::white, 1));
    graph_xy->yAxis->setSubTickPen(QPen(Qt::white, 1));
    graph_xy->xAxis->setTickLabelColor(Qt::white);
    graph_xy->yAxis->setTickLabelColor(Qt::white);

    // Adding two graphs
    graph_xy->addGraph(); //current location
    graph_xy->addGraph(); //last place the ball dropped

    // Setting properties of each graph
    graph_xy->graph(0)->rescaleAxes(true);
    graph_xy->graph(0)->setName("Current Position");
    graph_xy->graph(0)->setLineStyle(QCPGraph::lsLine);
    graph_xy->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    graph_xy->graph(0)->setPen(QPen(Qt::green));

    // ui->plot_x_y->graph(0)->setPen(QPen(QColor(128, 0, 255, 0)));

    graph_xy->graph(1)->rescaleAxes(true);
    graph_xy->graph(1)->setName("Previous Position");
    graph_xy->graph(1)->setLineStyle(QCPGraph::lsLine);
    graph_xy->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
    graph_xy->graph(1)->setPen(QPen(Qt::yellow));

    // XZ graph
    // Set range
    graph_xz->xAxis->setRange(0, 640);
    graph_xz->yAxis->setRange(0, 70);

    graph_xz->setBackground( QColor(46, 52, 54));
    // Set labels
    graph_xz->xAxis->setLabel("X axis");
    graph_xz->yAxis->setLabel("Z axis");
    graph_xz->yAxis->setLabelFont(QFont("Bookman Old Style", 8));
    graph_xz->yAxis->setLabelColor(Qt::white);
    graph_xz->xAxis->setLabelColor(Qt::white);
    graph_xz->xAxis->setLabelFont(QFont("Bookman Old Style", 8));

    graph_xz->legend->setFont(QFont("Bookman Old Style", 8));
    graph_xz->legend->setRowSpacing(-3);
    graph_xz->legend->setTextColor(Qt::white);
    graph_xz->legend->setVisible(true);
    graph_xz->legend->setSelectedTextColor(Qt::white);
    graph_xz->legend->setSelectedIconBorderPen(QPen(Qt::white, 1));
    graph_xz->legend->setBrush(QBrush(gradient));

    graph_xz->xAxis->grid()->setVisible(true);
    graph_xz->yAxis->grid()->setVisible(true);

    // Making the font white
    graph_xz->xAxis->setBasePen(QPen(Qt::white, 1));
    graph_xz->yAxis->setBasePen(QPen(Qt::white, 1));
    graph_xz->xAxis->setTickPen(QPen(Qt::white, 1));
    graph_xz->yAxis->setTickPen(QPen(Qt::white, 1));
    graph_xz->xAxis->setSubTickPen(QPen(Qt::white, 1));
    graph_xz->yAxis->setSubTickPen(QPen(Qt::white, 1));
    graph_xz->xAxis->setTickLabelColor(Qt::white);
    graph_xz->yAxis->setTickLabelColor(Qt::white);

    // Adding one graph
    graph_xz->addGraph(); // Current location

    // Setting properties of each graph
    graph_xz->graph(0)->rescaleAxes(true);
    graph_xz->graph(0)->setName("Current Position");
    graph_xz->graph(0)->setLineStyle(QCPGraph::lsLine);
    graph_xz->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    graph_xz->graph(0)->setPen(QPen(Qt::green));
}

void MainWindow::set3dGraph()
{
    cameraImage = new QLabel();

    Q3DTheme *a =new Q3DTheme();
    a->setBackgroundColor( QColor(46, 52, 54));

    QList<QColor> *q =new QList<QColor>();

    int r = 199;
    int g = 0;
    int b = 233;
    int o = 0;

    for (int i = 0; i < numberOfGraphs; i++)
    {
        if (QColor(r, g, b, o).isValid() == true)
        {
            QColor *nColor = new QColor(r, g, b, o);
            q->append(*nColor);
        }
        else
        {
            printf("Color not valid");
        }

        r = r+(255-r) * 0.20;
        g = g+(255-g) * 0.20;
        b = b+(255-b) * 0.20;
        o = o+(255-o) * 0.20;
    }

    QList<QColor> *q2 = new QList<QColor>();

    for (int i = numberOfGraphs - 1; i >= 0; i--)
    {
        q2->append(q->at(i));
    }

    a->setBaseColors(*q2);

    // Black background
    a->setLightColor(QColor(136, 138, 133));

    // QColor(136, 138, 133)
    a->setWindowColor( QColor(46, 52, 54));
    a->setGridLineColor(Qt::white);
    a->setLabelTextColor(Qt::white);
    a->setMultiHighlightColor(Qt::white);
    a->setBackgroundColor( QColor(46, 52, 54));
    a->setLabelBackgroundColor( QColor(46, 52, 54));
    a->setSingleHighlightColor(Qt::white );

    //QColor(238, 238, 236)
    a->setFont(QFont("Bookman Old Style", 8));
    a->setLabelBorderEnabled(true);
    a->setGridEnabled(true);
    a->setLabelBorderEnabled(true);
    a->setLabelBackgroundEnabled(true);

    QStringList *list = new QStringList();

    graph->axisX()->setLabels(*list);
    graph->axisX()->setTitleVisible(true);

    graph->addTheme(a);
    graph->setActiveTheme(a);
    graph->setMaximumWidth(100);
    graph->setMaximumHeight(100);

    graph->axisX()->setRange(0,640);
    graph->axisY()->setRange(0,70);
    graph->axisZ()->setRange(0,480);
    graph->axisX()->setTitle("X axis");
    graph->axisY()->setTitle("Z axis");
    graph->axisZ()->setTitle("Y axis");
    graph->show();
}

void MainWindow::GraphContainer()
{
    graph = new Q3DScatter();
    container = QWidget::createWindowContainer(graph);

    for (int i = 0; i < numberOfGraphs; i++)
    {
        graph->addSeries(new QScatter3DSeries);
    }
}

/* -------------------------------------------------- */

void MainWindow::on_button2d_clicked()
{
    if (currentViewType == view_3d)
    {
        // Rremove 3d
        container->close();
        ui->layout->removeWidget(container);
        ui->button3d->setEnabled(true);
    }
    else if (currentViewType == view_all)
    {
        // Remove 3D
        container->close();
        ui->layout->removeWidget(container);

        // Remove 2D
        ui->layout->removeWidget(graph_xy);
        ui->layout->removeWidget(graph_xz);
        ui->button23d->setEnabled(true);
    }

    if (currentViewType != view_2d)
    {
        // Add 2D
        set2dGraphs();
        ui->layout->addWidget(graph_xy,0,0, Qt::Alignment());
        ui->layout->addWidget(graph_xz,0,1, Qt::Alignment());

        currentViewType=view_2d;
        ui->button2d->setEnabled(false);
    }
}

void MainWindow::on_button3d_clicked()
{
    if (currentViewType == view_2d)
    {
        // Remove 2d
        ui->layout->removeWidget(graph_xy);
        ui->layout->removeWidget(graph_xz);
        ui->button2d->setEnabled(true);
    }
    else if (currentViewType == view_all)
    {
        // Remove 3d
        container->close();
        ui->layout->removeWidget(container);

        // Remove 2d
        ui->layout->removeWidget(graph_xy);
        ui->layout->removeWidget(graph_xz);
        ui->button23d->setEnabled(true);
    }

    if (currentViewType!=view_3d)
    {
        // Add 3D
        GraphContainer();
        ui->layout->addWidget(container);
        set3dGraph();
        currentViewType=view_3d;
        ui->button3d->setEnabled(false);
    }
}

void MainWindow::on_button23d_clicked()
{
    if (currentViewType == view_2d)
    {
        // Remove 2D
        ui->layout->removeWidget(graph_xy);
        ui->layout->removeWidget(graph_xz);
        ui->button2d->setEnabled(true);
    }
    else if (currentViewType == view_3d)
    {
        // Remove 3D
        container->close();
        ui->layout->removeWidget(container);
        ui->button3d->setEnabled(true);
    }

    if (currentViewType != view_all)
    {
        // Add 2D
        set2dGraphs();
        ui->layout->addWidget(graph_xy, 0, 0, Qt::Alignment());
        ui->layout->addWidget(graph_xz, 1, 0, Qt::Alignment());

        currentViewType=view_all;
        ui->button23d->setEnabled(false);

        // Add 3D
        GraphContainer();
        ui->layout->addWidget(container,0, 1, 2, 2, Qt::Alignment());
        set3dGraph();
    }
}

/* -------------------------------------------------- */

void MainWindow::on_balance_button_clicked()
{
    mOpencv_colorTracker->flag = 1;
    ui->circle_button->setEnabled(false);
    ui->stop_button->setEnabled(true);
}

void MainWindow::on_circle_button_clicked()
{
    mOpencv_colorTracker->flag = 2;
    ui->balance_button->setEnabled(false);
    ui->stop_button->setEnabled(true);
}

void MainWindow::on_stop_button_clicked()
{
    mOpencv_colorTracker->flag = 0;
    ui->balance_button->setEnabled(true);
    ui->circle_button->setEnabled(true);
    ui->stop_button->setEnabled(false);
}

/* -------------------------------------------------- */

void MainWindow::sendDatagram()
{
    message.clear();
    message.append(QString::number(x_img));
    message.append("-");
    message.append(QString::number(y_img));
    message.append("-");
    message.append(QString::number(height_img));
    message.append("-");
    // std::string => QByteArray
    QByteArray datagram(message.toUtf8());

    udpServer.writeDatagram(datagram, QHostAddress::Broadcast, 5555);
    datagram.clear();
}

void MainWindow::dataFromImageProcesssing()
{

}

/* -------------------------------------------------- */

void MainWindow::changeAngleRobot1()
{
    angle_robot1 = orj_angle_robot1 - 90;

    if (angle_robot1 - robot1->getTh1() >= 1)
    {
        robot1->setTh1(robot1->getTh1() + 1);
    }
    else if (angle_robot1 - robot1->getTh1() <= -1)
    {
        robot1->setTh1(robot1->getTh1() - 1);
    }
    else if ((-1 < (angle_robot1 - robot1->getTh1())) && ((angle_robot1 - robot1->getTh1()) < 1))
    {
        flag_robot1 = 1;
    }

    angle2_robot1 = 90 - ((orj_angle_robot1) / 1);

    if (angle2_robot1 - robot1->getTh2() >= 1)
    {
        robot1->setTh2(robot1->getTh2()+1);
    }
    else if (angle2_robot1 - robot1->getTh2() <= -1)
    {
        robot1->setTh2(robot1->getTh2() - 1);
    }
    else if ((-1 < (angle2_robot1 - robot1->getTh2())) && ((angle2_robot1 - robot1->getTh2()) < 1))
    {
        flag2_robot1 = 1;
    }

    angle3_robot1 = 90;

    if (angle3_robot1 - robot1->getTh3() >= 1)
    {
        robot1->setTh3(robot1->getTh3() + 1);
    }
    else if (angle3_robot1 - robot1->getTh3() <= -1)
    {
        robot1->setTh3(robot1->getTh3() - 1);
    }
    else if ((-1 < (angle3_robot1 - robot1->getTh3())) && ((angle3_robot1 - robot1->getTh3()) < 1))
    {
        flag3_robot1 = 1;
    }

    if (flag_robot1 == 1 && flag2_robot1 == 1 && flag3_robot1 == 1)
    {
        timer_robot1.stop();
    }
}

void MainWindow::changeAngleRobot2()
{
    angle_robot2 = orj_angle_robot2 - 90;

    if (angle_robot2 - robot2->getTh1() >= 1)
    {
        robot2->setTh1(robot2->getTh1() + 1);
    }
    else if (angle_robot2 - robot2->getTh1() <= -1)
    {
        robot2->setTh1(robot2->getTh1() - 1);
    }
    else if ((-1 < (angle_robot2 - robot2->getTh1())) && ((angle_robot2 - robot2->getTh1()) < 1))
    {
        flag_robot2 = 1;
    }

    angle2_robot2 = 90 -  ((orj_angle_robot2) / 1);

    if (angle2_robot2 - robot2->getTh2() >= 1)
    {
        robot2->setTh2(robot2->getTh2() + 1);
    }
    else if (angle2_robot2 - robot2->getTh2() <= -1)
    {
        robot2->setTh2(robot2->getTh2() - 1);
    }
    else if ((-1 < (angle2_robot2 - robot2->getTh2())) && ((angle2_robot2 - robot2->getTh2()) < 1))
    {
        flag2_robot2 = 1;
    }

    angle3_robot2 = 90;

    if (angle3_robot2 - robot2->getTh3() >= 1)
    {
        robot2->setTh3(robot2->getTh3() + 1);
    }
    else if (angle3_robot2 - robot2->getTh3() <= -1)
    {
        robot2->setTh3(robot2->getTh3() - 1);
    }
    else if ((-1<(angle3_robot2 - robot2->getTh3())) && ((angle3_robot2 - robot2->getTh3()) < 1))
    {
        flag3_robot2 = 1;
    }

    if (flag_robot2 == 1 && flag2_robot2 == 1 && flag3_robot2 == 1)
    {
        flag_robot2 = 0;
        flag3_robot2 = 0;
        flag2_robot2 = 0;
        timer_robot2.stop();
    }
}

void MainWindow::changeAngleRobot3()
{
    angle_robot3 = orj_angle_robot3 - 90;

    if (angle_robot3 - robot3->getTh1() >= 1)
    {
        robot3->setTh1(robot3->getTh1() + 1);
    }
    else if (angle_robot3 - robot3->getTh1() <= -1)
    {
        robot3->setTh1(robot3->getTh1()-1);
    }
    else if ((-1 < (angle_robot3 - robot3->getTh1())) && ((angle_robot3 - robot3->getTh1()) < 1))
    {
        flag_robot3 = 1;
    }

    angle2_robot3 = 90 - ((orj_angle_robot3) / 1);

    if (angle2_robot3 - robot3->getTh2() >= 1)
    {
        robot3->setTh2(robot3->getTh2()+1);
    }
    else if (angle2_robot3 - robot3->getTh2() <= -1)
    {
        robot3->setTh2(robot3->getTh2() - 1);
    }
    else if ((-1 < (angle2_robot3 - robot3->getTh2())) && ((angle2_robot3 - robot3->getTh2()) < 1))
    {
        flag2_robot3 = 1;
    }

    angle3_robot3 = 90 ;

    if (angle3_robot3 - robot3->getTh3() >= 1)
    {
        robot3->setTh3(robot3->getTh3() + 1);
    }
    else if (angle3_robot3 - robot3->getTh3() <= -1)
    {
        robot3->setTh3(robot3->getTh3() - 1);
    }
    else if ((-1 < (angle3_robot3 - robot3->getTh3())) && ((angle3_robot3 - robot3->getTh3()) < 1))
    {
        flag3_robot3 = 1;
    }

    if (flag_robot3 == 1 && flag2_robot3 == 1 && flag3_robot3 == 1)
    {
        flag_robot3=0;
        flag3_robot3=0;
        flag2_robot3=0;
        timer_robot3.stop();
    }
}

void MainWindow::changeAngleRobot4()
{
    angle_robot4 = orj_angle_robot4 - 90;

    if (angle_robot4 - robot4->getTh1() >= 1)
    {
        robot4->setTh1(robot4->getTh1() + 1);
    }
    else if (angle_robot4 - robot4->getTh1() <= -1)
    {
        robot4->setTh1(robot4->getTh1() - 1);
    }
    else if ((-1 < (angle_robot4 - robot4->getTh1())) && ((angle_robot4 - robot4->getTh1()) < 1))
    {
        flag_robot4 = 1;
    }

    angle2_robot4 = 90 - ((orj_angle_robot4) / 1);

    if (angle2_robot4 - robot4->getTh2() >= 1)
    {
        robot4->setTh2(robot4->getTh2() + 1);
    }
    else if (angle2_robot4 - robot4->getTh2() <= -1)
    {
        robot4->setTh2(robot4->getTh2() - 1);
    }
    else if ((-1 < (angle2_robot4 - robot4->getTh2())) && ((angle2_robot4 - robot4->getTh2()) < 1))
    {
        flag2_robot4 = 1;
    }

    angle3_robot4 = 90;

    if (angle3_robot4 - robot4->getTh3() >= 1)
    {
        robot4->setTh3(robot4->getTh3() + 1);
    }
    else if (angle3_robot4 - robot4->getTh3() <= -1)
    {
        robot4->setTh3(robot4->getTh3() - 1);
    }
    else if ((-1 < (angle3_robot4 - robot4->getTh3())) && ((angle3_robot4 - robot4->getTh3()) < 1))
    {
        flag3_robot4 = 1;
    }

    if (flag_robot4 == 1 && flag2_robot4 == 1 && flag3_robot4 == 1)
    {
        flag_robot4 = 0;
        flag3_robot4 = 0;
        flag2_robot4 = 0;
        timer_robot4.stop();
    }
}

void MainWindow::giveArmsAngle(double degree_arm3, double degree_arm4, double degree_arm1, double degree_arm2)
{
    orj_angle_robot1 = degree_arm1;
    orj_angle_robot2 = degree_arm2;
    orj_angle_robot3 = degree_arm3;
    orj_angle_robot4 = degree_arm4;

    connect(&timer_robot1, SIGNAL(timeout()), this, SLOT(changeAngleRobot1()));
    timer_robot1.setInterval(0);
    timer_robot1.start();

    connect(&timer_robot2, SIGNAL(timeout()), this, SLOT(changeAngleRobot2()));
    timer_robot2.setInterval(0);
    timer_robot2.start();

    connect(&timer_robot3, SIGNAL(timeout()), this, SLOT(changeAngleRobot3()));
    timer_robot3.setInterval(0);
    timer_robot3.start();

    connect(&timer_robot4, SIGNAL(timeout()), this, SLOT(changeAngleRobot4()));
    timer_robot4.setInterval(0);
    timer_robot4.start();
}

void MainWindow::changeBallsCoordinates(double x, double y, double z)
{
    Plate->changeLocation(x * 0.1, y * 0.1, z * 0.1);
}

void MainWindow::go()
{
    dt = 1.0 * (clock() - clk) / CLOCKS_PER_SEC;
    clk = clock();
    t += dt;

    robot1->go(dt);

    ui->view->updateGL();
}

/* -------------------------------------------------- */

void MainWindow::initGraphs()
{
    // Initializazes the 2D graphs
    set2dGraphs();

    // Initializazes the 3D graph
    GraphContainer();
    ui->layout->addWidget(container);
    set3dGraph();

    // 3D image is on at first
    ui->button3d->setEnabled(false);
}

void MainWindow::initSimulation()
{
    connect(&tmr, SIGNAL(timeout()), this, SLOT(go()));
    tmr.setInterval(0);
    tmr.start();

    robot1 = new Scara(this);
    robot2 = new Scara(this);
    robot3 = new Scara(this);
    robot4 = new Scara(this);
}

void MainWindow::initSerialPort(QString portName)
{
    serialPort.setPortName(portName);
    serialPort.setBaudRate(QSerialPort::Baud57600);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);
    serialPort.open(QIODevice::ReadWrite);
}

void MainWindow::initImageProcessing(int cameraIndex)
{
    cameraImage = new QLabel();

    // Connecting camera image, when new frame comes updates the window
    mOpencv_colorTracker = new colorTracker(this, cameraIndex);

    connect(mOpencv_colorTracker, &colorTracker::newPixmapCaptured, this, [&]()
    {
        cameraImage->setPixmap(mOpencv_colorTracker->pixmap().scaled(360,270));
        ui->image->setPixmap(mOpencv_colorTracker->pixmap().scaled(360,270));
    });

    container2 = new QWidget(cameraImage);

    // Gives highest priority to the image processing thread
    mOpencv_colorTracker->start();
}

void MainWindow::connectAllModules()
{
    // Conncecting image processing where the image is processed and the x,y,z values are retrieved
    // Signals the main window. The slot adds points to the graph and brodcasts data
    connect(mOpencv_colorTracker, &colorTracker::dataFromImageProcessing, this, [&]()
    {
        Command temp;
        int temp_flag;

        temp_flag = mOpencv_colorTracker->flag;
        if (temp_flag == 0)
        {
            mOpencv_colorTracker->flag = -1;
        }

        x_img = mOpencv_colorTracker->x;
        y_img = mOpencv_colorTracker->y;
        height_img = mOpencv_colorTracker->height;

        memcpy(&temp, &mOpencv_colorTracker->command, sizeof (temp));

        sendDatagram();
        addPoints(x_img,y_img,height_img);

        if (temp_flag != -1)
        {
            serialPort.write((char *) &temp, sizeof(temp));
            giveArmsAngle(temp.angle_0 - 5, temp.angle_1, temp.angle_2, temp.angle_3 - 10);
        }
    });
}

/* -------------------------------------------------- */
