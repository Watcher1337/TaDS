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
                simulate_processing_list(&params);
                break;
            case 3:
                simulate_processing_array(&params);
                break;
            case 4:
                show_memory_reuse_state();
                break;
            default: 
                break;
        }
        
        clear_input_buffer();
    }

    print_resulting_error_code(error);

    return error;
} 