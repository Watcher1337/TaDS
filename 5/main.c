#include "includes.h"
#include "processor.h"
#include "queue.h"
#include "prints.h"
#include "measures.h"

int main()
{
    srand(time(NULL));
    int error = ERROR_NONE;

    request_params params;
    set_default_request_params(&params);

    queue_arr *q_arr = (queue_arr *)malloc(sizeof(queue_arr));
    queue_list *q_list = (queue_list *)malloc(sizeof(queue_list));

    error = alloc_list(q_list);
    
    if (error == ERROR_NONE)
        error = alloc_arr(q_arr, ARR_SIZE);
    
    int option = -1;

    while (option != 0 && error == ERROR_NONE)
    {
        option = choose_menu(&error);
        
        switch(option)
        {
            case 1:
                change_request_params(&params);
                break;
            case 2:
                simulate_processing_list(&params, q_list);
                break;
            case 3:
                simulate_processing_array(&params, q_arr);
                break;
            case 4:
                show_memory_reuse_state();
                break;
            default: 
                break;
        }
        
        clear_input_buffer();
    }

    free_list(q_list);
    free(q_list);
    free_arr(q_arr);
    free(q_arr);

    print_resulting_error_code(error);

    return error;
} 