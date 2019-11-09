#include <stdio.h>

#include "prints.h"

void print_menu_one()
{
    printf("Choose one of the options below:\n");
    printf("1 - Fill matrices and multiplicate\n");
    printf("2 - Analyse algorythms\n");
    printf("0 - exit\n");
}

void print_menu_two()
{
    printf("Choose one of the options below:\n");
    printf("1 - Fill matrices manually\n");
    printf("2 - Autofill matrices\n");
}

void print_menu_three()
{
    printf("Choose one of the options below:\n");
    printf("1 - multiplication of string-vector and matrix\n");
    printf("2 - classic multiplication\n");
}

void print_matrix(int *matrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int k = 0; k < columns; k++)
            printf("%d ", matrix[i * columns + k]);
        printf("\n");
    }
}