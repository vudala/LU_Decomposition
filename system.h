#ifndef __SYSTEM__
#define __SYSTEM__

typedef struct {
    unsigned int n;
    float **A;
    float **L;
    float **U;
    float **B;
} System;

// Inicializa um novo sistema
System *new_system (unsigned int n);

// Lê um sistema
System *read_system ();

// Libera o espaço de memória ocupado por um sistema
void free_system (System *sys);

// Realiza a triangularização
double triangularization (System *sys, unsigned int piv);

// Calcula a matriz inversa do sistema
void invert (System *sys, float **x, double *x_total_time, double *y_total_time);

// Imprime os resultados em output_file
void print_result (FILE *output_file, System *sys, float **inverse, double time_tri, double time_y, double time_x);

#endif