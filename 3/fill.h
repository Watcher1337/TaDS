#ifndef FILL_H
#define FILL_H

#include "definitions.h"
 
void auto_fill_matrix(int *matrix, int rows, int columns, int percent);
void manual_fill_matrix(int *matrix, int rows, int columns);
int convert_matrix(int *matrix, sparse_matrix *sm, int rows, int columns);
void convert_vector(int *vector, sparse_vector *svector, int size);
void count_non_zero(int *matrix, int rows, int columns, int *nzn);
void manual_fill_vector(int *vector, sparse_vector *svector, int size);

#endif 