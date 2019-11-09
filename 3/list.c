#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "definitions.h"

void push(LIST list, int element)
{
    node_ptr temp = (node_ptr)malloc(sizeof(struct node));

    if (temp)
    {
        temp->Nk = element;
        temp->next = list->next;
        list->next = temp;
    }
    else
        printf("Memory allocation error\n");
}

void pop(LIST list)
{
    if (is_empty(list))
        printf("List is empty\n");
    else
    {
        node_ptr first = list->next;
        list->next = list->next->next;
        free(first);
    }
}

int is_empty(LIST list)
{
    return(list->next == NULL);
}