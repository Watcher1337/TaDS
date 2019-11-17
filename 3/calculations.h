#ifndef CALCULATIONS_H
#define CALCULATION_H

#include "definitions.h"

void sparse_multiplication(SMATRIX matr, int *vector, int *res_vector, int size);
void classic_multiplication(SMATRIX A, SMATRIX B, SMATRIX res);

#endif