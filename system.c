#include "utils.h"
#include "system.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

float **new_matrix(unsigned int n)
{
    float **new = (float**) malloc(sizeof(float*) * n);
    must_alloc(new, "new matrix");

    new[0] = (float*) calloc(n * n, sizeof(float));
    must_alloc(new[0], "new matrix");

    for (int i = 0; i < n; i++)
        new[i] = new[0] + i * n;

    return new;
}


float **set_identity(float **matrix, unsigned int n)
{
    for (int i = 0; i < n; i++)
        matrix[i][i] = 1;
    return matrix;
}


System *new_system(unsigned int n)
{
    System *new = (System*) malloc(sizeof(System));
    must_alloc(new, "new_system");

    new->L = set_identity(new_matrix(n), n);
    new->U = new_matrix(n);
    new->n = n;

    return new;
}


System *read_system()
{
    unsigned int n;
    fscanf(stdin, "%u\n", &n);

    System *sys = new_system(n);
    sys->n = n;

    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            fscanf(stdin, "%f", &(sys->U[i][j]));

    return sys;
}


void print_matrix(float **m, unsigned int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%f ", m[i][j]);
        printf("\n");
    }
}


void free_matrix(float **mat)
{
    free(mat[0]);
    free(mat);
}


void free_system(System *sys)
{
    free_matrix(sys->L);
    free_matrix(sys->U);
    free(sys);
}


void fatoracao (System *sys)
{
    int i, k, j;
    double m;
    
    for (k = 0; k < sys->n - 1; k++)
    {
        /// PIVOTEAMENTO PORRAAAAAA

        for (i = k + 1; i < sys->n; i++)
        {
            m = sys->U[i][k] / sys->U[k][k];

            sys->L[i][k] = m;
            sys->U[i][k] = 0.0f;

            for (j = k + 1; j < sys->n; j++)
                sys->U[i][j] -= (m * sys->U[k][j]);
        }
    }
}

int retrosubs(float **A, float *b, unsigned int n)
{
    for (int i = n - 1; i >= 0; i--)
    {
        b[i] /= A[i][i];
        A[i][i] = 1.0f;
        for (int j = i - 1; j >= 0; j--)
        {
            b[j] -= A[j][i] * b[i];
            A[j][i] = 0.0f;
        }
    }
    return 0;
}

float **clone_matrix(float **m, unsigned int n)
{   
    float **clone = (float**) malloc(sizeof(float*) * n);
    must_alloc(clone, __func__);
    
    clone[0] = malloc(sizeof(float) * n * n);
    must_alloc(clone[0], __func__);

    for (int i = 0; i < n; i++)
        clone[i] = clone[0] + i * n;

    memcpy(clone[0], m[0], sizeof(float) * n * n);

    return clone;
}

int eliminacaoGauss (float **A, float *x, float *b, unsigned int n)
{

    int i, k, j, result;

    float **clone = clone_matrix(A, n);
    double m;
    
    // Triangula usando o pivoteamento parcial
    for (k = 0; k < n - 1; k++){
        unsigned int max_index = k;
        float max = fabs(clone[k][k]);
        for (i = k + 1; i < n; i++)
            if (fabs(clone[i][k]) > max)
                max_index = i;

        if (max_index != k){ // Se terminou em um índice diferente de onde começou, troca
            float aux;
            for (int c = 0; c < n; c++)
            {
                aux = clone[k][c];
                clone[k][c] = clone[max_index][c];
                clone[max_index][c] = aux;
            }

            aux = b[k];
            b[k] = b[max_index];
            b[max_index] = aux;
        }

        for (i = k + 1; i < n; i++)
        {
            m = clone[i][k] / clone[k][k];

            clone[i][k] = 0.0f;
            for (j = k + 1; j < n; j++)
                clone[i][j] -= (m * clone[k][j]);
                
            b[i] -= m * b[k];
        }
    }

    result = retrosubs(clone, b, n);
    
    memcpy(x, b, sizeof(float) * n);

    return 0;
}