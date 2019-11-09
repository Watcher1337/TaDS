#include <stdio.h>
#include <stdlib.h>

#include "func_arr.h"
#include "func.h"

STACK_ARR create_stack_r(int max_elements)
{
    STACK_ARR S;
    
    if(max_elements < 1)
        printf("Stack size is too small\n");
    
    S = (STACK_ARR) malloc(sizeof(struct stack_record));
    if(S == NULL)
        printf("Memory allocation error\n");

    S->stack_array = (char *)malloc(sizeof(char) * max_elements);
    
    if(S->stack_array == NULL)
        printf("Memory allocation error\n");
    
    S->top_of_stack = EMPTY_TOS;
    S->stack_size = 0;
    
    return(S);
}

int is_empty_r(STACK_ARR S)
{
    return(S->top_of_stack == EMPTY_TOS);
}

void make_null_r(STACK_ARR S)
{
    S->top_of_stack = EMPTY_TOS;
}

void push_r(char x, STACK_ARR S)
{
    if(S->stack_size == MAX_STACK_SIZE)
        printf("Full stack");
    else
    {
        S->stack_array[++S->top_of_stack] = x;
        S->stack_size++;
    }
}

char top_r(STACK_ARR S)
{
    if(is_empty_r(S))
        printf("Empty stack\n");
    else
        return S->stack_array[S->top_of_stack];
}

void pop_r(STACK_ARR S)
{
    if(is_empty_r(S))
        printf("Empty stack\n");
    else
        S->top_of_stack--;
}

void free_stack_r(STACK_ARR stack)
{
    free(stack->stack_array);
}

void empty_stack_r(STACK_ARR stack)
{
    while(!is_empty_r(stack))
        pop_r(stack);
}