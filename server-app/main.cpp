#include "openingwindow.h"
#include "ui_openingwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    gWindow window;

    window.show();

    return application.exec();
}

