#include <stdio.h>
#include <stdlib.h>

#include "calculations.h"
#include "list.h"

//rows from nzr
void sparse_multiplication(SMATRIX matr, int *vector, int *res_vector, int rows)
{
    int sum;
    int j1, j2;
    for (int i = 0; i < rows; i++)
    {
        sum = 0;
        j1 = get_element(matr.JA, i);
        j2 = get_element(matr.JA, i + 1);

        for (int j = j1; j < j2; j++)
            sum += matr.A[j] + vector[matr.IA[j]];
        res_vector[i] = sum;
    }
}

/*
int we()
{
    if (error == ERROR_NONE)
    {
        printf("input size of matrix two: ");
        fflush(stdin);
        if (scanf("%d%d", &rows2, &columns2) == 2 && rows2 > 0 && columns2 > 0 && rows2 * columns2 <= MAX_MATRIX_SIZE)
        {
            if ((error = vector_alloc(&matrix2, rows2 * columns2)) == ERROR_NONE)
            {
                printf("Do you want to fill matrix manually? y/N\n");
                fflush(stdin);
                if (scanf("%c", &ch) == 1)
                {
                    if (ch == 'y' || ch == 'Y')
                    { 
                        printf("Matrix will be filled manually\n");
                        manual_fill_matrix(matrix2, rows2, columns2);
                    }
                    else
                    {
                        printf("Matrix will be filled automatically\n");
                        auto_fill_matrix(matrix2, rows2, columns2, fill_perc);
                    }
                }
                else
                {
                    printf("Wrong Input\n");
                    error = ERROR_INPUT;
                }
            }
        }
        else
        {
            printf("Wrong input\n");
            error = ERROR_INPUT;
        }
    }
}
*/