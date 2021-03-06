#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define ERROR_NONE 0
#define ERROR_INPUT 1
#define ERROR_MEMORY 2
#define ERROR_OTHER 3

#define MAX_MATRIX_SIZE 1000000

typedef struct node *node_ptr;
typedef node_ptr list;

struct node
{
    int Nk;
    node_ptr next;
}; 

struct sparse_matrix
{
    int *A;
    int *IA;
    list JA;
};

struct sparse_vector
{
    int *A;
    int *IA;
    int size;
};

typedef struct sparse_matrix sparse_matrix;
typedef struct sparse_vector sparse_vector;

#endif