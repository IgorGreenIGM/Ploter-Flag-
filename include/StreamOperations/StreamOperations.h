#ifndef FILEUTILITIES_H_INCLUDED
#define FILEUTILITIES_H_INCLUDED

#include <stdio.h>

int getFileNameLen(char *path);
char *readFileName(char *path);
unsigned long getFileLength(FILE *filePointer);
void printFileInfo(char *path, double scale_x, double scale_y);
void getFileMaxMinValues(double *max_x, double *max_y, double *min_x, double *min_y, FILE *filePointer);

#endif //FILEUTILITIES_H_INCLUDED