#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <unistd.h>
#include<QList>
#include <math.h>
#include <QtDataVisualization>
#define PI 3.14159265
using namespace QtDataVisualization;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dataTimer = new QTimer(this);

    //3d plot image
    set2dGraphs();
    set3dGraph();

}

MainWindow::~MainWindow()
{
    delete ui;
}

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

void MainWindow::addPoints(double x, double y, double z)
{
      qv_x.clear();
      qv_y.clear();
      qv_z.clear();

      qv_x.append(x);
      qv_y.append(y);
      qv_z.append(z);

      graph_xy->graph(0)->setData(qv_x, qv_y);

      if(qv_z[0] == 0){

          qv_x_previous_dropped.clear();
          qv_y_previous_dropped.clear();
          qv_x_previous_dropped.append(qv_x);
          qv_y_previous_dropped.append(qv_y);
          graph_xy->graph(1)->setData(qv_x_previous_dropped, qv_y_previous_dropped);
      }

      graph_xy->axisRect()->setupFullAxesBox();
      graph_xy->replot();
      graph_xy->update();

      graph_xz->graph(0)->setData(qv_x, qv_z);
      graph_xz->replot();
      graph_xz->update();

      qv_x_pre.push_back(x);
      qv_y_pre.push_back(y);
      qv_z_pre.push_back(z);

      for(int i=0;i<pointCount;i++){ //max 20
          QScatterDataArray *data = new QScatterDataArray;
          *data << QVector3D(qv_x_pre.at(i), qv_z_pre.at(i),qv_y_pre.at(i)); //?????
          graph->seriesList().at(i)->dataProxy()->resetArray(data);
      }
      if(pointCount < numberOfGraphs){//20
          pointCount++;
      }else{
          qv_x_pre.pop_front();
          qv_y_pre.pop_front();
          qv_z_pre.pop_front();
      }

      QString * str_x = new QString("Coordinates (x,y): ");
      str_x->append(QString::number(x));

      ui->label1->setText(*str_x);

      ui->label1->setStyleSheet("QLabel { background-color : black; color : white; }");
      QString * str_xy = new QString(" , ");
      str_xy->append(QString::number(y));
      ui->label4->setText(*str_xy);
      QFont font("Bookman Old Style", 8);

      ui->label1->setFont(font);
      ui->label4->setFont(font);

      QPixmap mypix (":/position.png");
      const int w =  ui->label1_img->width();
      const int h =  ui->label1_img->height();
      ui->label1_img->setPixmap(mypix.scaled(w,h,Qt::IgnoreAspectRatio));

      QString * str_y = new QString("Height: ");
      str_y->append(QString::number(y));
      ui->label2->setText(*str_y);
      ui->label2->setStyleSheet("QLabel { background-color : black; color : white; }");
      ui->label2->setFont(font);

      QPixmap mypix2 (":/height.png");
      const int w2 =  ui->label2_img->width();
      const int h2 =  ui->label2_img->height();
      ui->label2_img->setPixmap(mypix2.scaled(w2,h2,Qt::IgnoreAspectRatio));


      QString * str_z = new QString("Radius: ");
      str_z->append(QString::number(ballRadius));
      ui->label3->setText(*str_z);
      ui->label3->setStyleSheet("QLabel { background-color : black; color : white; }");
      ui->label3->setFont(font);

      QPixmap mypix3 (":/radius.png");
      const int w3 =  ui->label3_img->width();
      const int h3 =  ui->label3_img->height();
      ui->label3_img->setPixmap(mypix3.scaled(w3,h3,Qt::IgnoreAspectRatio));
}

void MainWindow::startGraph()
{
    //Sends realtimeDataSlot a signal as quick as possible (0's meaning)
    connect(dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer->start(50);
    //   QTimer::singleShot(200, this, SLOT(realtimeDataSlot()));
}

void MainWindow::set3dGraph()
{
    graph = new Q3DScatter();

    container = QWidget::createWindowContainer(graph);
    for(int i=0;i<numberOfGraphs;i++){
        graph->addSeries(new QScatter3DSeries);
    }

    ui->layout->addWidget(container,1);
    Q3DTheme * a =new Q3DTheme();
    a->setBackgroundColor(Qt::black);

    QList<QColor>*  q =new QList<QColor>();

    int r = 199;
    int g = 0;
    int b = 233;
    int o = 0;
    for(int i=0; i<numberOfGraphs;i++){
        if(QColor(r, g, b, o).isValid() == true){
            QColor * nColor = new QColor(r, g, b, o);
            q->append(*nColor);

        }else{
            printf("Color not valid");
        }
        r = r+(255-r)*0.12;
        g = g+(255-g)*0.12;
        b = b+(255-b)*0.12;
        o = o+(255-o)*0.12;
    }
    QList<QColor>*  q2 =new QList<QColor>();
    for(int i=numberOfGraphs-1; i>=0;i--){
        q2->append(q->at(i));
    }

    a->setBaseColors(*q2);

    //black background
    a->setLightColor(Qt::white);
    a->setWindowColor(Qt::black);
    a->setGridLineColor(Qt::white);
    a->setLabelTextColor(Qt::white);
    a->setMultiHighlightColor(Qt::white);
    a->setBackgroundColor(Qt::black);
    a->setLabelBackgroundColor(Qt::black);
    a->setSingleHighlightColor(Qt::white);

    a->setFont(QFont("Bookman Old Style", 8));
    a->setLabelBorderEnabled(true);
    a->setGridEnabled(true);
    a->setLabelBorderEnabled(true);
    a->setLabelBackgroundEnabled(true);

    QStringList * list = new QStringList();
    list->append("X axis");

    graph->axisX()->setLabels(*list);
    graph->axisX()->setTitle("X axis");
    graph->axisX()->setTitleVisible(true);

    graph->addTheme(a);
    graph->setActiveTheme(a);
    graph->setMaximumWidth(100);
    graph->setMaximumHeight(100);

    graph->axisX()->setRange(-100,100);
    graph->axisY()->setRange(0,200);
    graph->axisZ()->setRange(-100,100);
    graph->show();
}

void MainWindow::set2dGraphs()
{
  /*  graph_xy = new QCustomPlot();
    graph_xz = new QCustomPlot();
    container2 = QWidget::createWindowContainer(graph_xy);

    ui->layout3dImage->addWidget(container,1);
    */
    // x-y graph
    //set range

    graph_xy = new QCustomPlot();
    graph_xz = new QCustomPlot();
    graph_xy->xAxis->setRange(0,20);
    graph_xy->yAxis->setRange(0,20);

    // set dark background gradient
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
   // ui->plot_x_y->setBackground(QBrush(gradient));

    graph_xy->setBackground(Qt::black);
    //set labels
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

    //Making the font white
    graph_xy->xAxis->setBasePen(QPen(Qt::white, 1));
    graph_xy->yAxis->setBasePen(QPen(Qt::white, 1));
    graph_xy->xAxis->setTickPen(QPen(Qt::white, 1));
    graph_xy->yAxis->setTickPen(QPen(Qt::white, 1));
    graph_xy->xAxis->setSubTickPen(QPen(Qt::white, 1));
    graph_xy->yAxis->setSubTickPen(QPen(Qt::white, 1));
    graph_xy->xAxis->setTickLabelColor(Qt::white);
    graph_xy->yAxis->setTickLabelColor(Qt::white);

    //adding two graphs
    graph_xy->addGraph(); //current location
    graph_xy->addGraph(); //last place the ball dropped

    //setting properties of each graph
    graph_xy->graph(0)->rescaleAxes(true);
    graph_xy->graph(0)->setName("Current Position");
    graph_xy->graph(0)->setLineStyle(QCPGraph::lsLine);
    graph_xy->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    graph_xy->graph(0)->setPen(QPen(Qt::green));

    //ui->plot_x_y->graph(0)->setPen(QPen(QColor(128, 0, 255, 0)));

    graph_xy->graph(1)->rescaleAxes(true);
    graph_xy->graph(1)->setName("Previous Position");
    graph_xy->graph(1)->setLineStyle(QCPGraph::lsLine);
    graph_xy->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
    graph_xy->graph(1)->setPen(QPen(Qt::yellow));


    //x-z graph
    //set range
    graph_xz->xAxis->setRange(0,20);
    graph_xz->yAxis->setRange(0,200);

    //set dark background gradient
    //ui->plot_x_z->setBackground(QBrush(gradient));

    graph_xz->setBackground(Qt::black);
    //set labels
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

    //Making the font white
    graph_xz->xAxis->setBasePen(QPen(Qt::white, 1));
    graph_xz->yAxis->setBasePen(QPen(Qt::white, 1));
    graph_xz->xAxis->setTickPen(QPen(Qt::white, 1));
    graph_xz->yAxis->setTickPen(QPen(Qt::white, 1));
    graph_xz->xAxis->setSubTickPen(QPen(Qt::white, 1));
    graph_xz->yAxis->setSubTickPen(QPen(Qt::white, 1));
    graph_xz->xAxis->setTickLabelColor(Qt::white);
    graph_xz->yAxis->setTickLabelColor(Qt::white);

    // adding one graph
    graph_xz->addGraph(); //current location

    //setting properties of each graph
    graph_xz->graph(0)->rescaleAxes(true);
    graph_xz->graph(0)->setName("Current Position");

    graph_xz->graph(0)->setLineStyle(QCPGraph::lsLine);
    graph_xz->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    graph_xz->graph(0)->setPen(QPen(Qt::green));


}

void MainWindow::realtimeDataSlot()
{

        addPoints(x+5,5,x*x);
        if(x == 12){
            flag = 1;
        }else if(x == 0){
            flag = 0;
        }
        if(flag == 0){
            x=x+0.5;
        }else{
            x=x-0.5;
        }
}



void MainWindow::on_button2d_clicked()
{

    if(flag3d == 1 ) {
        container->close();
        ui->layout->removeWidget(container);
        set2dGraphs();
        ui->layout->addWidget(graph_xy);
        ui->layout->addWidget(graph_xz);
        flag3d = 0;
    } else if(flag3d == 2){
        container->close();
        ui->layout->removeWidget(container);
        flag3d = 0;
    }
}

void MainWindow::on_button3d_clicked()
{

    if(flag3d == 0){
        ui->layout->removeWidget(graph_xy);
        ui->layout->removeWidget(graph_xz);
        set3dGraph();
        flag3d= 1;
     }else if(flag3d == 2){
        ui->layout->removeWidget(graph_xy);
        ui->layout->removeWidget(graph_xz);
        flag3d = 1;
    }
}

void MainWindow::on_button23d_clicked()
{
    if(flag3d == 0){
        ui->layout->removeWidget(graph_xy);
        ui->layout->removeWidget(graph_xz);
        set2dGraphs();
        ui->layout->addWidget(graph_xy);
        ui->layout->addWidget(graph_xz);
        set3dGraph();
        ui->layout->setStretch(0,7);
        ui->layout->setStretch(1,7);
        ui->layout->setStretch(2,15);
        flag3d= 2;
    }else if(flag3d == 1){
        container->close();
         ui->layout->removeWidget(container);
         set2dGraphs();
         ui->layout->addWidget(graph_xy);
         ui->layout->addWidget(graph_xz);
         set3dGraph();
         ui->layout->setStretch(0,7);
         ui->layout->setStretch(1,7);
         ui->layout->setStretch(2,15);
         flag3d= 2;
    }
}

