#include <windows.h>
#include "../../include/GL/glut.h"

//axis static drawing methods
void drawAxis()
{
    //  x Axis
    glColor3ub(255, 255, 255);  //defining the axis color    

    glBegin(GL_LINES);
    glVertex2d(0, 0);
    glVertex2d(18, 0);
    glEnd();
    //  y Axis
    glBegin(GL_LINES);
    glVertex2d(0, 0);
    glVertex2d(0, 18);
    glEnd();

    //  x axis End
    glBegin(GL_LINE_STRIP);
    glVertex2d(18, 0.15);
    glVertex2d(18.15, 0);
    glVertex2d(18, -0.15);
    glEnd();
    //  y Axis End
    glBegin(GL_LINE_STRIP);
    glVertex2d(0.1, 18);
    glVertex2d(0, 18.2);
    glVertex2d(-0.1, 18);
    glEnd();
    glFlush();

    //Drawing axis subdivisions 
    glColor3ub(225, 255, 255);      //defining the subdivisions color
    //  x Axis
    for (float i = 0.3; i < 18; i += 0.3)
    {
        glBegin(GL_LINES);
        glVertex2d(i, 0.0);
        glVertex2d(i, -0.1);
        glEnd();
    }
    //  y Axis
    for (float i = 0.5333; i < 18; i += 0.55)
    {
        glBegin(GL_LINES);
        glVertex2d(0.0, i);
        glVertex2d(-0.1, i);
        glEnd();
    }
}

//grid drawing method
void drawGrid()
{
    glColor3ub(22, 22, 22);      //defining the Lines color
    //horizontal lines
    for (float i = 0.3; i < 18; i += 0.3)
    {
        glBegin(GL_LINES);
        glVertex2d(i, 18.0);
        glVertex2d(i, 0.0);
        glEnd();
    }
    //vertical lines
    for (float i = 0.5333; i < 18; i += 0.55)
    {
        glBegin(GL_LINES);
        glVertex2d(18.0, i);
        glVertex2d(0.0, i);
        glEnd();
    }
}