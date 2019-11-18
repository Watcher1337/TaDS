#include <stdio.h>
#include <stdlib.h>

#include "calculations.h"
#include "list.h"

//row vector and sparse matrix multiplication
//rows from nzr
void sparse_multiplication(SMATRIX matr, SMATRIX vector, int *res_vector, int rows)
{
    int sum;
    int j1, j2;

    for (int i = 0; i < rows; i++)
    {
        sum = 0;
        j1 = get_element(matr.JA, i);
        j2 = get_element(matr.JA, i + 1);

        for (int j = j1; j < j2; j++)
            sum += matr.A[j] + vector.A[matr.IA[j]];

        res_vector[i] = sum;
    }
}

void classic_multiplication(int* matrix, int* vector , int* result, int rows, int columns)
{
    for (int i = 0; i < columns; i++)
        for (int k = 0; k < rows; k++)
        {
            result[i] += matrix[k * columns + i] * vector[k];
        }
}

void smart_multiplication(SMATRIX *new_matrix, SMATRIX *vector, SMATRIX *matrix, int rows, int columns)
{
    for (int k = 0; k < rows; k++)
    {
        for (int i = matrix->IA[k]; i < matrix->ia[k+1]; i++)
        {  
            if (matrix->a[i] != 0)
                new_matrix[k] += matrix->a[i] * get_element(vector, matrix->ja[i], matrix->ja[i]);
        }
    }
}