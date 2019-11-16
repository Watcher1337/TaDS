#include <stdio.h>
#include <stdlib.h>

typedef struct node * node_ptr;
typedef node_ptr JA_LIST;

struct node
{
    int x;
    node_ptr next;
};

node_ptr getLast(node_ptr head); 
void pushBack(node_ptr head, int value);
void printLinkedList(node_ptr head);


void pushBack(node_ptr head, int value)
{
    node_ptr last = getLast(head);
    node_ptr tmp = (node_ptr) malloc(sizeof(struct node));
    tmp->x = value;
    tmp->next = NULL;
    last->next = tmp;
}

node_ptr getLast(node_ptr head) 
{
    printf("in");
    if (head == NULL) 
        return NULL;

    while (head->next) 
        head = head->next;
    
    return head;
}

void printLinkedList(node_ptr head) {
    printf("1");
    while (head) 
    {
        printf("%d ", head->x);
        head = head->next;
    }
    printf("2\n");
}

int main()
{
    JA_LIST list = (node_ptr)malloc(sizeof(struct node));

    for (int i = 0; i < 10; i++)
        pushBack(list, i);
    
    printLinkedList(list);

    free(list);
    system("pause");
    return 0;
}
