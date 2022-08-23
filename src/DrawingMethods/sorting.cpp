#include <stdio.h>
#include <stdlib.h>

/*Sorting Algorithm
 *this sorting algorithm is based on the fusion sort algorithm, working only with doubles or floating values
 *and return a file sorted array
*/
double *merge(double *A, int TA, double *B, int TB)
{
    int i = 0, j = 0, k = 0;
    double *T = (double*)calloc((TA + TB), sizeof(double));
    while ((i < TA) && (j < TB))
    {
        if (A[i] < B[j])
        {
            T[k] = A[i];    i++;    k++;
        }
        else
        {
            T[k] = B[j]; j++; k++;
        }
    }

    while (i < TA)
    {   
        T[k] = A[i];   i++;  k++;
    }

    while (j < TB)
    {
        T[k] = B[j];  j++;  k++;
    }
    return T;
}

double *sort(double *table, int size)
{
    if (size <= 1)
    {
        return table;
    }
    else
    {
        int t_a = size / 2;
        int t_b = size - t_a;

        double *A = (double*)malloc(t_a * sizeof(double));
        double *B = (double*)malloc(t_b * sizeof(double));
        int i = 0;
        for (i = 0; i < t_a; i++) A[i] = table[i];
        int k = i;
        for (int j = 0; j < t_b; j++)
        {
            B[j] = table[k];
            k++;
        }
        return merge(sort(A, t_a), t_a, sort(B, t_b), t_b);
    }
}