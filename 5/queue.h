#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue_array queue_arr;
typedef struct queue_list queue_list;
typedef struct node node;
typedef struct free_zone free_zone;

struct free_zone
{
    void **free_area;

    int freed;
    int reused;
};

//Represents cycling queue through array
struct queue_array
{
    void *p_in; //Element to be put into queue
    void *p_out; //Element to pop
    void *p_low; //Stores lower border of array
    void *p_high;

    char *arr; //King himself
    int max_size;
    int curr_size;
    int out; //Counts processed elements
    int in; //Counts entering elements
};
  
struct queue_list 
{ 
    int max_size;
    int curr_size;
    int in;
    int out;
    struct node *front, *rear; 
}; 

struct node
{
    char data;
    node *next;
};

void push_list(queue_list *q, char a);
int push_arr(queue_arr *q_arr, char c);

queue_list* alloc_list();
node* create_node(char a);
int alloc_arr(queue_arr *q_arr, int amount);

char pop_arr(queue_arr *q_arr);
char pop_list(queue_list *q_list);

int is_empty_list(queue_list *q_list);
int is_empty_arr(queue_arr *q_arr);

void free_list(queue_list *q_list);
void free_arr(queue_arr *q_arr);

int is_empty_list(queue_list *q_list);
int is_empty_arr(queue_arr *q_arr);

void init_free_area();
void free_free_area();
void show_free_area();

#endif