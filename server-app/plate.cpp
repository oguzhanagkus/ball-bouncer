#include "plate.h"
#include <iostream>

plate *Plate;

/* -------------------------------------------------- */

plate::plate(QObject *parent) :
    QObject(parent),
    th1(270.0), th2(90.0),th3(90.0), z(90.0),
    dth1(0.0), dth2(0.0), dz(0.0),
    posx(0.0), posy(0.0), posz(0.0),
    tx(1.0), ty(1.0), tz(1.0),
    x1(0),y1(0),z1(0),
    r1(1.5), r2(1.5)
{

}

/* -------------------------------------------------- */

void plate::displayPath()
{
    std::vector<PathPoint>::iterator i;
    glBegin(GL_LINE_STRIP);

    for(i = path.begin(); i < path.end(); ++i)
        glVertex3f(i->y, -i->x, i->z+0.5);
    glEnd();
}

void plate::display()
{
    glTranslatef(x1, y1, z1);
    glRotatef(th1, 0.0, 0.0, 1.0);
}

/* -------------------------------------------------- */

double plate::getTh1()
{
    return th1;
}

double plate::getTh2()
{
    return th2;
}
double plate::getTh3()
{
    return th2;
}

/* -------------------------------------------------- */

double plate::getX()
{
    return posx;
}

double plate::getY()
{
    return posy;
}

double plate::getZ()
{
    return posz;
}

/* -------------------------------------------------- */

void plate::setTh1(double _th1)
{
    th1 = _th1;
}

void plate::setTh2(double _th2)
{
    th2 = _th2;
}

void plate::setTh3(double _th3)
{
    th3 = _th3;
}
void plate::setZ(double _z)
{
    z = _z;
}

/* -------------------------------------------------- */

void plate::setTarget(double _tx, double _ty, double _tz)
{
    tx = _tx;
    ty = _ty;
    tz = _tz;
}

void plate::changeLocation(double x, double y, double z)
{
    x1=x;
    y1=y;
    z1=z;
}

/* -------------------------------------------------- */
