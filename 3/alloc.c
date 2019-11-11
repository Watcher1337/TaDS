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

void alloc_sparse_matrix_vectors(SMATRIX sm, int size)
{
    int *temp = (int *)malloc(sizeof(int) * size);
    if (temp)
    {
        sm->A = temp;

        temp = (int *)malloc(sizeof(int) * size);

        if (temp)
        {
            sm->JA = temp;
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
    free(sm->A); // freeing vector with non-zero nums
    free(sm->JA); // freeing vector with columns of these nums
    while (!is_empty(sm->IA))
        pop(sm->IA);
}

void alloc_sparse_matrix_list(SMATRIX sm, int non_zero_rows)
{
    node_ptr tmp;
    if (non_zero_rows > 0)
    {
        tmp = (node_ptr)malloc(sizeof(struct node));
        if (tmp)
        {
            for (int i = 0; i < non_zero_rows && tmp, i++)
            {
                tmp->next = (node_ptr)malloc(sizeof(struct node));
                tmp = tmp->next;
            }
            tmp->next = NULL;
        }
        else
        {
            printf("Allocation error\n");
        }
    }
}

void vector_realloc(int *vector, int target_size); //UNUS