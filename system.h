



struct linear_system {
    unsigned int n;
    float **U; // A
    float **L; // fodase
};


typedef struct linear_system System;

System *read_system();
void print_matrix(float **m, unsigned int n);
void free_system(System *sys);
void fatoracao(System *sys);
int eliminacaoGauss (float **A, float *x, float *b, unsigned int n);
float **set_identity(float **matrix, unsigned int n);
float **new_matrix(unsigned int n);