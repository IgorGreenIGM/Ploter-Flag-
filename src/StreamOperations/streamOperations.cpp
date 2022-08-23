#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/DrawingMethods/streamRead.h"
#include "../../include/DrawingMethods/sorting.h"

//Function which return the length of a file extension stored in a char array (path)
int getExtLen(char *path)                                                           
{
    int extensionLenght=0;
    for(int i=strlen(path)-1; i>=0; i--)
    {
        if(path[i] == '.')
        {
            extensionLenght = i;
            break;
        }
    }
    return strlen(path)-extensionLenght-1;
}

//Function which read and return a char array(string) from a file path stored in a char array(path)
char *readExtension(char *path)                                                         
{
    int extLen = getExtLen(path), pathLen = strlen(path), i=0;
    char *extension = (char*)malloc((extLen+1)*sizeof(char));
    for(i=0; i<extLen; i++)
    {
        extension[i] = path[pathLen-extLen+i];
    }
    extension[i] = '\0';                             //adding the (null) : '\0' caracter at end
    return extension;
}

//bool function which return 1 if a string has an extension and 0 else 
int haveExtension(char *path)                                                           
{
    return (getExtLen(path)!=strlen(path)-1) ? 1 : 0;
}

// Function which return the length of a file name from a path
int getFileNameLen(char *path)
{
    int nameLenght = 0;
    for (int i = strlen(path) - 1; i >= 0; i--)
    {
        if (path[i] == '/' || path[i] == '\\');
        {
            nameLenght = i;
            break;
        }
    }
    return strlen(path) - nameLenght - 1;
}

// Function which read and return the name of a file from a path
char *readFileName(char *path)
{
    int nameLen = getFileNameLen(path), pathLen = strlen(path), i = 0;
    char *name = (char *)malloc((nameLen + 1) * sizeof(char));
    for (i = 0; i <= nameLen; i++)
        name[i] = path[pathLen - nameLen + i - 1];

    name[i] = '\0'; // adding the (null) : '\0' caracter at end
    return name;
}

// function which return the size of a specific file
unsigned long getFileLength(FILE *filePointer)
{
    rewind(filePointer);
    fseek(filePointer, 0, SEEK_END);
    return ftell(filePointer);
}

//getting file extremum method
void getFileMaxMinValues(double *max_x, double *max_y, double *min_x, double *min_y, FILE *filePointer)
{
    int nbPoints = nbPointsCount(filePointer);

    double *x_valuesArray = (double *)malloc(nbPoints * sizeof(double));
    double *y_valuesArray = (double *)malloc(nbPoints * sizeof(double));
    readPoints(filePointer, x_valuesArray, y_valuesArray); // read the stream and store the values in the arrays

    double *x_sortedValuesArray = sort(x_valuesArray, nbPoints); // we sort the array, max values are supposed to be at end
    double *y_sortedValuesArray = sort(y_valuesArray, nbPoints);

    *max_x = x_sortedValuesArray[nbPoints - 1]; // assign the max values
    *max_y = y_sortedValuesArray[nbPoints - 1];

    *min_x = x_sortedValuesArray[0]; // assign the min values
    *min_y = y_sortedValuesArray[0];

    free(x_valuesArray);    free(y_valuesArray);    free(x_sortedValuesArray);  free(y_sortedValuesArray);
    rewind(filePointer);
}

void printFileInfo(char *path, double scale_x, double scale_y)
{
    FILE *fp = fopen(path, "r");

    if (fp != NULL)
    {
        double max_x = 0, max_y = 0, min_x = 0, min_y = 0;
        getFileMaxMinValues(&max_x, &max_y, &min_x, &min_y, fp);
        
        if (haveExtension(path))
            printf("File extension : %s\n", readExtension(path));
        else
            printf("there is no Extension detected in this path");
            
        printf("File size : %1.1lf ko -> %ld bytes\n\n", (double)getFileLength(fp) / 1024, getFileLength(fp));
        printf("Axis scales : \n");
        printf("    horizontal(x) axis scale : %lf \n", scale_x);
        printf("    vertial(y) axis scale : %lf \n\n", scale_y);
        printf("Axis Maximum : \n");
        printf("    horizontal(x) axis max value : %1.2lf\n", max_x);
        printf("    vertical(y) axis max value : %1.2lf\n\n", max_y);
        printf("Axis Minimum : \n");
        printf("    horizontal(x) axis min value : %1.2lf\n", min_x);
        printf("    vertical(y) axis min value : %1.2lf\n\n", min_y);
    }
    else
    {
        printf("enable to generate informations from \"%s\"", readFileName(path));
    }
}