#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define ERROR_NONE 0
#define ERROR_INPUT 1
#define ERROR_MEMORY 2
#define ERROR_OTHER 3

#define MAX_MATRIX_SIZE 100000

typedef struct node *node_ptr;
typedef node_ptr JA_LIST;

struct node
{
    int Nk;
    node_ptr next;
}; 

struct sparse_matrix
{
    int* A;
    int* IA;
    JA_LIST JA;
};

typedef struct sparse_matrix SMATRIX;

#endif