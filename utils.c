#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "utils.h"

void must_alloc (void *ptr, const char* desc)
{
    if (!ptr)
    {
        fprintf(stderr, "Malloc failure at %s.", desc);
        exit(1);
    }
}


double timestamp (void)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}


int invalid(float num)
{
    if (num == NAN)         return 1;
    if (num == INFINITY)    return 1;
    if (num == -INFINITY)   return 1;
    return 0;
}


void check_exception (float n)
{
    if (invalid(n))
    {
        fprintf(stderr, "Floating point exception.\n");
        exit(1);
    }
}