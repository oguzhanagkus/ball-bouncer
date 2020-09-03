QT       += core gui datavisualization network serialport multimedia opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11 opencv

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    colortracker.cpp \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    openingwindow.cpp \
    pid.cpp \
    plate.cpp \
    qcustomplot.cpp \
    scara.cpp

HEADERS += \
    colortracker.h \
    glwidget.h \
    mainwindow.h \
    model.h \
    openingwindow.h \
    pid.hpp \
    plate.h \
    qcustomplot.h \
    scara.h

FORMS += \
    mainwindow.ui \
    openingwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \    \
  obj/arm1.mtl \
  obj/arm2.mtl \
  obj/arm_3.mtl \
  obj/base.mtl \
  obj/glass.mtl \
  obj/test6.mtl \
  pid/pidServoX_config \
  pid/pidServoY_config \
  pid/pidServoY_config_circle \
  pidServoX_config \
  pidServoX_config_circle \
  pidServoY_config \
  pidServoY_config_circle \
  img/height.png \
  img/position.png

INCLUDEPATH += /usr/local/include/opencv4
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -lopencv_core -lopencv_imgproc
LIBS += -lglut -lGLU
