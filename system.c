#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "system.h"
#include "matrix.h"
#include "utils.h"

System *new_system (unsigned int n)
{
    System *new = (System*) malloc(sizeof(System));
    must_alloc(new, __func__);

    new->L = set_identity(new_matrix(n), n);
    new->A = new_matrix(n);
    new->n = n;

    return new;
}


System *read_system ()
{
    unsigned int n;
    fscanf(stdin, "%u\n", &n);

    System *sys = new_system(n);
    sys->n = n;

    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            fscanf(stdin, "%f", &(sys->A[i][j]));

    sys->U = clone_matrix(sys->A, sys->n);

    return sys;
}


void free_system (System *sys)
{
    free_matrix(sys->L);
    free_matrix(sys->U);
    free(sys);
}

void pivoting(float **A, float *b, unsigned int n)
{
    float max, aux;
    unsigned int max_index;
    int i, k;

    for (int k = 0; k < n - 1; k++)
    {
        max_index = k;
        max = fabs(A[k][k]);
        for (i = k + 1; i < n; i++)
            if (fabs(A[i][k]) > max)
                max_index = i;

        if (max_index != k)
        { // Se terminou em um índice diferente de onde começou, troca
            for (int c = 0; c < n; c++)
            {
                aux = A[k][c];
                A[k][c] = A[max_index][c];
                A[max_index][c] = aux;
            }

            if (b)
            {
                aux = b[k];
                b[k] = b[max_index];
                b[max_index] = aux;
            }
        }
    }
}


double triangularization (System *sys)
{
    double time_tri = timestamp();
    int i, k, j;
    double m;
    
    for (k = 0; k < sys->n - 1; k++)
    {
        for (i = k + 1; i < sys->n; i++)
        {
            m = sys->U[i][k] / sys->U[k][k];

            sys->L[i][k] = m;
            sys->U[i][k] = 0.0f;

            for (j = k + 1; j < sys->n; j++)
                sys->U[i][j] -= (m * sys->U[k][j]);
        }
    }

    time_tri = timestamp() - time_tri;

    return time_tri;
}


int retrosubs (float **A, float *b, unsigned int n)
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


int gauss_jordan (float **A, float *x, float *b, unsigned int n)
{
    float **clone = clone_matrix(A, n);
    float *b_clone = malloc(sizeof(float) * n);
    must_alloc(b_clone, __func__);

    memcpy(b_clone, b, sizeof(float) * n);

    int i, k, j;
    double m;
    
    // Triangula usando o pivoteamento parcial
    for (k = 0; k < n - 1; k++)
    {
        pivoting(clone, b_clone, n);
        for (i = k + 1; i < n; i++)
        {
            m = clone[i][k] / clone[k][k];

            clone[i][k] = 0.0f;
            for (j = k + 1; j < n; j++)
                clone[i][j] -= (m * clone[k][j]);
                
            b_clone[i] -= m * b_clone[k];
        }
    }

    retrosubs(clone, b_clone, n);
    
    memcpy(x, b_clone, sizeof(float) * n);

    return 0;
}


void invert(System *sys, float **x, double *x_total_time, double *y_total_time)
{
    double time_y, time_x;

    float **B = set_identity(new_matrix(sys->n), sys->n);

    float *y = malloc(sizeof(float) * sys->n);
    must_alloc(y, __func__);

    for (int i = 0; i < sys->n; i++){
        time_y = timestamp();
        gauss_jordan(sys->L, y, B[i], sys->n);
        time_y = timestamp() - time_y;

        time_x = timestamp();
        gauss_jordan(sys->U, x[i], y, sys->n);
        time_x = timestamp() - time_x;

        *y_total_time += time_y;
        *x_total_time += time_x;
    }

    *y_total_time /= sys->n;
    *x_total_time /= sys->n;

    free_matrix(B);
    free(y);
}


// Calcula o resíduo de um sistema linear e sua solução
float *residue(System *sys, float *y, float *x)
{
    float *res = malloc(sys->n * sizeof(float));
    must_alloc(res, __func__);

    int i, k;
    double ax;

    for (i = 0; i < sys->n; i++){
        ax = 0.0f;
        for (k = 0; k < sys->n; k++)
            ax += sys->A[i][k] * x[k];
        res[i] = y[i] - ax;
    }
    
    return res;
}

float residue_norm(System *sys, float *res)
{
    float sum = 0.0f;
    for (int i = 0; i < sys->n; i++)
        sum += pow(res[i], 2.0f);
    return sqrt(sum);
}


void print_residues(System *sys, float **y, float **x)
{
    float norm;
    float *res = NULL;

    for (int i = 0; i < sys->n; i++)
    {
        res = residue(sys, y[i], x[i]);
        norm = residue_norm(sys, res);
        free(res);
        printf("%f ", norm);
    }

    printf("\n");
}


void print_result(System *sys, float **inverse, double time_tri, double time_y, double time_x, float **y, float **x)
{
    printf("%u\n", sys->n);
    print_matrix(sys->A, sys->n, 0);
    printf("#\n");
    print_matrix(inverse, sys->n, 1);
    printf("###########\n");
    printf("# Tempo Triangularização: %1.9f\n", time_tri);
    printf("# Tempo cálculo de Y: %1.9f\n", time_y);
    printf("# Tempo cálculo de X: %1.9f\n", time_x);
    printf("# Norma L2 do Residuo: ");
    print_residues(sys, y, x);
    printf("###########\n");
}
