#include "prints.h"

void print_arr(queue_arr *queue_arr)
{
    for (int i = 0; i < queue_arr->curr_size; i++)
        printf("arr element: %c\n", queue_arr->arr[i]);
    printf("\n");
}

int choose_menu(int *error)
{
    int choice = 0;
    printf("\nChoose one of the options: \n");
    printf("1 - change request parameters\n");
    printf("2 - list processing\n");
    printf("3 - array processing\n");
    printf("4 - memory fragmentation state\n");
    printf("0 - exit\n");

    if (scanf("%d", &choice) != 1)
        *error = ERROR_INPUT;

    return choice;
}

void print_resulting_error_code(int error)
{
    switch (error)
    {
        case ERROR_NONE:
            printf("Ok\n");
            break;
        case ERROR_INPUT:
            printf("Input error\n");
            break;
        case ERROR_MEMORY:
            printf("Memory error\n");
            break;
        default:
            break;
    }
}

void show_memory_reuse_state()
{
    printf("Work in progress\n");
    int k;
    scanf("%d", &k);
}
