#ifndef PRINTS_H
#define PRINTS_H

#include "definitions.h"
#include "list.h"

void print_matrix(int *matrix, int rows, int columns);
void print_sparse_matrix(sparse_matrix *sm, int non_zero_num);
void print_vector(int *vector, int size);
void print_menu();
 
#endif 