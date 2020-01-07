#include "includes.h"
#include "queue.h"

int alloc_list(queue_list *q_list)
{
    int error = ERROR_NONE;
    q_list->list = (node *)malloc(sizeof(node));

    if (!q_list->list)
        error = ERROR_MEMORY;
    else
    {
        q_list->list->next = NULL;
        q_list->curr_size = 0;
        q_list->p_in = q_list->list;
    }

    return error;
} 

int alloc_arr(queue_arr *q_arr, int amount)
{
    int error = ERROR_NONE;
    q_arr->arr = (char *)malloc(amount);

    if (!q_arr->arr)
        error = ERROR_MEMORY;
    else
    { 
        q_arr->max_size = amount;
        q_arr->curr_size = 0;
        q_arr->p_in = q_arr->arr;
        q_arr->p_out = q_arr->arr;
        q_arr->p_low = q_arr->arr; //Low border of cycling queue
        q_arr->p_high = q_arr->arr + amount; //High border
    }

    return error;
}

int push_list(queue_list *q_list, char c)
{
    int error = ERROR_NONE;    
    node *tmp = (node *)malloc(sizeof(node));
    
    if (tmp)
    {
        tmp->data = c;
        tmp->next = NULL;

        q_list->p_in->next = tmp;
        q_list->p_in = tmp;
        q_list->curr_size++;
    }

    return error;
}

int push_arr(queue_arr *q_arr, char c)
{
    int error = ERROR_NONE;
    *(char *)q_arr->p_in = c;
    q_arr->curr_size++;
    q_arr->p_in += sizeof(char);

    if (q_arr->p_in >= q_arr->p_high)
        q_arr->p_in = q_arr->p_low;
    
    if (q_arr->curr_size == q_arr->max_size)
        error = ERROR_QUE_OVERFLOW;

    q_arr->in++;

    return error;
}

char pop_arr(queue_arr *q_arr)
{
    char ret;

    if (q_arr->curr_size != 0)
    {
        ret = *(char *)q_arr->p_out;
        q_arr->curr_size--;

        q_arr->p_out += sizeof(char);

        if (q_arr->p_out >= q_arr->p_high)
            q_arr->p_out = q_arr->p_low;
        
        q_arr->out++;
    }

    return ret;
}

char pop_list(queue_list *q_list)
{
    char ret;

    if (q_list->list->next != NULL)
    {
        node *tmp = q_list->list->next;
        ret = q_list->list->next->data;
        q_list->list->next = q_list->list->next->next;
        
        free(tmp);
        q_list->curr_size--;
    }
    else
        printf("queue is empty\n");

    return ret;
}

void free_list(queue_list *q_list)
{
    while (q_list->curr_size > 0)
        pop_list(q_list); // freeing all elements
    
    free(q_list->list); // freeing root
}

void free_arr(queue_arr *q_arr)
{
    free(q_arr->arr);
}

int is_empty_list(queue_list *q_list)
{
    return (q_list->list->next == NULL);
}

int is_empty_arr(queue_arr *q_arr)
{
    return (q_arr->curr_size == 0);
}