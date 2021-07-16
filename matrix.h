#ifndef __MATRIX__
#define __MATRIX__

// Inicializa uma matrix
float **new_matrix (unsigned int n);

// Transforma uma matriz em uma matriz identidade
float **set_identity (float **matrix, unsigned int n);

// Imprime a matriz em stdout
void print_matrix (float **m, unsigned int n, unsigned int inverse);

// Libera o espaço de memória ocupado por uma matriz
void free_matrix (float **mat);

// Cria uma cópia de uma matriz
float **clone_matrix (float **m, unsigned int n);

#endif