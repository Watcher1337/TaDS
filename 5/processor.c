#include "includes.h"
#include "processor.h"

// User initiated
void change_request_params(request_params *params)
{
    printf("Current parameters setup:\n");
    printf("1) Min arrival time for T1 request: %d\n", params->in_time_1_min);
    printf("2) Max arrival time for T1 request: %d\n", params->in_time_1_max);
    printf("3) Min arrival time for T2 request: %d\n", params->in_time_2_min);
    printf("4) Max arrival time for T2 request: %d\n", params->in_time_2_max);
    printf("5) Min time for T1 processing: %d\n", params->process_time_1_min);
    printf("6) Max time for T1 processing: %d\n", params->process_time_1_max);
    printf("7) Min time for T2 processing: %d\n", params->process_time_2_min);
    printf("8) Max time for T2 processing: %d\n", params->process_time_2_max);
    
    printf("Input number to change: ");

    int choice;

    if (scanf("%d", &choice) == 1)
    {
        int *change_parameter = NULL;
        switch (choice)
        {
            case 1:
                change_parameter = &params->in_time_1_min;
                break;
            case 2:
                change_parameter = &params->in_time_1_max;
                break;
            case 3:
                change_parameter = &params->in_time_2_min;
                break;
            case 4:
                change_parameter = &params->in_time_2_max;
                break;
            case 5:
                change_parameter = &params->process_time_1_min;
                break;
            case 6:
                change_parameter = &params->process_time_1_max;
                break;
            case 7:
                change_parameter = &params->process_time_2_min;
                break;
            case 8:
                change_parameter = &params->process_time_2_max;
                break;
            default:
                break;
        }

        if (change_parameter != NULL)
        {
            printf("Input new value: ");
            int value;
            if (scanf("%d", &value) == 1)
                *change_parameter = value;
        }
    }

    printf("\n");
}

// Startup only
void set_default_request_params(request_params * params)
{
    params->in_time_1_min = 1;
    params->in_time_1_max = 5;

    params->in_time_2_min = 0;
    params->in_time_2_max = 3;

    params->process_time_1_min = 0;
    params->process_time_1_max = 4;

    params->process_time_2_min = 0;
    params->process_time_2_max = 1;
}

void simulate_processing_array(request_params *params, queue_arr *queue)
{
    printf("Simulating array processing...\n");
    int T1, T2;
    int T1_current, T2_current;
    int is_processed_T1 = 0; // To determine if T1 or T2 queue currently being processed


    
    int k; // Pauses program
    scanf("%d", &k);
    printf("\n");
}

void simulate_processing_list(request_params *params, queue_list *queue)
{
    printf("Simulating list processing...\n");
    int T1, T2;
    int T1_current, T2_current;
    int is_processed_T1 = 0; // To determine if T1 or T2 queue currently being processed

    
    int k; // Pauses program
    scanf("%d", &k);
    printf("\n");
}