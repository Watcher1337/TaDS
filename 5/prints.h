#ifndef PRINTS_H
#define PRINTS_H

#include "includes.h"
#include "queue.h"
#include "measures.h"
#include "processor.h"

void print_list(queue_list *q_list);
void print_arr(queue_arr *queue_arr);
void print_resulting_error_code(int error);
void show_memory_reuse_state();
int choose_menu(int *error);

#endif