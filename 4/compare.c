#include <stdio.h>
#include <time.h>

#include "compare.h"
#include "func_arr.h"
#include "func_list.h"

unsigned long long tick(void)
{
    unsigned long long tmp;
    __asm __volatile__ ("rdtsc" : "=A" (tmp) );
    return tmp;
}

void compare(int N, int *error)
{
    printf("\nAnalysis for %d elements\n", N);

    unsigned long long duration;
    unsigned long long t1, t2;

    STACK_ARR stack_arr = create_stack_r(N, error);
    STACK stack_list = create_stack(error);
    stack_list->next = NULL;

    printf("--------size comparison--------\n");
    printf("Size of array stack: %d\n", sizeof(stack_arr->stack_array) + sizeof(stack_arr->curr_ptr) + sizeof(char) * N);
    printf("Size of list array: %d to %d\n", sizeof(stack_list), sizeof(stack_list) + sizeof(struct node) * N);

    printf("\n-----push speed comparison-----\n");
    t1 = tick();
    for (int i = 0; i < N; i++)
        push_r('F', stack_arr);
    t2 = tick();
    duration = (unsigned long long)(t2 - t1);

    printf("Array: %llu\n", duration);

    t1 = tick();
    for (int i = 0; i < N; i++)
        push('F', stack_list, error);
    t2 = tick();
    duration = (unsigned long long)(t2 - t1);

    printf("List: %llu\n", duration);

    printf("\n-----pop speed comparison-----\n");
    t1 = tick();
    for (int i = 0; i < N; i++)
        pop_r(stack_arr);
    t2 = tick();
    duration = (unsigned long long)(t2 - t1);

    printf("Array: %llu\n", duration);

    t1 = tick();
    for (int i = 0; i < N; i++)
        pop(stack_list, 0);
    t2 = tick();
    duration = (unsigned long long)(t2 - t1);

    printf("List: %llu\n\n\n", duration);

    free_stack_r(stack_arr);
}