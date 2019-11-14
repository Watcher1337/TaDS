#ifndef FUNC_H
#define FUNC_H

#define ERROR_NONE 0
#define ERROR_ERROR 1

#define BUFF_SIZE 256
#define FREE_AREA 100
 
#include "func_arr.h"

typedef struct node *node_ptr;
typedef node_ptr STACK; 

void init_free_area();

struct node
{
    char expression;
    node_ptr next;
};

int is_empty(STACK S);
STACK create_stack(int *error);
void empty_stack(STACK data);
void push(char x, STACK S, int *error);
void pop(STACK S, int flag);
char top(STACK S);
void check_expression(STACK data, int stack_size, int *error);
int push_expression(char *buffer, STACK data, int *error);
void display_stack(STACK data);
void print_menu();

#endif