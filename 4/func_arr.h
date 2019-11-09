#ifndef FUNC_ARR_H
#define FUNC_ARR_H

#define BUFF_SIZE 256
#define EMPTY_TOS (-1)

typedef struct stack_record *STACK_ARR;

struct stack_record
{
    int stack_size;
    int top_of_stack;
    char *stack_array;
};

int is_empty_r(STACK_ARR S);
STACK_ARR create_stack_r(int max_elements);
void make_null_r(STACK_ARR S);
void push_r(char x, STACK_ARR S);
void pop_r(STACK_ARR S);
char top_r(STACK_ARR S);
void empty_stack_r(STACK_ARR stack);
void free_stack_r(STACK_ARR stack);

#endif