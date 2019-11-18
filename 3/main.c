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
#include "calculations.h"
#include "definitions.h"

int main()
{
    srand(time(NULL));

    int *matrix;
    sparse_matrix smatrix;
    sparse_vector row_vector, res_vector;

    int rows, columns;
    int non_zero_numbers;
    char choice;

    int matrix_set = 0;

    int filling_percentage = 50;

    printf("Enter matrix rows and columns: ");

    if (scanf("%d%d", &rows, &columns) == 2)
    {
        int check = alloc_vector(&matrix, rows * columns);

        printf("Would you like to input matrix manually? y/N\n");
        fflush(stdin);
        if (scanf("%c", &choice) == 1 && check == ERROR_NONE)
        {
            if (choice == 'y' || choice == 'Y')
                manual_fill_matrix(matrix, rows, columns);
            else
                auto_fill_matrix(matrix, rows, columns, filling_percentage);
            
            count_non_zero(matrix, rows, columns, &non_zero_numbers);

            if (non_zero_numbers > 0)
            {
                alloc_sparse_matrix_vectors(&smatrix, non_zero_numbers);
                alloc_sparse_matrix_list(&smatrix, rows);
                convert_matrix(matrix, &smatrix, rows, columns); 

                print_sparse_matrix(&smatrix, non_zero_numbers);
                matrix_set = 1;
            }
            else
                printf("Zero matrix\n");
        }
        else
            printf("Wrong input!\n");
    }
    else
        printf("Wrong input!\n");


    if (matrix_set)
    {
        int choice = -1;

        int *vector, *res_vector;
        vector = (int *)calloc(rows, sizeof(int));
        res_vector = (int *)calloc(columns, sizeof(int));

        if (rows < 15 && columns < 15)
        {
            printf("current matrix:\n");
            print_matrix(matrix, rows, columns);
        }
        if (rows < 75 && columns < 75)
            print_sparse_matrix(&smatrix, non_zero_numbers);

        calculate_and_measure(vector, res_vector, rows, columns, matrix, smatrix);
            
        free(vector);
        free(res_vector);
    }
    else
        printf("matrix not set\n");

    free(matrix);
    free_sparse_matrix(&smatrix);
    printf("OK\n");
    return 0;
}