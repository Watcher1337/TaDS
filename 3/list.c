#include <stdio.h>
#include <stdlib.h>
 
#include "definitions.h"
#include "list.h"

void pop(IA_LIST IA)
{
    if (is_empty(IA))
        printf("List is empty\n");
    else
    {
        node_ptr first = IA->next;
        IA->next = IA->next->next;
        free(IA);
    }
}

int is_empty(IA_LIST IA)
{
    return(IA->next == NULL);
}

void repack_matrix(int *matrix, int rows, int columns, SMATRIX sm)
{
    int A_curr = 0;
    int An_curr = 0;
    int first_in_column = 1;

    for (int i = 0; i < columns; i++)
    {
        for (int k = 0; k < rows; k++, first_in_column = 1)
        {
            sm->A[A_curr] = matrix[i * columns + k];
            sm->JA[A_curr] = k;

            if (first_in_column)
            {
                first_in_column = 0;
                sm->IA->Nk = A_curr;
                sm->IA->i = i;
                sm->IA = sm->IA->next;
            }
            A_curr++;
        }
    }
}

