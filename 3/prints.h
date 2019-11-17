#ifndef PRINTS_H
#define PRINTS_H

#include "definitions.h"
#include "list.h"

void print_matrix(int *matrix, int rows, int columns);
void print_sparse_matrix(SMATRIX *sm, int non_zero_num, int non_zero_row);
void print_menu();
 
#endif 