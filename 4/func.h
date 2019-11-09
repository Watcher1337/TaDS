#ifndef FUNC_H
#define FUNC_H

#define ERROR_NONE 0
#define ERROR_ERROR 1

#define BUFF_SIZE 256
#define MAX_STACK_SIZE 10000

#include "func_arr.h"

typedef struct node *node_ptr;
typedef node_ptr STACK;

struct node
{
    char expression;
    node_ptr next;
};

int is_empty(STACK S);
STACK create_stack(int *error);
void make_null(STACK S);
void empty_stack(STACK data);
void push(char x, STACK S, int *error);
void pop(STACK S);
char top(STACK S);
void check_expression(STACK data, int stack_size, int *error);
int push_expression(char *buffer, STACK data, int *error);
void compare_stacks(STACK data_list, STACK_ARR data_array, int *error);
void print_menu();

#endif