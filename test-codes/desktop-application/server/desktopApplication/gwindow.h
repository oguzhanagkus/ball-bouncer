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
    void on_pushButton_clicked();
    void loading();

private:
    QTimer * dataTimer;
    Ui::gWindow *ui;
    Q3DScatter *graph;
    QWidget *container;
    int loadLabelNumber = 0;
    MainWindow *mainwindow;

};

#endif // GWINDOW_H
