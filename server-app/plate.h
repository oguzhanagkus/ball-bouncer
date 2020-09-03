#ifndef PLATE_H
#define PLATE_H

#include <cmath>
#include <vector>
#include <iostream>
#include <QObject>

#include "model.h"

class plate : public QObject
{
    Q_OBJECT

public:
    explicit plate(QObject *parent = 0);

public slots:
    void displayPath();
    void display();

    double getTh1();
    double getTh2();
    double getTh3();

    double getX();
    double getY();
    double getZ();

    void setTh1(double th1);
    void setTh2(double th2);
    void setTh3(double th3);
    void setZ(double z);

    void setTarget(double tx, double ty, double tz);
    void changeLocation(double x,double y,double z);

private:
    double th1, th2,th3, z;
    double dth1, dth2, dz;
    double posx, posy, posz;
    double tx, ty, tz;

    double x1,y1,z1;
    double r1, r2;

    Model plate_model;

    struct PathPoint {double x, y, z;};
    std::vector<PathPoint> path;
};

extern plate *Plate;

#endif // SCARA_H
