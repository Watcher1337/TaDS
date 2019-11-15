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
 
void print_sparse_matrix(SMATRIX sm, int non_zero_num, int non_zero_row)
{
    printf("A: ");
    for (int i = 0; i < non_zero_num; i++)
        printf("%d ", sm.A[i]);

    printf("\nJA: ");
    for (int i = 0; i < non_zero_num; i++)
        printf("%d ", sm.JA[i]);

    printf("\nNk: ");
    node_ptr start = sm.JA->next;
    while (start != NULL)
    {
        printf("%d ", start->Nk);
        start = start->next;
    }

    printf("\ni: ");
    start = sm.JA->next;
    while (start != NULL)
    {
        printf("%d ", start->i);
        start = start->next;
    }
    printf("\n");
}