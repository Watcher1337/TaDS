#ifndef FRAGMENTATION_TEST
#define FRAGMENTATION_TEST

#include "includes.h"
#include "queue.h"

typedef struct fragments fragments;

struct fragments
{
    node** freed_memory;
    node** reused_memory;
};

void init_fragments(fragments *frags);

#endif