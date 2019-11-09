#include <stdio.h>
#include <stdlib.h>

#include "fill.h"

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
                matrix[i * columns + j] = rand() % 10;
        }
}

void manual_fill_matrix(int *matrix, int rows, int columns)
{
    int i = 0, j = 0, value = 0;

    fflush(stdin);
    do
    {
        if (i >= 0 && j >= 0 && i < rows && j < columns)
            matrix[i*columns+j] = value;
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
    for (int i = 0; i < rows)
    {
        int counter = 0;
        for (int k = 0; k < columns)
        {
            if (matrix[i * columns + k] != 0)
            {
                sm->A = matrix[i * columns + k];
                sm->JA = k;
                counter++;
            }
        }
    }
}