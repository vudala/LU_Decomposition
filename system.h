#ifndef __SYSTEM__
#define __SYSTEM__

typedef struct {
    unsigned int n;
    float **A;
    float **U;
    float **L;
} System;

// Inicializa um novo sistema
System *new_system (unsigned int n);

// Lê um sistema
System *read_system ();

// Libera o espaço de memória ocupado por um sistema
void free_system (System *sys);

// Realiza a triangularização
double triangularization (System *sys);

// Resolve um sistema através do método de Gauss-Jordan
int gauss_jordan (float **A, float *x, float *b, unsigned int n);

// Imprime os resultados em stdout
void print_result(System *sys, float **inverse, double time_tri, double time_y, double time_x, float **y, float **x);

// Calcula a inversa do sistema linear
void invert(System *sys, float **x, double *x_total_time, double *y_total_time);

#endif