#include <stdio.h>
#include <stdlib.h>

#include "calculations.h"
#include "alloc.h"
#include "fill.h"
#include "list.h"

//row vector and sparse matrix multiplication
//rows from nzr
void sparse_multiplication(sparse_matrix matr, sparse_vector vector, int *res_vector, int rows)
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

void calculate_and_measure(int *vector, int *res_vector, int rows, int columns, int* matrix, sparse_matrix smatrix)
{
    sparse_vector s_vector, s_res_vector;
    printf("Input amount of vector elements: ");
    int size;
    if (scanf("%d", &size) == 1)
    {
        s_vector.A = (int *)calloc(size, sizeof(int));
        s_vector.IA = (int *)calloc(size, sizeof(int));
        s_vector.size = size;

        manual_fill_vector(vector, &s_vector, rows);

        printf("vector: ");
        for (int i = 0; i < rows; i++)
            printf("%d ", vector[i]);

        printf("\nsparse form:\n");
        
        printf("A: ");
        for (int i = 0; i < s_vector.size; i++)
            printf("%d ", s_vector.A[i]);
    
        printf("\nIA: ");
        for (int i = 0; i < s_vector.size; i++)
            printf("%d ", s_vector.IA[i]);
        printf("\n");
    }
    else
    printf("Wrong Input\n");

    free(s_vector.A);
    free(s_vector.IA);
}