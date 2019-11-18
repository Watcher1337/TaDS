#ifndef CALCULATIONS_H
#define CALCULATION_H

#include "definitions.h"

void sparse_multiplication(SMATRIX matr, int *vector, int *res_vector, int size);
void classic_multiplication(int* matrix, int* vector , int* result, int rows, int columns);

#endif