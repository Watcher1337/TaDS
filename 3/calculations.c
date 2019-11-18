#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "calculations.h"
#include "alloc.h"
#include "fill.h"
#include "list.h"

unsigned long long tick(void)
{
    unsigned long long tmp;
    __asm __volatile__ ("rdtsc" : "=A" (tmp) );
    return tmp;
}

//row vector and sparse matrix multiplication
//rows from nzr
void sparse_multiplication(sparse_matrix matr, sparse_vector vector, int *res_vector, int columns)
{
    int sum;
    int j1, j2;

    for (int i = 0; i < columns; i++)
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

void transpose(int *matrix, sparse_matrix *smatrix, int rows, int columns)
{
    int count = 0;
    smatrix->JA->Nk = 0;
    int index = 1;
    
    node_ptr current_node = smatrix->JA->next;
    for (int i = 0; i < columns; i++, index++)
    {
        for (int j = 0; j < rows; j++)
        {
            if (matrix[j * columns + i] != 0)
            {
                smatrix->A[count] = matrix[j * columns + i];
                current_node->Nk = j;
                current_node = current_node->next;
                count++;
            }
        }
        smatrix->IA[index] = count;
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

        printf("\n\nvector: ");
        for (int i = 0; i < rows; i++)
            printf("%d ", vector[i]);

        printf("\n\nsparse form:\n");
        
        printf("A: ");
        for (int i = 0; i < s_vector.size; i++)
            printf("%d ", s_vector.A[i]);
    
        printf("\nIA: ");
        for (int i = 0; i < s_vector.size; i++)
            printf("%d ", s_vector.IA[i]);
        printf("\n");

        classic_multiplication(matrix, vector, res_vector, rows, columns);
        printf("\nclassic |vector * matrix| multiplication result: ");

        for (int i = 0; i < columns; i++)
            printf("%d ", res_vector[i]);
        printf("\n");

        printf("pre-transpose\n");
        
        transpose(matrix, &smatrix, rows, columns);
        
        printf("post-transpose\n");
        
        sparse_multiplication(smatrix, s_vector, res_vector, columns);

        printf("post-sparse\n");

        printf("sparse multiplication result: ");
        for (int i = 0; i < columns; i++)
            printf("%d ", res_vector[i]);
        printf("\n");

        int non_z_num = 0;
        for (int i = 0; i < columns; i++)
            if (res_vector[i] != 0)
                non_z_num++;
        
        if (non_z_num > 0)
        {
            s_res_vector.A = (int *)calloc(size, sizeof(int));
            s_res_vector.IA = (int *)calloc(size, sizeof(int));
            s_res_vector.size = size;

            free(s_res_vector.A);
            free(s_res_vector.IA);
        }
        else
            printf("zero vector\n");
    }
    else
    printf("Wrong Input\n");

    free(s_vector.A);
    free(s_vector.IA);
}