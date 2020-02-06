#include "includes.h"
#include "processor.h"

#define PRIORITY_T1 1
#define PRIORITY_T2 2

// User initiated
void change_request_params(request_params *params)
{ 
    printf("Current parameters setup:\n");
    printf("1) Min arrival time for T1 request: %f\n", params->in_time_1_min);
    printf("2) Max arrival time for T1 request: %f\n", params->in_time_1_max);
    printf("3) Min arrival time for T2 request: %f\n", params->in_time_2_min);
    printf("4) Max arrival time for T2 request: %f\n", params->in_time_2_max);
    printf("5) Min time for T1 processing: %f\n", params->process_time_1_min);
    printf("6) Max time for T1 processing: %f\n", params->process_time_1_max);
    printf("7) Min time for T2 processing: %f\n", params->process_time_2_min);
    printf("8) Max time for T2 processing: %f\n", params->process_time_2_max);
    
    printf("Input number to change: ");

    int choice;

    if (scanf("%d", &choice) == 1)
    {
        int is_min; // used to determine tmp stored value
        float tmp; // stores min/max value to prevent min_time > max_time
        float *change_parameter = NULL; // stores value to change
        switch (choice)
        {
            case 1:
                change_parameter = &params->in_time_1_min;
                is_min = 1;
                tmp = params->in_time_1_max;
                break;
            case 2:
                change_parameter = &params->in_time_1_max;
                is_min = 0;
                tmp = params->in_time_1_min;
                break;
            case 3:
                change_parameter = &params->in_time_2_min;
                is_min = 1;
                tmp = params->in_time_2_max;
                break;
            case 4:
                change_parameter = &params->in_time_2_max;
                is_min = 0;
                tmp = params->in_time_2_min;
                break;
            case 5:
                change_parameter = &params->process_time_1_min;
                is_min = 1;
                tmp = params->process_time_1_max;
                break;
            case 6:
                change_parameter = &params->process_time_1_max;
                is_min = 0;
                tmp = params->process_time_1_min;
                break;
            case 7:
                change_parameter = &params->process_time_2_min;
                is_min = 1;
                tmp = params->process_time_2_max;
                break;
            case 8:
                change_parameter = &params->process_time_2_max;
                is_min = 0;
                tmp = params->process_time_2_min;
                break;
            default:
                break;
        }

        if (change_parameter != NULL)
        {
            printf("Input new value: ");
            float value;
            if (scanf("%f", &value) == 1)
            {
                if ((is_min == 1 && value <= tmp) || (is_min == 0 && value >= tmp))
                    *change_parameter = value;
                else
                    printf("Wrong input");
            }
        }
    }

    printf("\n");
}

// Startup only
void set_default_request_params(request_params * params)
{
    params->in_time_1_min = 1.f;
    params->in_time_1_max = 5.f;

    params->in_time_2_min = 0.f;
    params->in_time_2_max = 3.f;

    params->process_time_1_min = 0.f;
    params->process_time_1_max = 4.f;

    params->process_time_2_min = 0.f;
    params->process_time_2_max = 1.f;
}

void simulate_processing_array(request_params *params)
{
    printf("Simulating array processing...\n");

    int k; // Pauses program
    scanf("%d", &k);
    printf("\n");
}

void simulate_processing_list(request_params *params)
{
    printf("Simulating list processing...\n");
    printf("| T1 requests | T1 queue length | T2 queue length | Average T1 length | Average T2 length |\n");

    queue_list *q_list_T1;
    queue_list *q_list_T2;

    q_list_T1 = alloc_list();
    q_list_T2 = alloc_list();

    // ------------------------------------- MAIN PART OF ALGORITHM

    float time_T1 = 0;
    float time_T2 = 0;

    float time_processing;
    float time_total_processing = 0;
    float time_idle = 0;

    int priority;
    int warning_counter = 0;

    time_T1 += gen_number(params->in_time_1_min, params->in_time_1_max);
    time_T2 += gen_number(params->in_time_2_min, params->in_time_2_max);

    float tmp_time_T1 = time_T1;
    float tmp_time_T2 = time_T2;

    // initializing
    if (time_T1 < time_T2)
    {
        // time until processor starts the first time
        time_idle = fabs(0.f - time_T1);
        // starting procesing time
        time_total_processing = time_T1;
        priority = PRIORITY_T1;
    }
    else
    {
        time_idle = fabs(0.f - time_T2);
        time_total_processing = time_T2;
        priority = PRIORITY_T2;
    }

    printf("Initial T1 size: %d\nInitial T2 size: %d\n", q_list_T1->curr_size, q_list_T2->curr_size);

    printf("T1 arrives at %f\n", time_T1);
    printf("T2 arrives at %f\n", time_T2);

    push_list(q_list_T1, 'a');
    push_list(q_list_T2, 'a');
    
    printf("Current T1 size: %d\nCurrent T2 size: %d\n", q_list_T1->curr_size, q_list_T2->curr_size);

    printf("initialized..\n");

    while (q_list_T1->out < 1000)
    {
        // Testing only
        warning_counter++;
        if (warning_counter > 1000)
            break;

        printf("\n\n");

        //pause();
        if (priority == PRIORITY_T1)
        {
            pop_list(q_list_T1);
            printf("T1 left queue at %f\n\n", time_T1);
         
            time_processing = gen_number(params->process_time_1_min, params->process_time_1_max);
            time_total_processing = time_processing + tmp_time_T1;

            printf("T1 left processor at %f\n", time_T1 + time_processing);
            printf("Current total processing time: %f\n\n", time_total_processing);
            printf("Current T1 size: %d\nCurrent T2 size: %d\n", q_list_T1->curr_size, q_list_T2->curr_size);
        }

        if (priority == PRIORITY_T2)
        {
            pop_list(q_list_T2);
            printf("T2 left queue at %f\n\n", time_T2);
         
            time_processing = gen_number(params->process_time_2_min, params->process_time_2_max);
            time_total_processing = time_processing + tmp_time_T2;
         
            printf("T2 left processor at %f\n", time_T2 + time_processing);
            printf("Current total processing time: %f\n\n", time_total_processing);
            printf("Current T1 size: %d\nCurrent T2 size: %d\n", q_list_T1->curr_size, q_list_T2->curr_size);
        }

        // Priority switch
        if (priority == PRIORITY_T1 && is_empty_list(q_list_T1) && time_total_processing < time_T1)
            if (time_T2 < time_T1)
            {
                priority = PRIORITY_T2;
                printf("switching priority to T2\n");
            }

        if (priority == PRIORITY_T2 && is_empty_list(q_list_T2) && time_total_processing < time_T2)
            if (time_T1 < time_T2)
            {
                priority = PRIORITY_T1;
                printf("switching priority to T1\n");
            }

        // counting idle time
        if (time_total_processing < time_T2 && time_total_processing < time_T1 && 
                            is_empty_list(q_list_T1) && is_empty_list(q_list_T2))
        {
            if (time_T1 > time_T2)
            {
                time_idle += time_T2 - time_total_processing;
                printf("processor stays idle for %f\n", time_T2 - time_total_processing);
            }
            else
            {
                time_idle += time_T1 - time_total_processing;
                printf("processor stays idle for %f\n", time_T1 - time_total_processing);
            }
        }

        while (time_T1 < time_total_processing)
        {
            tmp_time_T1 = gen_number(params->in_time_1_min, params->in_time_1_max);
            time_T1 += tmp_time_T1;
            push_list(q_list_T1, 'a');
            printf("T1 request arrives at %f\n", time_T1);
            printf("Current T1 size: %d\nCurrent T2 size: %d\n", q_list_T1->curr_size, q_list_T2->curr_size);
        }

        while (time_T2 < time_total_processing)
        {
            tmp_time_T2 = gen_number(params->in_time_2_min, params->in_time_2_max);
            time_T2 += tmp_time_T2;
            push_list(q_list_T2, 'a');
            printf("T2 request arrives at %f\n", time_T2);
            printf("Current T1 size: %d\nCurrent T2 size: %d\n", q_list_T1->curr_size, q_list_T2->curr_size);
        }

        // Statistics
        printf("\n---------------------------------------------\n");
        //printf("Current T1 size: %d\nCurrent T2 size: %d\n", q_list_T1->curr_size, q_list_T2->curr_size);
        //printf("Next T1 request: %f\n Next T2 request: %f\n", time_T1, time_T2);
        printf("Current processing time: %f\n", time_total_processing);
        printf("Total idle time is %f\n", time_idle);
        printf("-----------------------------------------------\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        pause();

        // Testing only
        if (q_list_T1->curr_size > 100 || q_list_T2->curr_size > 100)
            break;
    }

    // ------------------------------------- END OF ALGORITHM PART

    free_list(q_list_T1);
    free(q_list_T1);
    free_list(q_list_T2);
    free(q_list_T2);

    pause();
}

// random [min, max]
float gen_number(float min, float max)
{
    return ((float)rand()/(float)(RAND_MAX)) * (max - min) + min;
}

// Called every 100 processed T1 requests
void print_queue_list_status(queue_list *q_list, queue_list *q_list_2, int req_num, int avg_len_1, int avg_len_2)
{
    printf("|%13.d|%17.d|%17.d|%19.d|%19.d|\n", req_num, q_list->curr_size, q_list_2->curr_size, avg_len_1, avg_len_2);
}

void pause()
{
    int k; // Pauses program
    printf("Enter any number to continue... ");
    scanf("%d", &k);
    printf("\n");
    clear();
}

void clear()
{    
    while (getchar() != '\n');
}