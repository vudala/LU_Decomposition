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

// Retorna o tempo de execução e calcula a matriz Y
double get_y(System *sys, float **y);

// Retorna o tempo de execução e calcula a matriz X
double get_x(System *sys, float **y, float **x);

// Resolve um sistema através do método de Gauss-Jordan
int gauss_jordan (float **A, float *x, float *b, unsigned int n);

// Imprime os resultados em stdout
void print_result(System *sys, float **inverse, double time_tri, double time_y, double time_x, float **y, float **x);

void pivoting(float **A, float *b, unsigned int n);



#endif