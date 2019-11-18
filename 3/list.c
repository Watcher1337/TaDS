#include <stdio.h>
#include <stdlib.h>
 
#include "definitions.h"
#include "list.h"

int is_empty(list JA)
{
    return(JA->next == NULL); 
}

void display_list(node_ptr start)
{
    while (start != NULL)
    {
        printf("%d ", start->Nk);
        start = start->next;
    }
}

int get_element(node_ptr start, int position)
{
    int count = 0;
    while (count < position)
    {
        start = start->next;
        count++;
    }
    return start->Nk; 
}