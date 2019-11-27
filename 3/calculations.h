#ifndef CALCULATIONS_H
#define CALCULATION_H

#include "definitions.h"

void sparse_multiplication(sparse_matrix matr, sparse_vector vector, int *res_vector, int size);
void classic_multiplication(int* matrix, int* vector , int* result, int rows, int columns);
void calculate_and_measure(int *vector, int *res_vector, int rows, int columns, int* matrix, sparse_matrix smatrix);
void swap(int *a, int *b);

#endif 