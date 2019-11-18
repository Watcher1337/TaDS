#ifndef LIST_H
#define LIST_H

#include "definitions.h"

int is_empty(list JA); // checks if JA in given smatrix is empty
void pop(list JA); // removes top element from smatrix's linked list JA
void display_list(node_ptr start);
int get_element(node_ptr start, int position);

#endif 