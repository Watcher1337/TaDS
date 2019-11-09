#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "func.h"
#include "func_arr.h"

int is_empty(STACK S)
{
    return(S->next == NULL);
}

STACK create_stack(int *error)
{
    STACK S;
    S = (STACK)malloc(sizeof(struct node));
    if(S == NULL)
    {
        printf("Error: memory allocation\n");
        *error = ERROR_ERROR;
    }
    return S;
}

void make_null(STACK S)
{
    if(S != NULL)
        S->next = NULL;
    else
        printf("Must use create_stack first\n");
}

void push(char x, STACK S, int *error)
{
    node_ptr tmp_cell;
    tmp_cell = (node_ptr) malloc(sizeof(struct node));
    if(tmp_cell == NULL)
    {
        printf("Memory allocation error\n");
        *error = ERROR_ERROR;
    }
    else
    {
        tmp_cell->expression = x;
        tmp_cell->next = S->next;
        S->next = tmp_cell;
    }
}

void pop(STACK S)
{
    node_ptr first_cell;
    if(is_empty(S))
        printf("Empty stack\n");
    else
    {
        first_cell = S->next;
        S->next = S->next->next;
        free(first_cell);
    }
}

char top(STACK S)
{
    if(is_empty(S))
    {
        printf("Empty stack\n");
        return -1;
    }
    else
        return S->next->expression;
}

int push_expression(char *buffer, STACK data, int *error)
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
            push(sym, data, error);
            stack_size++;
        }

        if (stack_size == MAX_STACK_SIZE)
        {
            printf("Error: stack overflow\n");
            *error = ERROR_ERROR; 
            break;
        }
    }

    return stack_size;
}

void check_expression(STACK data, int stack_size, int *error)
{
    int mismatch[3] = {0, 0, 0};
    int to_exit = 0;
    while (stack_size > 0)
    {
        
        char b = top(data);
        pop(data);

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
        printf("expression bracket format is wrong\n\n");
    else
        printf("expression bracket format is correct\n\n");
}

void print_menu()
{
    system("cls");
    printf("\nChoose one of the options below: \n");
    printf("2 - Analyse expression\n");
    printf("3 - Add element to stack (list)\n");
    printf("4 - Pop element from stack (list)\n");
    printf("5 - Display stack status (list)\n");
    printf("----------------------------------\n");
    printf("6 - Add element to stack (array)\n");
    printf("7 - Pop element from stack (array)\n");
    printf("8 - Display stack status (array)\n");
    printf("-----------------------------------\n");
    printf("9 - compare array vs list effectiveness\n");
    printf("0 - exit\n");
}

void compare_stacks(STACK data_list, STACK_ARR data_array, int *error)
{
    empty_stack(data_list);
    empty_stack_r(data_array);

    clock_t time1;
    clock_t time2;
    double current = 0;

    size_t size_list_empty = sizeof(data_list);
    size_t size_list_full = 0;
    char x = 'F';
    for (int i = 0; i < 10000; i++)
    {
        time1 = clock();
        push(x, data_list, error);
        time2 = clock();
        size_list_full += sizeof(data_list);
        current += time2 - time1;
    }
    double push_timer_list = (double)current / CLOCKS_PER_SEC;

    current = 0;
    time1 = clock();
    for (int i = 0; i < 10000; i++)
    {
        pop(data_list);
    }
    time2 = clock();
    current += time2 - time1;  
    double pop_timer_list = (double)current / CLOCKS_PER_SEC;

    current = 0;
    size_t size_array_empty = sizeof(data_array);
    time1 = clock();
    for (int i = 0; i < 1000; i++)
    {
        push_r(x, data_array);
    }
    time2 = clock();
    current += time2 - time1;
    double push_timer_array = (double)current / CLOCKS_PER_SEC;
    size_t size_array_full = data_array->stack_size * sizeof(char);

    current = 0;
    time1 = clock();
    for (int i = 0; i < 1000; i++)
    {
        pop_r(data_array);
    }
    time2 = clock();
    current += time2 - time1;  
    double pop_timer_array = (double)current / CLOCKS_PER_SEC;

    printf("size of empty list stack: %d\n", size_list_empty);
    printf("size of empty array stack: %d\n", size_array_empty);
    printf("size of full list stack: %d\n", size_list_full);
    printf("size of full array stack: %d\n", size_array_full);
    printf("\ntime to fill 1000 list-stack elements: %lf\n", push_timer_list);
    printf("time to fill 1000 array-stack elements: %lf\n", push_timer_array);
    printf("\ntime to empty 1000 list-stack elements: %lf\n", pop_timer_list);
    printf("time to empty 1000 array-stack elements: %lf\n", pop_timer_array);
}

void empty_stack(STACK data)
{
    while (!is_empty(data))
        pop(data);
}