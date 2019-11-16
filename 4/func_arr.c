#include <stdio.h>
#include <stdlib.h>

#include "func_arr.h"

STACK_ARR create_stack_r(int max_elements, int *error)
{
    STACK_ARR S;
     
    if(max_elements < 1)
        printf("Stack size is too small\n");
    
    S = (STACK_ARR)malloc(sizeof(struct stack_record));
    if(S == NULL)
    {
        *error = ERROR_ERROR; 
        printf("Memory allocation error\n");
    }
    S->stack_array = (char *)malloc(sizeof(char) * max_elements);
    
    if(S->stack_array == NULL)
    {
        *error = ERROR_ERROR;
        printf("Memory allocation error\n");
    }

    S->stack_size = max_elements;
    S->curr_ptr = S->stack_array - 1;
    S->stack_size = 0;
    
    return(S);
}

int is_empty_r(STACK_ARR S)
{
    return (S->curr_ptr == S->stack_array - 1);
}

void push_r(char x, STACK_ARR S)
{
    if(S->curr_ptr > S->stack_array + S->stack_size - 1)
        printf("Full stack");
    else
    {
        S->curr_ptr++;
        *(S->curr_ptr) = x;
        S->stack_size++;
    }
}

char top_r(STACK_ARR S)
{
    if(is_empty_r(S))
        printf("Empty stack\n");
    else
        return *(S->curr_ptr);
}

void pop_r(STACK_ARR S)
{
    if(is_empty_r(S))
        printf("Empty stack\n");
    else
        S->curr_ptr--;
}

void free_stack_r(STACK_ARR stack)
{
    free(stack->stack_array);
    free(stack);
}

void empty_stack_r(STACK_ARR stack)
{
    while(!is_empty_r(stack))
        pop_r(stack);
}

void display_stack_r(STACK_ARR data, int stack_size)
{
    int *save = (int *)malloc(sizeof(int) * stack_size);

    if (save)
    {
        for (int i = 0; i < stack_size; i++)
        {
            save[i] = top_r(data);
            printf("%c\n", save[i]);
            pop_r(data);
        }

        for (int i = stack_size - 1; i >= 0; i--)
        {
            push_r(save[i], data);
            data->stack_size--;
        }
    }
    else
    {
        printf("Memory allocation error\n");
    }
}

int push_expression_r(char *buffer, STACK_ARR data, int *error)
{
    fseek(stdin, SEEK_END, 0);
    printf("Enter expression containing () {} or [] brackets: ");
    gets(buffer);

    int stack_size = 0;
 
    for (int k = 0; buffer[k] != '\0' && *error == ERROR_NONE; k++)
    {
        int sym = buffer[k];

        if ((sym == '(') || (sym == '{') || (sym == '[') || (sym == ')') || (sym == '}') || (sym == ']'))
        {
            push_r(sym, data);
            stack_size++;
        }
    }

    return stack_size;
}

void check_expression_r(STACK_ARR data, int stack_size, int *error)
{
    int mismatch[3] = {0, 0, 0};
    int to_exit = 0;
    while (stack_size > 0)
    {
        char b = top_r(data);
        pop_r(data);

        if (b != -1 && to_exit == 0)
        {
            switch (b)
            {
            case '{':
                if (mismatch[0] == 0)
                    to_exit = 1;
                mismatch[0]++;
                break;
            case '(':
                if (mismatch[1] == 0)
                    to_exit = 1;
                mismatch[1]++;
                break;
            case '[':
                if (mismatch[2] == 0)
                    to_exit = 1;
                mismatch[2]++;
                break;

            case '}':
                mismatch[0]--;
                break;
            case ')':
                mismatch[1]--;
                break;
            case ']':
                mismatch[2]--;
                break;

            default:
                break;
            }            
        }

        stack_size--;
    }

    if (mismatch[0] != 0 || mismatch[1] != 0 || mismatch[2] != 0 || to_exit)
        printf("WRONG\n\n");
    else
        printf("CORRECT\n\n");
}