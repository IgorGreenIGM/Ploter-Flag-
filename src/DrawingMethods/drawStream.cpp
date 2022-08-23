#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "../../include/GL/glut.h" 
#include "../../include/DrawingMethods/structures.h"
#include "../../include/DrawingMethods/streamRead.h"
#include "../../include/DrawingMethods/drawStream.h"

//Function which generate randomly a color in the RGB color format
Color *createRandomColor()
{
    Color *color = (Color*)malloc(sizeof(*color));
    color->red = rand()%255;
    color->green = rand()%color->red + 255;
    color->blue = rand()%color->green + 255;
    return color;
}

//Static Drawing stream Method
void drawStream(FILE *filePointer, double scale_x, double scale_y)
{
    Color *color = createRandomColor();
    int nbPoints = nbPointsCount(filePointer);

    double *x_valuesArray_toDraw = (double*)malloc(nbPoints*sizeof(double));
    double *y_valuesArray_toDraw = (double*)malloc(nbPoints*sizeof(double));

    Point *pointA = (Point*)malloc(sizeof(*pointA));
    Point *pointB = (Point*)malloc(sizeof(*pointB));

    readPoints_toDraw(filePointer, x_valuesArray_toDraw, y_valuesArray_toDraw, scale_x, scale_y);     //reading and storing the points to draw in arrays

    int i=0;
    glColor3ub(color->red, color->green, color->blue);
    while(i <= nbPoints-2){
    pointA->x = x_valuesArray_toDraw[i];  pointA->y = y_valuesArray_toDraw[i];    i++;    //Incrementation of pointA and pointB A->B and B->next(B)
    pointB->x = x_valuesArray_toDraw[i];  pointB->y = y_valuesArray_toDraw[i];

    glBegin(GL_LINES);                                                  //drawing of segment A-B
    glVertex2d(pointA->x, pointA->y);
    glVertex2d(pointB->x, pointB->y);
    glEnd();
    }
    free(pointA);   free(pointB);   free(color);
    glFlush();
}


//Function of calculztion of the position of the drawer
//let be A(xa, ya) and B(xb, yb)
//this function give the position of the drawer inside the segemnt A-B
void calculateDrawerPosition(double x_a, double x_b, double y_a, double y_b, Point *drawer)
{
    drawer->y = (double)(((y_b - y_a)*(drawer->x - x_a)))/(x_b - x_a) + y_a;
}

/**
 * function of drawing the drawer for simulate an animation, by drawing multiple points in place of directly the segment A-B 
 * A and B defined as the extrems of the segment, theses are read in the specifies stream
 * for change the speed of the aniation, just increase or decrease the absciss of the drawer incrementation
 */
void drawSegmentByDrawer(Point *drawer, Point *pointA, Point *pointB, Color *color)
{
    for(drawer->x = pointA->x ; drawer->x < pointB->x ; drawer->x+=0.000001)    /*the speed of the animation*/
    {
    calculateDrawerPosition(pointA->x, pointB->x, pointA->y, pointB->y, drawer);
    glBegin(GL_POINTS);
    glColor3ub(color->red, color->green, color->blue);
    glVertex2d(drawer->x, drawer->y);
    glEnd();
    }
    glFlush();
}

//Animated Drawing Stream Method
void drawStreamAnimation(FILE *filePointer, double scale_x, double scale_y)
{
    Color *color = createRandomColor();
    int nbPoints = nbPointsCount(filePointer);
    rewind(filePointer);

    double *x_valuesArray_toDraw = (double*)malloc(nbPoints*sizeof(double));
    double *y_valuesArray_toDraw = (double*)malloc(nbPoints*sizeof(double));

    Point *pointA = (Point*)malloc(sizeof(*pointA));
    Point *pointB = (Point*)malloc(sizeof(*pointB));
    Point *drawer = (Point*)malloc(sizeof(*drawer));

    readPoints_toDraw(filePointer, x_valuesArray_toDraw, y_valuesArray_toDraw, scale_x, scale_y);     //reading and storing the points to draw in arrays

    int i=0;
    glColor3ub(color->red, color->green, color->blue);
    while(i <= nbPoints-2){
    pointA->x = x_valuesArray_toDraw[i];  pointA->y = y_valuesArray_toDraw[i];    i++;    //Incrementation of pointA and pointB A->B and B->next(B)
    pointB->x = x_valuesArray_toDraw[i];  pointB->y = y_valuesArray_toDraw[i];

    drawSegmentByDrawer(drawer, pointA, pointB, color);
    }
    free(pointA);   free(pointB);   free(color);    free(drawer);
    glFlush();
}