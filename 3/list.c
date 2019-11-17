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
        start = start->next;
    return start->Nk; 
}


int Multiplicate(SMATRIX sm, int row, double *x, double *b)
{
    for (int i = 0; i < row; i++)
    {
        b[i] = 0.0;
        for (int j=get_element(sm.JA, i); j<get_element(sm.JA, i + 1); j++)
            b[i] += sm.A[j] * x[sm.IA[j]];
    }

    return 0;
}
