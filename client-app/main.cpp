#include "mainwindow.h"
#include <cstdlib>
#include <QApplication>
#include <unistd.h>
#include <QtDataVisualization>

using namespace QtDataVisualization;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

