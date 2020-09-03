#include "glwidget.h"

#include <GL/glu.h>

/* -------------------------------------------------- */

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent), pitch(30.0), yaw(10.0), distance(15.0)
{

}

/* -------------------------------------------------- */

void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);

    glEnable(GL_CULL_FACE);

    glEnable(GL_POINT_SMOOTH);
    glPointSize(10.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setView();
    setLight();

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glColor4f(0.0, 0.5, 0.0, 0.5);
    for(int i = 0; i <= 20; ++i)
    {
        glBegin(GL_LINES);
        glVertex3f(-5.0+0.5*i, -5.0, 0.0); glVertex3f(-5.0+0.5*i, 5.0, 0.0);
        glVertex3f(-5.0, -5.0+0.5*i, 0.0); glVertex3f(5.0, -5.0+0.5*i, 0.0);
        glEnd();
    }

    glPushMatrix();
    glTranslatef(-3, 0, 0);
    glColor4f(0.5, 0.5, 0.0, 0.5);

    /* --------------- */

    glBegin(GL_LINES);
    glVertex3f(robot1->getY(), -robot1->getX(), 0.0); glVertex3f(robot1->getY(), -robot1->getX(), robot1->getZ()+0.5);
    glEnd();

    glColor4f(0.9, 0.0, 0.0, 0.5);
    robot1->displayPath();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    robot1->display();

    /* --------------- */

    glBegin(GL_LINES);
    glVertex3f(robot2->getY(), -robot2->getX(), 0.0); glVertex3f(robot2->getY(), -robot2->getX(), robot2->getZ()+0.5);
    glEnd();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, -3, 0 );
    glRotatef(90, 0, 0, 1);
    glColor4f(0.9, 0.0, 0.0, 0.5);
    robot2->displayPath();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    robot2->display();

    /* --------------- */

    glBegin(GL_LINES);
    glVertex3f(robot3->getY(), -robot3->getX(), 0.0); glVertex3f(robot3->getY(), -robot3->getX(), robot3->getZ()+0.5);
    glEnd();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(3, 0, 0.0 );
    glRotatef(180,0 , 0, 1);
    glColor4f(0.9, 0.0, 0.0, 0.5);
    robot3->displayPath();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    robot3->display();

    /* --------------- */

    glBegin(GL_LINES);
    glVertex3f(robot4->getY(), -robot4->getX(), 0.0); glVertex3f(robot4->getY(), -robot4->getX(), robot4->getZ()+0.5);
    glEnd();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 3, 0 );
    glRotatef(270,0 , 0, 1);
    glColor4f(0.9, 0.0, 0.0, 0.5);
    robot4->displayPath();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    robot4->display();

    /* --------------- */

    glPopMatrix();
    glPushMatrix();
    glTranslatef(2, 2, 3 );
    glRotatef(90,0 , 0, 1);
    glFlush();
}

void GLWidget::resizeGL(int _w, int _h)
{
    w = _w;
    h = _h;
    glViewport(0.0, 0.0, w, h);
    setView();
}

/* -------------------------------------------------- */

void GLWidget::setPitch(double _pitch)
{
    pitch = _pitch;
}

void GLWidget::setYaw(double _yaw)
{
    yaw = _yaw;
}

void GLWidget::setDistance(double _distance)
{
    distance = _distance;
}

/* -------------------------------------------------- */

void GLWidget::setView()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0*w/h, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(-distance, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glRotatef(pitch, 0.0, -1.0, 0.0);
    glRotatef(yaw, 0.0, 0.0, -1.0);
}

void GLWidget::setLight()
{
    GLfloat lamb[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat ldif[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lpos[] = { -10.0, -10.0, 10.0, 1.0 };

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glColor4fv(ldif);
    glBegin(GL_POINTS);
    glVertex4fv(lpos);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lamb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ldif);
}

/* -------------------------------------------------- */
