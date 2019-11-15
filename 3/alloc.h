#ifndef ALLOC_H
#define ALLOC_H

#include "definitions.h"

int matrix_alloc(int **vector, int size);
void matrix_free(int *vector);
void vector_realloc(int *vector, int target_size); //UNUSED
void alloc_sparse_matrix_vectors(SMATRIX * sm, int size);
void alloc_sparse_matrix_list(SMATRIX * sm, int size);
void free_sparse_matrix(SMATRIX sm);
 
#endif 