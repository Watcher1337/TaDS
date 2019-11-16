#include <stdio.h>
#include <stdlib.h>

#include "alloc.h"
#include "list.h"

int matrix_alloc(int **vector, int size)
{ 
    int error = ERROR_NONE;
    *vector = (int *)calloc(size, sizeof(int));

    if (!(*vector))
    {
        printf("Memory allocation error\n");
        error = ERROR_MEMORY;
    }

    return error; 
}

void alloc_sparse_matrix_vectors(SMATRIX * sm, int size)
{ 
    int *temp = (int *)malloc(sizeof(int) * size);
    if (temp)
    {
        sm->A = temp;

        temp = (int *)malloc(sizeof(int) * size);

        if (temp)
        {
            sm->IA = temp;
            temp = NULL;
        }
        else
        {
            printf("Error: memory allocation\n");
        }
    }
    else
    {
        printf("Error: memory allocation\n");
    }
}

void matrix_free(int *vector)
{
    free(vector);
}

void free_sparse_matrix(SMATRIX sm)
{
    free(sm.A); // freeing vector with non-zero nums
    free(sm.IA); // freeing vector with rows of these nums
    while (!is_empty(sm.JA))
        pop(sm.JA);
}

void alloc_sparse_matrix_list(SMATRIX * sm, int non_zero_rows)
{
    if (non_zero_rows > 0)
    {
        sm->JA = (JA_LIST)malloc(sizeof(struct node));
        sm->JA->next = NULL;
        if (!sm->JA)
            printf("Allocation error\n");
        else
        {
            node_ptr tmp = sm->JA;
            for(int i = 0; i < non_zero_rows && tmp; i++)
            {
                tmp = (node_ptr)malloc(sizeof(struct node));
                if(!tmp)
                    printf("node allocation error\n");
                
                if (i + 1 == non_zero_rows)
                    tmp->next = NULL;
                else
                    tmp = tmp->next;
            }
        }
    }
    else
    {
        printf("Empty matrix\n");
    }
}