#ifndef SCARA_H
#define SCARA_H

#include <cmath>
#include <vector>
#include <iostream>
#include <QObject>

#include "model.h"

enum SteeringMode {SIMPLE, TARGET};

class Scara : public QObject
{
    Q_OBJECT

public:
    explicit Scara(QObject *parent = 0);

public slots:
    void go(double dt);
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

    void setMode(SteeringMode mode);
    void setTarget(double tx, double ty, double tz);

private slots:
    void kinPr();
    void kinOdwr();
    bool calcSpeed(double vx, double vy, double vz);

private:
    double th1, th2,th3, z;
    double dth1, dth2, dz;
    double posx, posy, posz;
    double tx, ty, tz;

    SteeringMode mode;

    double r1, r2;

    Model baseModel, arm1Model, arm2Model, arm3Model,plate,arm4Model;
    Model baseModel2, arm1Model2, arm2Model2, arm3Model2;

    struct PathPoint { double x, y, z; };
    std::vector<PathPoint> path;
};

extern Scara * robot1;
extern Scara * robot2;
extern Scara * robot3;
extern Scara * robot4;

#endif // SCARA_H
