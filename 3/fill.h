#ifndef FILL_H
#define FILL_H

#include "definitions.h"
 
void auto_fill_matrix(int *matrix, int rows, int columns, int percent);
void manual_fill_matrix(int *matrix, int rows, int columns);
int convert_matrix(int *matrix, SMATRIX *sm, int rows, int columns);
void count_non_zero(int *matrix, int rows, int columns, int *nzr, int *nzn);
void fill();

#endif 