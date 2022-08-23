#include <stdio.h>
#include <stdlib.h>
#include "../../include/DrawingMethods/sorting.h"
#include "../../include/DrawingMethods/streamRead.h"

#define _screenWidthLimit 17
#define _screenHeightLimit 17

// Reading points in a file function
void readPoints(FILE *filePointer, double *x_valuesArray, double *y_valuesArray)
{
    rewind(filePointer);
    char *buffer = (char *)malloc(256 * sizeof(char)); // supposing that one line length isn't bigger than 256

    int i = 0;
    while (fgets(buffer, 256, filePointer) != NULL)
    {
        sscanf(buffer, "%lf %lf", &x_valuesArray[i], &y_valuesArray[i]);
        i++;
    }
    free(buffer);
    rewind(filePointer);
}

// Function whose counts the number of stored points(abs and ord) in a specified
int nbPointsCount(FILE *filePointer)
{
    char *buffer = (char *)malloc(256 * sizeof(char)); // supposing that one line length isn't bigger than 256
    int nbPoints = 0;
    while (fgets(buffer, 256, filePointer) != NULL)
        nbPoints++;
    rewind(filePointer); // set the virtual cursor to the begining
    free(buffer);
    return nbPoints;
}

/*Function of calculation of the scale
 *she search the max values (on x and y axis) which are stored in the file
 * and by these values, scale_x and scale_y are calculated then the graph will be limited to the screen
 * ie not everlap 17 pixels according to our defined map
 */
void calculateScale(double *scale_x, double *scale_y, char *filesPaths[], int filesNumber)
{
    double max_x[filesNumber];
    double max_y[filesNumber];

    int nbPoints[filesNumber];
    FILE *fileStreams[filesNumber];

    for (int i = 0; i < filesNumber; i++)
        fileStreams[i] = fopen(filesPaths[i], "r");
    for (int i = 0; i < filesNumber; i++)
        nbPoints[i] = nbPointsCount(fileStreams[i]);

    for (int i = 0; i < filesNumber; i++)
    {
        double *x_valuesArray = (double *)malloc(nbPoints[i] * sizeof(double));
        double *y_valuesArray = (double *)malloc(nbPoints[i] * sizeof(double));
        readPoints(fileStreams[i], x_valuesArray, y_valuesArray); // read the stream and store the values in the arrays

        // we sort the array, max values are supposed to be at end
        double *x_sortedValuesArray = sort(x_valuesArray, nbPoints[i]);
        double *y_sortedValuesArray = sort(y_valuesArray, nbPoints[i]);

        max_x[i] = x_sortedValuesArray[nbPoints[i] - 1]; // assign the max values
        max_y[i] = y_sortedValuesArray[nbPoints[i] - 1];

        free(x_valuesArray);    free(y_valuesArray);
        free(x_sortedValuesArray);  free(y_sortedValuesArray);
    }

    double *max_x_sortedValuesArray = sort(max_x, filesNumber);
    double *max_y_sortedValuesArray = sort(max_y, filesNumber);

    *scale_x = _screenWidthLimit/max_x_sortedValuesArray[filesNumber - 1];
    *scale_y = _screenHeightLimit/max_y_sortedValuesArray[filesNumber - 1];

    free(max_x_sortedValuesArray);  free(max_y_sortedValuesArray);
    for(int i=0; i<filesNumber; i++)
        fclose(fileStreams[i]);
}

void readPoints_toDraw(FILE *filePointer, double *x_valuesArray_toDraw, double *y_valuesArray_toDraw, double scale_x, double scale_y)
{
    rewind(filePointer);
    char *buffer = (char *)malloc(256 * sizeof(char)); // supposing that one line length isn't bigger than 256

    int i = 0;
    while (fgets(buffer, 256, filePointer) != NULL) // we read the values in the file but directly multiply it by the scale on each axis
    {
        sscanf(buffer, "%lf %lf", &x_valuesArray_toDraw[i], &y_valuesArray_toDraw[i]);
        x_valuesArray_toDraw[i] *= scale_x;
        y_valuesArray_toDraw[i] *= scale_y;
        i++;
    }
    free(buffer);
    rewind(filePointer);
}