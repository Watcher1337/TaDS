/*
Разреженная (содержащая много нулей) матрица хранится в форме 3-х объектов:
- вектор A содержит значения ненулевых элементов;
- вектор JA содержит номера столбцов для элементов вектора A;
- связный список IA, в элементе Nk которого находится номер компонент
в A и JA, с которых начинается описание строки Nk матрицы A.
1. Смоделировать операцию умножения вектора-строки и матрицы,
хранящихся в этой форме, с получением результата в той же форме.
2. Произвести операцию умножения, применяя стандартный алгоритм работы
с матрицами.
3. Сравнить время выполнения операций и объем памяти при использовании
этих 2-х алгоритмов при различном проценте заполнения матриц.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "prints.h"
#include "fill.h"
#include "alloc.h"
#include "definitions.h"

int main()
{
    srand(time(NULL));
    int error = ERROR_NONE;

    SMATRIX s_matrix1, s_matrix2, s_matrix3;

    int *matrix1, *matrix2;

    int fill_perc = 30; // filling %
    int non_zero_num = 0;

    int choice = -1;
    
    int rows, columns;
    int rows2, columns2;
    printf("input size of matrix one: ");

    if (scanf("%d%d", &rows, &columns) == 2 && rows > 0 && columns > 0 && rows * columns <= MAX_MATRIX_SIZE)
    {
        char ch;
        if ((error = matrix_alloc(&matrix1, rows * columns)) == ERROR_NONE)
        {
            printf("Do you want to fill matrix manually? y/N\n");
            fflush(stdin);
            if (scanf("%c", &ch) == 1)
            {
                if (ch == 'y' || ch == 'Y')
                {
                    printf("Matrix will be filled manually\n");
                    manual_fill_matrix(matrix1, rows, columns);
                }
                else
                {
                    printf("Matrix will be filled automatically\n");
                    auto_fill_matrix(matrix1, rows, columns, fill_perc);
                }
                print_matrix(matrix1, rows, columns);
            }
            else
            {
                printf("Wrong Input\n");
                error = ERROR_INPUT;
            }
        }

        if (error == ERROR_NONE)
        {
            printf("input size of matrix two: ");
            fflush(stdin);
            if (scanf("%d%d", &rows2, &columns2) == 2 && rows2 > 0 && columns2 > 0 && rows2 * columns2 <= MAX_MATRIX_SIZE)
            {
                if ((error = matrix_alloc(&matrix2, rows2 * columns2)) == ERROR_NONE)
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
                        print_matrix(matrix2, rows2, columns2);
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
    
        if (error == ERROR_NONE)
        {
            convert_matrix(matrix1, s_matrix1, rows, columns);
            convert_matrix(matrix2, s_matrix2, rows2, columns2);
        }
    }
    else
    {
        printf("Wrong input\n");
        error = ERROR_INPUT;
    }
    
    matrix_free(matrix2);
    matrix_free(matrix1);
    return error;
}