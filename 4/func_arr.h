#ifndef FUNC_ARR_H
#define FUNC_ARR_H

#define ERROR_NONE 0
#define ERROR_ERROR 1

#define BUFF_SIZE 256
#define EMPTY_TOS (-1)

typedef struct stack_record *STACK_ARR;

struct stack_record
{
    int stack_size;
    char *stack_array;
    char *curr_ptr;
};

int is_empty_r(STACK_ARR S);
STACK_ARR create_stack_r(int max_elements, int *error);
void push_r(char x, STACK_ARR S);
void pop_r(STACK_ARR S);
char top_r(STACK_ARR S);
void empty_stack_r(STACK_ARR stack);
void free_stack_r(STACK_ARR stack);

#endif