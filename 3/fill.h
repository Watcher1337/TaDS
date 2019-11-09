#ifndef FILL_H
#define FILL_H

#include "definitions.h"

void auto_fill_matrix(int *matrix, int rows, int columns, int percent);
void manual_fill_matrix(int *matrix, int rows, int columns);
void convert_matrix(int *matrix, SMATRIX sm, int rows, int columns);
void fill();

#endif