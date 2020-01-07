#include "includes.h"
#include "processor.h"

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
    //int T1, T2;
    //int T1_current, T2_current;
    //int is_processed_T1 = 0; // To determine if T1 or T2 queue currently being processed
    
    int k; // Pauses program
    scanf("%d", &k);
    printf("\n");
}

void simulate_processing_list(request_params *params)
{
    printf("Simulating list processing...\n");
    printf("| T1 requests | T1 queue length | T2 queue length | Average T1 length | Average T2 length |\n");
    float T1_arrival = 0, T2_arrival = 0;
    int T1_total = 0, T2_total = 0;
    int is_processed_T1 = 0; // To determine if T1 or T2 queue currently being processed
    int priority_switches_1 = 0;
    int priority_switches_2 = 0;
    int length_on_switch_1 = 0;
    int length_on_switch_2 = 0;
    float processed_time;
    float total_processed_time = 0;
    float arrival_time_1 = 0; // Total arrival time
    float arrival_time_2 = 0;

    queue_list *q_list_T1 = (queue_list *)malloc(sizeof(queue_list));
    queue_list *q_list_T2 = (queue_list *)malloc(sizeof(queue_list));

    alloc_list(q_list_T1);
    alloc_list(q_list_T2);

    // Choosing initial priority for queue
    while (T1_arrival == T2_arrival)
    {
        T1_arrival = gen_number(params->in_time_1_min, params->in_time_1_max);
        T2_arrival = gen_number(params->in_time_2_min, params->in_time_2_max);
    }

    // initiating first request to enter processor
    if (T2_arrival > T1_arrival)
    {
        printf("T1 request initiated...\n");
        push_list(q_list_T1, 'a');
        is_processed_T1 = 1;
    }
    else
    {
        printf("T2 request initiated...\n");
        push_list(q_list_T2, 'a');
        is_processed_T1 = 0;
    }

    while (T1_total < 1000)
    {
        while(is_processed_T1 == 0)
        {
            printf("processing T2 queue...\n");
            pop_list(q_list_T2);
            T2_total++;

            processed_time = gen_number(params->process_time_2_min, params->process_time_2_max);
            total_processed_time += processed_time;
            printf("T2 will be processed in %f\n", processed_time);

            T1_arrival = gen_number(params->in_time_1_min, params->in_time_1_max);
            arrival_time_1 += T1_arrival;
            printf("next T1 arrives in %f\n", T1_arrival);
            T2_arrival = gen_number(params->in_time_2_min, params->in_time_2_max);
            arrival_time_2 += T2_arrival;
            printf("next T2 arrives in %f\n", T2_arrival);

            if (T1_arrival < processed_time)
            {
                float tmp_time = 0;
                while (T1_arrival + tmp_time < processed_time) //in case several requests arrive during one processing
                {
                    float tmp = gen_number(params->in_time_1_min, params->in_time_1_max);
                    if (T1_arrival + tmp < processed_time)
                    {
                        printf("new T1 arrived before process ending\n");
                        push_list(q_list_T1, 'a');
                    }
                    
                    arrival_time_1 += tmp;
                    tmp_time += tmp;
                }
            }
            
            if (T2_arrival < processed_time)
            {
                float tmp_time = 0;
                while (T2_arrival + tmp_time < processed_time)
                {
                    float tmp = gen_number(params->in_time_2_min, params->in_time_2_max);
                    if (T2_arrival + tmp < processed_time)
                    {
                        printf("new T2 arrived before process ending\n");
                        push_list(q_list_T2, 'a');
                    }
                    
                    arrival_time_2 += tmp;
                    tmp_time += tmp;
                }
            }

            if (is_empty_list(q_list_T2) && (T2_arrival > processed_time && T2_arrival > T1_arrival))
                is_processed_T1 = 1;

            push_list(q_list_T1, 'a');
            push_list(q_list_T2, 'a');

            clear_input_buffer();
            printf("current T1 queue: %d\n", q_list_T1->curr_size);
            printf("current T2 queue: %d\n", q_list_T2->curr_size);
            int l; // Pauses program
            scanf("%d", &l);
            printf("\n");
        }

        priority_switches_1++;
        length_on_switch_1 += q_list_T1->curr_size;

        while (is_processed_T1 == 1)
        {
            printf("processing T1 queue...\n");
            pop_list(q_list_T1);
            T1_total++;

            // queue status report
            if (T1_total % 100 == 0 && T1_total)
                print_queue_list_status(q_list_T1, q_list_T2, T1_total,
                                        length_on_switch_1 / priority_switches_1, 
                                        length_on_switch_2 / priority_switches_2);

            // time to process current request
            processed_time = gen_number(params->process_time_1_min, params->process_time_1_max);
            total_processed_time += processed_time;
            printf("T1 will be processed in %f\n", processed_time);

            if (T1_total == 1000)
                break;

            T1_arrival = gen_number(params->in_time_1_min, params->in_time_1_max);
            arrival_time_1 += T1_arrival;
            printf("next T1 arrives in %f\n", T1_arrival);
            T2_arrival = gen_number(params->in_time_2_min, params->in_time_2_max);
            arrival_time_2 += T2_arrival;
            printf("next T2 arrives in %f\n", T2_arrival);


            if (T1_arrival < processed_time)
            {
                float tmp_time = 0;
                while (T1_arrival + tmp_time < processed_time) //in case several requests arrive during one processing
                {
                    float tmp = gen_number(params->in_time_1_min, params->in_time_1_max);
                    if (T1_arrival + tmp < processed_time)
                    {
                        printf("new T1 arrived before process ending\n");
                        push_list(q_list_T1, 'a');
                    }
                    arrival_time_1 += tmp;
                    tmp_time += tmp;
                }
            }
            
            if (T2_arrival < processed_time)
            {
                float tmp_time = 0;
                while (T2_arrival + tmp_time < processed_time)
                {
                    float tmp = gen_number(params->in_time_2_min, params->in_time_2_max);
                    if (T2_arrival + tmp < processed_time)
                    {
                        printf("new T2 arrived before process ending\n");
                        push_list(q_list_T2, 'a');
                    }
                    arrival_time_2 += tmp;
                    tmp_time += tmp;
                }
            }

            // last element of queue is being processed and next arrives after its done
            if (is_empty_list(q_list_T1) && (T1_arrival > processed_time && T1_arrival > T2_arrival))
                is_processed_T1 = 0;

            push_list(q_list_T1, 'a');
            push_list(q_list_T2, 'a');
            
            clear_input_buffer();
            printf("current T1 queue: %d\n", q_list_T1->curr_size);
            printf("current T2 queue: %d\n", q_list_T2->curr_size);
            int l; // Pauses program
            scanf("%d", &l);
            printf("\n");
        }

        // used to calculate avg. length
        priority_switches_2++;
        length_on_switch_2 += q_list_T2->curr_size;
    }

    printf("Total T1 requests in: %d\n", q_list_T1->in);
    printf("Total T2 requests in: %d\n", q_list_T2->in);

    printf("Total T1 requests out: %d\n", T1_total);
    printf("Total T2 requests out: %d\n", T2_total);

    printf("Idle processor time actual: %f\n\n", total_processed_time - (arrival_time_1 + arrival_time_2));
    
    printf("Processed requests theoretical time: %f\n", (params->process_time_1_min + params->process_time_1_max) / 2 +
                                                        (params->process_time_2_min + params->process_time_2_max) / 2);
    printf("Processed requests actual time: %f\n\n", total_processed_time / (T1_total + T2_total));
    /*
    printf("Average arrival theoretical: %f\n", (params->in_time_1_min + params->in_time_1_max) / 2 +
                                                (params->in_time_2_min + params->in_time_2_max) / 2);          
    printf("Average arrival actual: %f\n\n", (arrival_time_1 + arrival_time_2) / (T1_total + T2_total));*/
    
    free_list(q_list_T1);
    free(q_list_T1);
    free_list(q_list_T2);
    free(q_list_T2);

    int k; // Pauses program
    scanf("%d", &k);
    printf("\n");
}

// random [min, max]
float gen_number(float min, float max)
{
    return ((float)rand()/(float)(RAND_MAX)) * (max - min) + min;
}

void print_queue_list_status(queue_list *q_list, queue_list *q_list_2, int req_num, int avg_len_1, int avg_len_2)
{
    printf("|%13.d|%17.d|%17.d|%19.d|%19.d|\n", req_num, q_list->curr_size, q_list_2->curr_size, avg_len_1, avg_len_2);
}