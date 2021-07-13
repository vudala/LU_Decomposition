#include <stdio.h>
#include "system.h"
#include "utils.h"
#include <stdlib.h>


void print_vetor(float *v, int n)
{
    
}

int main()
{
    while (!feof(stdin))
    {
        System *sys = read_system();
        fatoracao(sys);
        
        float **B = set_identity(new_matrix(sys->n), sys->n);
        float *y = malloc(sizeof(float) * sys->n);
        must_alloc(y, "y");

        float **inversa = new_matrix(sys->n);

        for (int i = 0; i < sys->n; i++)
        {    
            eliminacaoGauss(sys->L, y, B[i], sys->n);
            eliminacaoGauss(sys->U, inversa[i], y, sys->n);
        }

        print_matrix(inversa, sys->n);

        free_system(sys);
        sys = NULL;
    }

    return 0;
}