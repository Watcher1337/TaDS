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
    int non_zero_row_1 = 0, non_zero_num_1 = 0;
    int non_zero_row_2 = 0, non_zero_num_2 = 0;

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
            // Allocating memory and converting matrixes into sparse vector form
            count_non_zero(matrix1, rows, columns, &non_zero_row_1, &non_zero_num_1);
            printf("count done\n");
            alloc_sparse_matrix_vectors(&s_matrix1, non_zero_num_1);
            printf("sparse allocated\n");
            alloc_sparse_matrix_list(&s_matrix1, non_zero_row_1);
            printf("list allocated\n");
            convert_matrix(matrix1, s_matrix1, rows, columns);
            printf("matrix converted\n");
            if (rows < 10 && columns < 10)
                print_matrix(matrix1, rows, columns);
            print_sparse_matrix(s_matrix1, non_zero_num_1, non_zero_row_1);

            count_non_zero(matrix2, rows2, columns2, &non_zero_row_2, &non_zero_num_2);
            alloc_sparse_matrix_vectors(&s_matrix2, non_zero_num_2);
            alloc_sparse_matrix_list(&s_matrix2, non_zero_row_2);
            convert_matrix(matrix2, s_matrix2, rows2, columns2);
            if (rows2 < 10 && columns2 < 10)
                print_matrix(matrix2, rows2, columns2);
            print_sparse_matrix(s_matrix2, non_zero_num_2, non_zero_row_2);

            alloc_sparse_matrix_vectors(&s_matrix3, non_zero_num_1 + non_zero_num_2);
            s_matrix3.JA->Nk = -1;
            s_matrix3.JA->i = -1;
        }
    }
    else
    {
        printf("Wrong input\n");
        error = ERROR_INPUT;
    }
    
    free_sparse_matrix(s_matrix3);
    free_sparse_matrix(s_matrix2);
    free_sparse_matrix(s_matrix1);
    matrix_free(matrix2);
    matrix_free(matrix1);
    return error;
}