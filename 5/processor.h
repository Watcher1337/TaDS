#ifndef PROCESSOR_H
#define PROCESSOR_H

typedef struct request_params request_params;

#include "queue.h"
#include "includes.h"

struct request_params
{
    float in_time_1_min;
    float in_time_1_max;

    float in_time_2_min;
    float in_time_2_max;

    float process_time_1_min;
    float process_time_1_max;

    float process_time_2_min;
    float process_time_2_max;

    int process_amount_T1;
};

void change_request_params(request_params *params);
void set_default_request_params(request_params *params);
void simulate_processing_array(request_params *params);
void simulate_processing_list(request_params *params);
void print_queue_list_status(queue_list *q_list, queue_list *q_list_2, int req_num, int avg_len_1, int avg_len_2);
void print_queue_arr_status(queue_arr *q_arr, queue_arr *q_arr_2, int req_num, int avg_len_1, int avg_len_2);
void print_theoretical_data(request_params *params, int requests_T1, int requests_T2, float proc_time);
float gen_number(float min, float max);
void pause();
void clear();

#endif