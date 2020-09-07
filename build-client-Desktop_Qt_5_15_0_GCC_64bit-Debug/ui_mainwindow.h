/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *button2d;
    QPushButton *button3d;
    QPushButton *button23d;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame_2;
    QLabel *label_3;
    QLabel *label1_img;
    QLabel *label2_img;
    QLabel *label1;
    QLabel *label2;
    QLabel *label4;
    QWidget *gridLayoutWidget;
    QGridLayout *layout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1080, 720);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(40, 630, 1000, 50));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(200, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        button2d = new QPushButton(frame);
        button2d->setObjectName(QString::fromUtf8("button2d"));
        button2d->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        horizontalLayout->addWidget(button2d);

        button3d = new QPushButton(frame);
        button3d->setObjectName(QString::fromUtf8("button3d"));
        button3d->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        horizontalLayout->addWidget(button3d);

        button23d = new QPushButton(frame);
        button23d->setObjectName(QString::fromUtf8("button23d"));
        button23d->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        horizontalLayout->addWidget(button23d);

        horizontalSpacer_2 = new QSpacerItem(200, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(40, 560, 1000, 50));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(720, 10, 30, 30));
        label_3->setStyleSheet(QString::fromUtf8("font: 10pt \"Bookman Old Style\";\n"
"color: rgb(255, 255, 255);"));
        label1_img = new QLabel(frame_2);
        label1_img->setObjectName(QString::fromUtf8("label1_img"));
        label1_img->setGeometry(QRect(260, 10, 30, 30));
        label2_img = new QLabel(frame_2);
        label2_img->setObjectName(QString::fromUtf8("label2_img"));
        label2_img->setGeometry(QRect(570, 10, 30, 30));
        label1 = new QLabel(frame_2);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setGeometry(QRect(300, 10, 141, 30));
        label1->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label2 = new QLabel(frame_2);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(610, 10, 110, 30));
        label2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label4 = new QLabel(frame_2);
        label4->setObjectName(QString::fromUtf8("label4"));
        label4->setGeometry(QRect(440, 10, 80, 30));
        label4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(39, 39, 1001, 501));
        layout = new QGridLayout(gridLayoutWidget);
        layout->setObjectName(QString::fromUtf8("layout"));
        layout->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        button2d->setText(QCoreApplication::translate("MainWindow", "2D View", nullptr));
        button3d->setText(QCoreApplication::translate("MainWindow", "3D View", nullptr));
        button23d->setText(QCoreApplication::translate("MainWindow", "View All", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "cm", nullptr));
        label1_img->setText(QString());
        label2_img->setText(QString());
        label1->setText(QCoreApplication::translate("MainWindow", "Coordinates (x,y):", nullptr));
        label2->setText(QCoreApplication::translate("MainWindow", "Height:", nullptr));
        label4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
