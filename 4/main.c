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


    char buffer[BUFF_SIZE];
    
    int choice = 1;
    int stack_created = 0;
    int stack_size_list = 0;
    int exp_info_size = 0;
    //STACK *list_addr = (STACK *)malloc(sizeof(STACK *) * MAX_STACK_SIZE);
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
            case 2:
                exp_info_size = push_expression(buffer, data_list, &error);

                if (exp_info_size == 0)
                    printf("Warning: You should input at least one bracket\n");
                else if (exp_info_size + stack_size_list > MAX_STACK_SIZE)
                {
                    printf("Stack overflow\n");
                    //error = ERROR_ERROR;
                }
                else if (error == ERROR_NONE)
                    check_expression(data_list, exp_info_size, &error);
                system("pause");
                break;

            case 3:
                if (stack_size_list == MAX_STACK_SIZE)
                    printf("Stack is full\n");
                else
                {
                    fseek(stdin, SEEK_END, 0);
                    printf("Enter a single character: ");
                    if (scanf("%c", &x) == 1 && x != '\n' && x != ' ')
                    {
                        push(x, data_list, &error);
                        //list_addr[stack_size_list] = data_list->next;
                        list_address[stack_size_list] = data_list->next;
                        stack_size_list++; // add address records
                    }
                    else
                        printf("Error: Wrong input\n");
                }
                system("pause");
                break; 

            case 4: 
                if (stack_size_list > 0)
                    stack_size_list--;
                pop(data_list);
                system("pause");
                break;

            case 5:
                if (!is_empty(data_list))
                {
                    printf("Top element of list stack is %c \n", top(data_list));
                    printf("Total list stack elements: %d\n", stack_size_list);
                    printf("Elements in the stack, top to bottom: \n");
                    display_stack(data_list, stack_size_list);
                    printf("\nAddresses:\n");
                    for (int i = 0; i < stack_size_list; i++)
                        printf("%zu\n", list_address[i]);
                }
                else
                    printf("List stack is empty\n");
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
                    printf("stack elements, top to bottom: \n");
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
    //printf("address free\n");
    empty_stack_r(data_array);
    //printf("array empty\n");
    free_stack_r(data_array);
    //printf("array free\n");
    empty_stack(data_list);
    //printf("stack empty\n");
    return error; 
}