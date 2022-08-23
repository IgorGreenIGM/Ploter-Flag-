#ifndef DRAWSTREAM_H_INCLUDED
#define DRAWSTREAM_H_INCLUDED

#include "structures.h"
#include <stdio.h>

Color *createRandomColor();
void drawStream(FILE *filePointer, double scale_x, double scale_y);
void drawStreamAnimation(FILE *filePointer, double scale_x, double scale_y);
void drawSegmentByDrawer(Point *drawer, Point *pointA, Point *pointB, Color *color);
void calculateDrawerPosition(double x_a, double x_b, double y_a, double y_b, Point *drawer);
#endif