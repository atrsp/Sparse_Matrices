#include "matrix.h"
#include "cell.h"

#include <stdio.h>
#include <stdlib.h>

#define SZ_LINES 4
#define SZ_COLUMNS 5

int main(int argc, char **argv)
{   

    Matrix *m = construct_matrix(SZ_LINES, SZ_COLUMNS);

    for (int i = 0; i < SZ_LINES; i++)
    {
        for (int j = 0; j < SZ_COLUMNS; j++)
            add_value_matrix(m, i, j, i + j);
    }

    Matrix *k = construct_matrix(3, 3);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            add_value_matrix(k, i, j, 6);
    }


    Matrix* conv = convolution_matrix (m, k);
    destroy_matrix (conv);
    destroy_matrix(k);
    destroy_matrix(m);

    /*EXPECTED OUTPUT:

        24.00  54.00  90.00  126.00  96.00

        54.00  108.00  162.00  216.00  162.00

        90.00  162.00  216.00  270.00  198.00

        72.00  126.00  162.00  198.00  144.00
    
    */

    return 0;
}

