#include <stdio.h>
#include <stdlib.h>

#include "alloc.h"

int matrix_alloc(int **vector, int size)
{
    int error = ERROR_NONE;
    *vector = (int *)calloc(size, sizeof(int));

    if (!(*vector))
    {
        printf("Memory allocation error\n");
        error = ERROR_MEMORY;
    }

    return error;
}

void matrix_free(int *vector)
{
    free(vector);
}

int matrix_packed_alloc(SMATRIX sm, int rows, int columns)
{
    
}

void matrix_packed_free(int *A, int *JA, LIST IA)
{

}

void vector_realloc(int *vector, int target_size); //UNUS