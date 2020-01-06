#include "includes.h"
#include "queue.h"
#include "measures.h"

int main()
{
    srand(time(NULL));
    int error = ERROR_NONE;

    queue_arr *q_arr = (queue_arr *)malloc(sizeof(queue_arr));
    queue_list *q_list = (queue_list *)malloc(sizeof(queue_list));

    alloc_list(q_list);
    alloc_arr(q_arr, ARR_SIZE);

    //test_list(q_list);
    //test_arr(q_arr);

    free_list(q_list);
    free(q_list);
    printf("list freed\n");
    free_arr(q_arr);
    free(q_arr);
    printf("arr freed\n");

    return error;
} 