#ifndef ALLOC_H
#define ALLOC_H

#include "definitions.h"

int matrix_alloc(int **vector, int size);
void matrix_free(int *vector);
void matrix_packed_alloc(int *A, int *JA);
void matrix_packed_free(int *A, int *JA, LIST IA);
void vector_realloc(int *vector, int target_size); //UNUS

#endif