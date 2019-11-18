#include <stdio.h>
#include <stdlib.h>

#include "fill.h"
#include "list.h"

void auto_fill_matrix(int *matrix, int rows, int columns, int percent)
{ 
    int chance;

    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
        {
            chance = rand() % 100;
            if (chance > percent)
                matrix[i * columns + j] = 0;
            else
                matrix[i * columns + j] = rand() % 10;
        }
}

void auto_fill_vector(int *vector, int size, int percent)
{
    for (int i = 0; i < size; i++)
        vector[i] = rand() % 10;
}

void manual_fill_matrix(int *matrix,  int rows, int columns)
{
    int i = 0, j = 0, value = 0;
    fflush(stdin);
    do
    {
        if (i >= 0 && j >= 0 && i < rows && j < columns)
        {
            matrix[i * columns + j] = value;
        }
        else
            printf("ERR: wrong index (i: [0; %d], j: [0, %d]) \\ rows", rows - 1, columns - 1);

        printf("Input (i j value): ");
        fflush(stdin);
    }
    while (scanf("%d %d %d", &i, &j, &value) == 3);
} 

void manual_fill_vector(int *vector, sparse_vector *svector, int size)
{
    int i = 0, value = 0;
    int current = 0;
    fflush(stdin);

    printf("Input (i value): ");
    while (current < svector->size && scanf("%d %d", &i, &value) == 2)
    {
        if (i >= 0 && i < size)
        {
            vector[i] = value;
            svector->A[current] = value;
            svector->IA[current] = i;
            current++;
        }
        else
            printf("wrong index\n");
        
        printf("Input (i value): ");
        fflush(stdin);
    } 
    
}

int convert_matrix(int *matrix, sparse_matrix *sm, int rows, int columns)
{
    int error = ERROR_NONE;
    
    int curr = 0;
    int in_row = 0;
    int prev = 0;

    sm->JA->Nk = 0;
    node_ptr tmp = sm->JA->next;
    for (int i = 0; i < rows; i++)
    {
        in_row = 0;
        for (int k = 0; k < columns; k++)
            if (matrix[i * columns + k] != 0)
            {
                sm->A[curr] = matrix[i * columns + k];
                sm->IA[curr] = k;
                in_row++;
                curr++;
            }
        
        if (in_row == 0)
        {
            tmp->Nk = prev;
            tmp = tmp->next;
        }
        else
        {
            tmp->Nk = in_row + prev;
            tmp = tmp->next;
            prev += in_row;
        }
    }

    return error;
}

//nzn - non zero numbers
void count_non_zero(int *matrix, int rows, int columns, int *nzn)
{
    *nzn = 0;
    for (int i = 0; i < rows; i++)
        for (int k = 0; k < columns; k++)
        {
            if (matrix[i * columns + k] != 0)
            {
                *nzn = *nzn + 1;
            }
        }
}