#include <stdio.h>
#include <stdlib.h>

#include "system.h"
#include "matrix.h"
#include "utils.h"

int main()
{
    while (!feof(stdin))
    {
        double time_tri, time_y, time_x;
        System *sys = read_system();

        // Separa o sistema em L e U
        time_tri = triangularization(sys);
        
        float **y = new_matrix(sys->n);
        float **inverse = new_matrix(sys->n);

        // Calcula Y
        time_y = get_y(sys, y);

        // Calcula X, que é a inversa
        time_x = get_x(sys, y, inverse);
        
        // Imprime os resultados
        //print_result(sys, inverse, time_tri, time_y, time_x, y, inverse);

        print_matrix(inverse, sys->n, 0);

        free_system(sys);
        free_matrix(y);
        free_matrix(inverse);

        sys = NULL;
        y = NULL;
        inverse = NULL;
    }

    return 0;
}
