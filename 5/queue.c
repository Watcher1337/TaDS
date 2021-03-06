#include "includes.h"
#include "queue.h"

free_zone free_area;

void init_free_area()
{
    free_area.free_area = calloc(MAX_QUEUE_SIZE, sizeof(void *));
    free_area.freed = 0;
    free_area.reused = 0;
}

void free_free_area()
{
    free(free_area.free_area);
}

void show_free_area()
{
    printf("Still available memory: %d\n", free_area.freed);
    printf("Reused memory: %d\n", free_area.reused);

    printf("Free adresses: \n");
    for (int i = 0; i < (free_area.freed < 20 ? free_area.freed : 20); i++)
    {
        printf("%p\n", free_area.free_area[i]);
    }
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
        q_arr->in = 0;
        q_arr->out = 0;
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

node *create_node(char a) 
{ 
    node *temp = (node*)malloc(sizeof(node)); 
    temp->data = a; 
    temp->next = NULL; 
    return temp; 
} 
  
queue_list *alloc_list() 
{ 
    queue_list *q = (queue_list *)malloc(sizeof(queue_list)); 
    q->front = q->rear = NULL; 
    q->curr_size = 0;
    q->in = 0;
    q->out = 0;

    return q;
}
  
void push_list(queue_list *q, char a) 
{ 
    node *temp = create_node(a); 
    int flag = FALSE;

    for (int i = 0; i < free_area.freed; i++)
    {
        if (free_area.free_area[i] == (void *)temp)
        {
            free_area.free_area[i] = NULL;
            flag = TRUE;
        }

        if (flag == TRUE)
            free_area.free_area[i] = free_area.free_area[i+1];
    }

    if (flag == TRUE)
    {
        free_area.freed--;
        free_area.reused++;
    }

    if (q->rear == NULL) 
    { 
        q->curr_size++;
        q->front = q->rear = temp; 
        return; 
    } 

    q->curr_size++;
    q->in++;

    q->rear->next = temp; 
    q->rear = temp; 
} 
  
char pop_list(queue_list *q) 
{
    node *temp;
    char ret = 'x'; 
    if (q->front == NULL) 
        printf("queue is empty\n");
    else
    {
        temp = q->front; 
        ret = temp->data;

        q->front = q->front->next; 
    
        if (q->front == NULL) 
            q->rear = NULL; 

        free_area.free_area[free_area.freed++] = (void *)temp;

        free(temp);
        q->curr_size--;
        q->out++;
        
    }

    return ret; 
} 

void free_list(queue_list *q_list)
{
    while (q_list->curr_size > 0)
        pop_list(q_list); // freeing all elements
    
    free(q_list); // freeing root
}

void free_arr(queue_arr *q_arr)
{
    free(q_arr->arr);
}

int is_empty_list(queue_list *q_list)
{
    return (q_list->rear == NULL);
}

int is_empty_arr(queue_arr *q_arr)
{
    return (q_arr->curr_size == 0);
}