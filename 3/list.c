#include <stdio.h>
#include <stdlib.h>
 
#include "definitions.h"
#include "list.h"

void pop(JA_LIST JA)
{ 
    if (is_empty(JA))
        printf("List is empty\n");
    else
    {
        printf("free\n");
        node_ptr first = JA->next;
        JA->next = JA->next->next;
        free(JA);
    }
}

int is_empty(JA_LIST JA)
{
    return(JA->next == NULL); 
}

void display_list(node_ptr start)
{
    while (start)
    {
        printf("1)%d ", start->Nk);
        start = start->next;
    }
    printf("\n");
}