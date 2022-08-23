#ifndef STREAMREAD_H_INCLUDED
#define STREAMREAD_H_INCLUDED

#include <stdio.h>

void readPoints(FILE *filePointer, double *x_valuesArray, double *y_valuesArray);

void readPoints_toDraw(FILE *filePointer, double *x_valuesArray_toDraw, double *y_valuesArray_toDraw, double scale_x, double scale_y);

int nbPointsCount(FILE *filePointer);

void calculateScale(double *scale_x, double *scale_y, char *filesPaths[], int nbFiles);

#endif //STREAMREAD_H_INCLUDED