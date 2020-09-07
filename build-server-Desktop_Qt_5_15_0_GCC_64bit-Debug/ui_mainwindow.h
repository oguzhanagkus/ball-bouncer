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
#include <QtWidgets/QWidget>
#include <glwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    GLWidget *view;
    QLabel *image;
    QWidget *gridLayoutWidget;
    QGridLayout *layout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *button2d;
    QPushButton *button3d;
    QPushButton *button23d;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame_2;
    QLabel *label4;
    QLabel *label1_img;
    QLabel *label1;
    QLabel *label2_img;
    QLabel *label_3;
    QLabel *label2;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *balance_button;
    QPushButton *circle_button;
    QPushButton *stop_button;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1400, 750);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        view = new GLWidget(centralwidget);
        view->setObjectName(QString::fromUtf8("view"));
        view->setGeometry(QRect(40, 350, 360, 360));
        view->setStyleSheet(QString::fromUtf8(""));
        image = new QLabel(centralwidget);
        image->setObjectName(QString::fromUtf8("image"));
        image->setGeometry(QRect(40, 40, 360, 270));
        image->setStyleSheet(QString::fromUtf8(""));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(439, 39, 921, 481));
        layout = new QGridLayout(gridLayoutWidget);
        layout->setObjectName(QString::fromUtf8("layout"));
        layout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(440, 600, 920, 50));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(160, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        button2d = new QPushButton(frame);
        button2d->setObjectName(QString::fromUtf8("button2d"));
        button2d->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
""));

        horizontalLayout_2->addWidget(button2d);

        button3d = new QPushButton(frame);
        button3d->setObjectName(QString::fromUtf8("button3d"));
        button3d->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"\n"
""));

        horizontalLayout_2->addWidget(button3d);

        button23d = new QPushButton(frame);
        button23d->setObjectName(QString::fromUtf8("button23d"));
        button23d->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(button23d);

        horizontalSpacer_2 = new QSpacerItem(160, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(440, 540, 921, 50));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        label4 = new QLabel(frame_2);
        label4->setObjectName(QString::fromUtf8("label4"));
        label4->setGeometry(QRect(410, 10, 80, 30));
        label4->setStyleSheet(QString::fromUtf8("font: 10pt \"Bookman Old Style\";\n"
"color: rgb(255, 255, 255);"));
        label1_img = new QLabel(frame_2);
        label1_img->setObjectName(QString::fromUtf8("label1_img"));
        label1_img->setGeometry(QRect(220, 10, 30, 30));
        label1_img->setStyleSheet(QString::fromUtf8(""));
        label1 = new QLabel(frame_2);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setGeometry(QRect(260, 10, 150, 30));
        label1->setStyleSheet(QString::fromUtf8("font: 10pt \"Bookman Old Style\";\n"
"color: rgb(255, 255, 255);"));
        label2_img = new QLabel(frame_2);
        label2_img->setObjectName(QString::fromUtf8("label2_img"));
        label2_img->setGeometry(QRect(520, 10, 20, 30));
        label2_img->setStyleSheet(QString::fromUtf8(""));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(670, 10, 30, 30));
        label_3->setStyleSheet(QString::fromUtf8("font: 10pt \"Bookman Old Style\";\n"
"color: rgb(255, 255, 255);"));
        label2 = new QLabel(frame_2);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(550, 10, 121, 30));
        label2->setStyleSheet(QString::fromUtf8("font: 10pt \"Bookman Old Style\";\n"
"color: rgb(255, 255, 255);"));
        frame_3 = new QFrame(centralwidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(440, 660, 920, 50));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(160, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        balance_button = new QPushButton(frame_3);
        balance_button->setObjectName(QString::fromUtf8("balance_button"));
        balance_button->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        horizontalLayout->addWidget(balance_button);

        circle_button = new QPushButton(frame_3);
        circle_button->setObjectName(QString::fromUtf8("circle_button"));
        circle_button->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        horizontalLayout->addWidget(circle_button);

        stop_button = new QPushButton(frame_3);
        stop_button->setObjectName(QString::fromUtf8("stop_button"));
        stop_button->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        horizontalLayout->addWidget(stop_button);

        horizontalSpacer_4 = new QSpacerItem(160, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        image->setText(QString());
        button2d->setText(QCoreApplication::translate("MainWindow", "2D View", nullptr));
        button3d->setText(QCoreApplication::translate("MainWindow", "3D View", nullptr));
        button23d->setText(QCoreApplication::translate("MainWindow", "View All", nullptr));
        label4->setText(QString());
        label1_img->setText(QString());
        label1->setText(QCoreApplication::translate("MainWindow", "Coordinates (x,y):", nullptr));
        label2_img->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "cm", nullptr));
        label2->setText(QCoreApplication::translate("MainWindow", "Height:", nullptr));
        balance_button->setText(QCoreApplication::translate("MainWindow", "Balance", nullptr));
        circle_button->setText(QCoreApplication::translate("MainWindow", "Draw Circle", nullptr));
        stop_button->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
