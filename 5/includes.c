#include "includes.h"

void clear_input_buffer(void)
{
    while (getchar() != '\n');
}