#include <stdio.h>
#include <stdlib.h>

#include "fill.h"
#include "list.h"

void auto_fill_matrix(int *matrix, int rows, int columns, int percent)
{ 
    int chance;

    if (!matrix)
        printf("help..\n");

    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
        {
            chance = rand() % 100;
            if (chance > percent)
                matrix[i * columns + j] = 0;
            else
            {
                matrix[i * columns + j] = rand() % 10;
            }
        }
}

void manual_fill_matrix(int *matrix, int rows, int columns)
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

int convert_matrix(int *matrix, SMATRIX sm, int rows, int columns)
{
    int error = ERROR_NONE;
    
    int curr = 0;
    int first = 0;

    for (int i = 0; i < rows; i++)
    {
        first = 1;
        for (int k = 0; k < columns; k++)
            if (matrix[i * columns + k] != 0)
            {
                sm.A[curr] = matrix[i * columns + k];
                sm.IA[curr] = k;

                if (first)
                {
                    first = 0;
                    push(curr, i, sm.JA);
                    printf("list\n");
                }
                curr++;
            }
    }

    return error;
}

//nzr - non zero rows
//nzn - non zero numbers
void count_non_zero(int *matrix, int rows, int columns, int *nzr, int *nzn)
{
    int row_count_flag = 0;
    for (int i = 0; i < rows; i++, row_count_flag = 0)
        for (int k = 0; k < columns; k++)
        {
            if (matrix[i * columns + k] != 0)
            {
                *nzn = *nzn + 1;
                if (row_count_flag == 0)
                {
                    *nzr = *nzr + 1;
                    row_count_flag = 1;
                }
            }
        }
}