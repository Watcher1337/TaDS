#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "func_list.h"
#include "func_arr.h"

static void **free_area;
static int n;

int is_empty(STACK S)
{
    return (S->next == NULL);
} 

void init_free_area()
{
    free_area = calloc(FREE_AREA, sizeof(void *));
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

void pop(STACK S, int flag)
{
    node_ptr first_cell;
    if(is_empty(S))
        printf("Empty stack\n");
    else
    {
        first_cell = S->next;
        S->next = S->next->next;

        if (flag)
            free_area[n++] = (void *)first_cell;

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
        pop(data, 0);

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

void print_menu()
{
    system("cls");
    printf("\nChoose one of the options below: \n");
    printf("1 - Analyse expression (list)\n");
    printf("2 - Add element to stack (list)\n");
    printf("3 - Pop element from stack (list)\n");
    printf("4 - Display stack status (list)\n");
    printf("----------------------------------\n");
    printf("5 - Analyse expression (array)\n");
    printf("6 - Add element to stack (array)\n");
    printf("7 - Pop element from stack (array)\n");
    printf("8 - Display stack status (array)\n");
    printf("-----------------------------------\n");
    printf("9 - compare array vs list effectiveness\n");
    printf("0 - exit\n");
}

void empty_stack(STACK data)
{
    while (!is_empty(data))
        pop(data, 1);
    free(free_area);
}

void display_stack(STACK data)
{
    node_ptr curr = data->next;

    printf("stack elements:\n");
    while (curr != NULL)
    {
        printf("%c (%p)\n", curr->expression, curr);
        curr = curr->next;
    }

    printf("free zone adresses:\n");
    for (int i = 0; i < n; i++)
        printf("%p ", free_area[i]);
    puts("");
}