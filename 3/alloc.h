#ifndef ALLOC_H
#define ALLOC_H

#include "definitions.h"

int alloc_vector(int **matrix, int size);
void matrix_free(int *vector);
void vector_realloc(int *vector, int target_size); //UNUSED
void alloc_sparse_matrix_vectors(sparse_matrix * sm, int size);
void alloc_sparse_matrix_list(sparse_matrix * sm, int size);
void free_sparse_matrix(sparse_matrix *sm);
 
#endif 