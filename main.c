#include <stdio.h>
#include <stdlib.h>

#include "system.h"
#include "matrix.h"
#include "utils.h"

int main()
{
    while (!feof(stdin))
    {
        System *sys = read_system();

        // Separa o sistema em L e U
        double time_tri = triangularization(sys);
        
        float **y = new_matrix(sys->n);
        float **inverse = new_matrix(sys->n);

        // Inverte a matriz e registra o tempo tomado
        double time_y = 0.0f, time_x = 0.0f;
        invert(sys, inverse, &time_y, &time_x);
        
        // Imprime os resultados
        print_result(sys, inverse, time_tri, time_y, time_x, y, inverse);

        free_system(sys);
        free_matrix(y);
        free_matrix(inverse);

        sys = NULL;
        y = NULL;
        inverse = NULL;
    }

    return 0;
}
