#include <stdio.h>
#include <stdlib.h>

#include "func_list.h"
#include "func_arr.h"
#include "compare.h"

int main()
{
    int error = ERROR_NONE;

    STACK data_list;
    data_list = create_stack(&error);
    data_list->next = NULL;

    STACK_ARR data_array; 
    data_array = create_stack_r(MAX_STACK_SIZE, &error);

    init_free_area();

    char buffer[BUFF_SIZE];
    
    int choice = 1;
    int stack_created = 0;

    int exp_info_size = 0;

    node_ptr *list_address = (node_ptr *)malloc(sizeof(node_ptr) * MAX_STACK_SIZE);
    
    if (list_address == NULL)
    {
        printf("Allocation error\n");
        error = ERROR_ERROR;
    }
    
    char x;

    while (choice != 0 && error == ERROR_NONE)
    {
        print_menu();
        fflush(stdin);
        if (scanf("%d", &choice) == 1)
            switch (choice)
            {
            case 1:
                exp_info_size = push_expression(buffer, data_list, &error);

                if (exp_info_size == 0)
                    printf("Warning: You should input at least one bracket\n");
                else if (error == ERROR_NONE)
                    check_expression(data_list, exp_info_size, &error);
                system("pause");
                break;

            case 2:
                fseek(stdin, SEEK_END, 0);
                printf("Enter a single character: ");
                if (scanf("%c", &x) == 1 && x != '\n' && x != ' ')
                    push(x, data_list, &error);
                else
                    printf("Error: Wrong input\n");
                system("pause");
                break; 

            case 3: 
                pop(data_list, 1);
                system("pause");
                break;

            case 4:
                if (!is_empty(data_list))
                {
                    printf("Top element of list stack is %c \n", top(data_list));
                    display_stack(data_list);
                }
                else
                    printf("List stack is empty\n");
                system("pause");
                break;

            case 5:
                exp_info_size = push_expression_r(buffer, data_array, &error);

                if (exp_info_size == 0)
                    printf("Warning: you should input at least one bracket\n");
                else if (error == ERROR_NONE)
                    check_expression_r(data_array, exp_info_size, &error);
                system("pause");
                break;

            case 6:
                if ((data_array->stack_size) == MAX_STACK_SIZE)
                {
                    printf("Array stack is full\n");
                }
                else
                {
                    fseek(stdin, SEEK_END, 0);
                    printf("Enter a single character: ");
                    if (scanf("%c", &x) == 1 && x != '\n' && x != ' ')
                    {
                        push_r(x, data_array);
                    }
                    else
                        printf("Error: Wrong input\n");
                }
                system("pause");
                break;

            case 7:
                if (data_array->stack_size > 0)
                    data_array->stack_size--;
                pop_r(data_array);
                system("pause");
                break;

            case 8:
                if (!is_empty_r(data_array))
                {
                    printf("Top element of array stack is %c \n", top_r(data_array));
                    printf("Total elements in array stack: %d\n", ((data_array->curr_ptr - data_array->stack_array)) + 1);
                    printf("stack elements: \n");
                    display_stack_r(data_array, data_array->stack_size);
                }
                else
                    printf("Array stack is empty\n");
                system("pause");
                break;

            case 9:
                compare(1000, &error);
                if (error == ERROR_NONE)
                    compare(10000, &error);
                system("pause");
                break;
                
            default:
                break;
            }
        else
        {
            printf("Wrong input\n");
            system("pause");
        }
    }

    free(list_address);
    empty_stack_r(data_array);
    free_stack_r(data_array);
    empty_stack(data_list);
    return error; 
}