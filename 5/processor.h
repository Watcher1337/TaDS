#ifndef PROCESSOR_H
#define PROCESSOR_H

typedef struct request_params request_params;

#include "queue.h"
#include "includes.h"

struct request_params
{
    int in_time_1_min;
    int in_time_1_max;

    int in_time_2_min;
    int in_time_2_max;

    int process_time_1_min;
    int process_time_1_max;

    int process_time_2_min;
    int process_time_2_max;
};

void change_request_params(request_params *params);
void set_default_request_params(request_params *params);
void simulate_processing_array(request_params *params, queue_arr *queue);
void simulate_processing_list(request_params *params, queue_list *queue);


#endif