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
    int error = ERROR_NONE;
 
    SMATRIX s_matrix1, s_matrix2, s_matrix3;

    int *matrix1, *matrix2;

    int fill_perc = 50; // filling %
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
            // Allocating memory and converting matrixes into sparse vector form
            count_non_zero(matrix1, rows, columns, &non_zero_row_1, &non_zero_num_1);
            alloc_sparse_matrix_vectors(&s_matrix1, non_zero_num_1);
            alloc_sparse_matrix_list(&s_matrix1, rows);
            convert_matrix(matrix1, &s_matrix1, rows, columns);

            int choice = -1;

            int* vector; 
            int* res_vector;

            while (choice != 0)
            {
                system("cls");
                printf("matrix: \n");

                if (rows < 10 && columns < 10)
                    print_matrix(matrix1, rows, columns);
                if (rows < 50 && columns < 50)
                    print_sparse_matrix(&s_matrix1, non_zero_num_1, non_zero_row_1);

                print_menu();
                fflush(stdin);
                if (scanf("%d", &choice) == 1)
                {
                    switch(choice)
                    {
                        case 1:
                            if (matrix_alloc(&vector, rows) == ERROR_NONE)
                            {
                                SMATRIX s_vector, s_res_vector;
                                matrix_alloc(&res_vector, rows);
                                printf("Do you want to fill vector manually? y/N\n");
                                fflush(stdin);
                                if (scanf("%c", &ch) == 1)
                                {
                                    if (ch == 'y' || ch == 'Y')
                                        manual_fill_vector(vector, rows);
                                    else
                                    {
                                        int fill_perc2 = 100; 
                                        auto_fill_vector(vector, rows, fill_perc2);
                                    }

                                    printf("\nvector:\n");
                                    print_vector(vector, rows);

                                    count_non_zero(vector, 1, rows, &non_zero_row_2, &non_zero_num_2);
                                    alloc_sparse_matrix_vectors(&s_matrix2, non_zero_num_2);
                                    alloc_sparse_matrix_list(&s_matrix2, 1);
                                    convert_matrix(res_vector, &s_matrix2, 1, rows);

                                    sparse_multiplication(s_matrix1, vector, res_vector, rows);

                                    printf("\nresult:\n");
                                    print_vector(res_vector, rows);


                                    printf("\nsparse result:");
                                    print_sparse_matrix(&s_matrix2, non_zero_num_2, 1);
                                }
                                else
                                {
                                    printf("Wrong Input\n");
                                    error = ERROR_INPUT;
                                }
                            }

                            free(vector);
                            free(res_vector);
                            free_sparse_matrix(&s_matrix2);
                            system("pause");
                            break;

                        case 2:
                            if (matrix_alloc(&vector, rows) == ERROR_NONE)
                            {
                                matrix_alloc(&res_vector, rows);
                                printf("Do you want to fill vector manually? y/N\n");
                                fflush(stdin);
                                if (scanf("%c", &ch) == 1)
                                {
                                    if (ch == 'y' || ch == 'Y')
                                        manual_fill_vector(vector, rows);
                                    else
                                    {
                                        int fill_perc2 = 100; 
                                        auto_fill_vector(vector, rows, fill_perc2);
                                    }

                                    printf("\nvector:\n");
                                    print_vector(vector, rows);

                                    classic_multiplication(matrix1, vector, res_vector, rows, columns);
                                    
                                    printf("\nresult:\n");
                                    print_vector(res_vector, rows);
                                }
                                else
                                {
                                    printf("Wrong Input\n");
                                    error = ERROR_INPUT;
                                }
                            }
                            
                            free(vector);
                            free(res_vector);
                            system("pause");
                            break;
                        case 3:
                            //USE BOTH FUNCTIONS ABOVE TO COUNT TIME
                            //CALCULATE EFFICIENCY
                            //RESULT
                            system("pause");
                            break;
                        default:
                            if (choice != 0)
                            {
                                printf("WARNING: select one of the options\n");
                                system("pause");
                            }
                            
                            break;
                    }
                }
                else
                {
                    printf("wrong input\n");
                    fflush(stdin);
                }
            }
        }
    }
    else
    {
        printf("Wrong input\n");
        error = ERROR_INPUT;
    }

    free_sparse_matrix(&s_matrix1);
    matrix_free(matrix1);
    printf("OK\n");
    return error;
}