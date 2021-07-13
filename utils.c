#include <stdlib.h>
#include <stdio.h>

void must_alloc(void *ptr, const char* desc)
{
    if (!ptr)
    {
        fprintf(stderr, "Malloc failure at %s.", desc);
        exit(1);
    }
}