#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <sys/time.h>

// Certifica que um ponteiro foi alocado
void must_alloc (void *ptr, const char* desc);

// Retorna o horário atual em ms
double timestamp (void);

#endif