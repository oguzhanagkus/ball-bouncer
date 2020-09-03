#include "mainwindow.h"
#include<cstdlib>
#include <QApplication>
#include <unistd.h>
#include <QtDataVisualization>
#include "gwindow.h"
#include "ui_gwindow.h"
using namespace QtDataVisualization;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    gWindow w;
    w.show();


    return a.exec();
}

