/********************************************************************************
** Form generated from reading UI file 'openingwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENINGWINDOW_H
#define UI_OPENINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gWindow
{
public:
    QGridLayout *gridLayout;
    QGroupBox *camera;
    QGridLayout *gridLayout_3;
    QPushButton *cameraConnect;
    QLabel *cameraLabel;
    QPushButton *cameraRefresh;
    QComboBox *cameraList;
    QLabel *statusLabel;
    QGroupBox *controller;
    QGridLayout *gridLayout_2;
    QLabel *controllerLabel;
    QComboBox *controllerList;
    QPushButton *controllerConnect;
    QPushButton *controllerRefresh;
    QPushButton *continueButton;

    void setupUi(QWidget *gWindow)
    {
        if (gWindow->objectName().isEmpty())
            gWindow->setObjectName(QString::fromUtf8("gWindow"));
        gWindow->resize(715, 234);
        gWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));
        gridLayout = new QGridLayout(gWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        camera = new QGroupBox(gWindow);
        camera->setObjectName(QString::fromUtf8("camera"));
        camera->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));
        camera->setAlignment(Qt::AlignCenter);
        gridLayout_3 = new QGridLayout(camera);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        cameraConnect = new QPushButton(camera);
        cameraConnect->setObjectName(QString::fromUtf8("cameraConnect"));
        cameraConnect->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        gridLayout_3->addWidget(cameraConnect, 0, 3, 1, 1);

        cameraLabel = new QLabel(camera);
        cameraLabel->setObjectName(QString::fromUtf8("cameraLabel"));
        cameraLabel->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));
        cameraLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(cameraLabel, 0, 4, 1, 1);

        cameraRefresh = new QPushButton(camera);
        cameraRefresh->setObjectName(QString::fromUtf8("cameraRefresh"));
        cameraRefresh->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        gridLayout_3->addWidget(cameraRefresh, 0, 2, 1, 1);

        cameraList = new QComboBox(camera);
        cameraList->setObjectName(QString::fromUtf8("cameraList"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cameraList->sizePolicy().hasHeightForWidth());
        cameraList->setSizePolicy(sizePolicy);
        cameraList->setMaximumSize(QSize(260, 16777215));
        cameraList->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        gridLayout_3->addWidget(cameraList, 0, 0, 1, 2);


        gridLayout->addWidget(camera, 3, 0, 1, 4);

        statusLabel = new QLabel(gWindow);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));
        statusLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(statusLabel, 4, 1, 1, 2);

        controller = new QGroupBox(gWindow);
        controller->setObjectName(QString::fromUtf8("controller"));
        controller->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));
        controller->setAlignment(Qt::AlignCenter);
        gridLayout_2 = new QGridLayout(controller);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        controllerLabel = new QLabel(controller);
        controllerLabel->setObjectName(QString::fromUtf8("controllerLabel"));
        controllerLabel->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));
        controllerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(controllerLabel, 0, 4, 1, 1);

        controllerList = new QComboBox(controller);
        controllerList->setObjectName(QString::fromUtf8("controllerList"));
        sizePolicy.setHeightForWidth(controllerList->sizePolicy().hasHeightForWidth());
        controllerList->setSizePolicy(sizePolicy);
        controllerList->setMaximumSize(QSize(260, 16777215));
        controllerList->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        gridLayout_2->addWidget(controllerList, 0, 0, 1, 2);

        controllerConnect = new QPushButton(controller);
        controllerConnect->setObjectName(QString::fromUtf8("controllerConnect"));
        controllerConnect->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        gridLayout_2->addWidget(controllerConnect, 0, 3, 1, 1);

        controllerRefresh = new QPushButton(controller);
        controllerRefresh->setObjectName(QString::fromUtf8("controllerRefresh"));
        controllerRefresh->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        gridLayout_2->addWidget(controllerRefresh, 0, 2, 1, 1);


        gridLayout->addWidget(controller, 1, 0, 1, 4);

        continueButton = new QPushButton(gWindow);
        continueButton->setObjectName(QString::fromUtf8("continueButton"));
        continueButton->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        gridLayout->addWidget(continueButton, 5, 1, 1, 2);


        retranslateUi(gWindow);

        QMetaObject::connectSlotsByName(gWindow);
    } // setupUi

    void retranslateUi(QWidget *gWindow)
    {
        gWindow->setWindowTitle(QCoreApplication::translate("gWindow", "Form", nullptr));
        camera->setTitle(QCoreApplication::translate("gWindow", "Camera Connection", nullptr));
        cameraConnect->setText(QCoreApplication::translate("gWindow", "Connect", nullptr));
        cameraLabel->setText(QCoreApplication::translate("gWindow", "Select camera!", nullptr));
        cameraRefresh->setText(QCoreApplication::translate("gWindow", "Refresh", nullptr));
        statusLabel->setText(QCoreApplication::translate("gWindow", "Connect to controller and camera, then continue!", nullptr));
        controller->setTitle(QCoreApplication::translate("gWindow", "Controller Connection", nullptr));
        controllerLabel->setText(QCoreApplication::translate("gWindow", "Select controller!", nullptr));
        controllerConnect->setText(QCoreApplication::translate("gWindow", "Connect", nullptr));
        controllerRefresh->setText(QCoreApplication::translate("gWindow", "Refresh", nullptr));
        continueButton->setText(QCoreApplication::translate("gWindow", "Continue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gWindow: public Ui_gWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENINGWINDOW_H
