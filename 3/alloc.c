#include <stdio.h>
#include <stdlib.h>

#include "alloc.h"
#include "list.h"

int alloc_vector(int **matrix, int size)
{ 
    int error = ERROR_NONE;
    *matrix = (int *)calloc(size, sizeof(int));

    if (!(*matrix))
        printf("Memory allocation error\n");

    return error; 
}

void alloc_sparse_matrix_vectors(sparse_matrix * sm, int size)
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
            printf("Error: memory allocation\n");
    }
    else
        printf("Error: memory allocation\n");
}

void matrix_free(int *vector)
{
    free(vector);
}

void free_sparse_matrix(sparse_matrix *sm)
{
    free(sm->A);
    free(sm->IA);

    node_ptr tmp;
    list start = sm->JA;
    while (start != NULL)
    {
        tmp = start;
        start = start->next;
        free(tmp);
    }    
}

void alloc_sparse_matrix_list(sparse_matrix *sm, int size)
{
    if (size > 0)
    {
        sm->JA = (list)malloc(sizeof(struct node));
        sm->JA->next = NULL;

        if (!sm->JA)
            printf("Allocation error\n");
        else
        {
            node_ptr tmp = (node_ptr)malloc(sizeof(struct node));
            sm->JA->next = tmp;

            for(int i = 0; i < size - 1; i++)
            {
                tmp->next = (node_ptr)malloc(sizeof(struct node));
                tmp = tmp->next;   

                if(!tmp)
                {
                    printf("node allocation error\n");
                    break;
                }
            }
            tmp->next = NULL;
        }
    }
    else
    {
        printf("Empty matrix\n");
    }
}
