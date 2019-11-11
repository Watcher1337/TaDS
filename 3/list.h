#ifndef LIST_H
#define LIST_H

#include "definitions.h"

void repack_matrix(int *matrix, int rows, int columns, int A, int JA, IA_LIST IA);
int is_empty(IA_LIST IA); // checks if IA in given smatrix is empty
void push(IA_LIST IA)); // adds value to linked list IA in smatrix
void pop(IA_LIST IA); // removes top element from smatrix's linked list IA

#endif