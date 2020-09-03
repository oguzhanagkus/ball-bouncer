#include "mainwindow.h"
#include "ui_mainwindow.h"

/* -------------------------------------------------- */

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Ball Bouncer - Client");

    dataTimer = new QTimer(this);

    udpClient.bind(5555, QUdpSocket::ShareAddress);
    connect(&udpClient, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));

    // 3D plot image
    set2dGraphs();

    GraphContainer();
    ui->layout->addWidget(container);
    set3dGraph();

    // 3D image is on at first
    ui->button3d->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* -------------------------------------------------- */

void MainWindow::plot()
{
    graph_xy->graph(0)->setData(qv_x,qv_y);
    graph_xy->graph(1)->setData(qv_x_previous_dropped,qv_y_previous_dropped);
    graph_xy->replot();
    graph_xy->update();

    graph_xz->graph(0)->setData(qv_x,qv_z);
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
            qInfo() << "Color not valid";
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

void MainWindow::addNewPointToGraphs(QString message)
{
    // Split message
    QStringList list = message.split("-");
    QString x_coor = list[0];
    QString y_coor = list[1];
    QString z_coor = list[2];

    // std::cout << " X = "<< x_coor.toDouble();
    // (x,y,z) -> sağ-sol, yukarı-aşağı, ileri-geri
    addPoints(x_coor.toDouble(),y_coor.toDouble(),z_coor.toDouble());
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
        // Remove 3D
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
        // Remove 2D
        ui->layout->removeWidget(graph_xy);
        ui->layout->removeWidget(graph_xz);
        ui->button2d->setEnabled(true);
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

    if (currentViewType != view_3d)
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
        ui->layout->addWidget(graph_xy,0,0, Qt::Alignment());
        ui->layout->addWidget(graph_xz,1,0, Qt::Alignment());
        currentViewType=view_all;
        ui->button23d->setEnabled(false);

        // Add 3D
        GraphContainer();
        ui->layout->addWidget(container,0,1,2,2,Qt::Alignment());
        set3dGraph();

    }
}

/* -------------------------------------------------- */

void MainWindow::processPendingDatagrams()
{
    QByteArray datagram;
    do
    {
        datagram.resize(udpClient.pendingDatagramSize());
        udpClient.readDatagram(datagram.data(), datagram.size());
        // QByteArray => std::string
        string stdString(datagram.constData(), datagram.length());
        QString message(QString::fromStdString(stdString));
        addNewPointToGraphs(message);
    } while (udpClient.hasPendingDatagrams());
}

/* -------------------------------------------------- */
