#include "includes.h"
#include "measures.h"

void compare_time(queue_arr *q_arr, queue_list *q_list);

//For internal tests ONLY
void test_list(queue_list *q_list)
{
    printf("filling list\n");
    for (int i = 65; i < 90; i++)
        push_list(q_list, (char)i);
    printf("list filled\n");
    print_list(q_list);
    printf("list displayed\n");

    for (int i = 0; i < 10; i++)
        printf("pop List: %c\n", pop_list(q_list));
}

//For internal tests ONLY
void test_arr(queue_arr *q_arr)
{
    printf("filling array\n");
    for (int i = 65; i < 90; i++)
        push_arr(q_arr, (char)i);
    printf("array filled\n");
    print_arr(q_arr);
    printf("array displayed\n");

    for (int i = 0; i < 10; i++)
        printf("pop Arr: %c\n", pop_arr(q_arr));
} 