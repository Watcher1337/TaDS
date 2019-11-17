#include <stdio.h>
#include <stdlib.h>

#include "prints.h"

void print_matrix(int *matrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int k = 0; k < columns; k++)
            printf("%d ", matrix[i * columns + k]);
        printf("\n");
    }
}
 
void print_sparse_matrix(SMATRIX *sm, int non_zero_num, int non_zero_row)
{
    printf("\nA: ");
    for (int i = 0; i < non_zero_num; i++)
        printf("%d ", sm->A[i]);

    printf("\nIA: ");
    for (int i = 0; i < non_zero_num; i++)
        printf("%d ", sm->IA[i]);
 
    printf("\nNk: ");
    JA_LIST start = sm->JA;
    while (start != NULL)
    {
        printf("%d ", start->Nk);
        start = start->next;
    }

    printf("\n\n");
}

void print_row_vector(int *vector, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", vector[i]);
}

void print_menu()
{
    printf("choose one of the options:\n");
    printf("1 - row-vector * matrix\n");
    printf("2 - matrix * matrix\n");
    printf("3 - compare calculation time\n");
    printf("0 - exit\n");
}