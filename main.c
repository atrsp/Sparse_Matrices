#include "matrix.h"
#include "cell.h"

#include <stdio.h>
#include <stdlib.h>

#define SZ_LINES 4
#define SZ_COLUMNS 7

int main (){

    Matrix* m = construct_matrix (SZ_LINES, SZ_COLUMNS);

    for (int i=0;i<SZ_LINES;i++){
        for (int j=0;j<SZ_COLUMNS; j++)
            add_value_matrix(m, i, j, i+j);
    }
        
    /*
    for (int i=0;i<SZ_LINES;i++){
        for (int j=0;j<SZ_COLUMNS; j++)
            printf ("val: %.0f,   ", get_value_matrix(m, i, j));
        printf ("\n");
    }
    */

    //print_dense_matrix (m);
    //print_sparse_matrix (m);

    Matrix* mscalar = multiply_scalar_matrix (m, 2);

    destroy_matrix (m);
    destroy_matrix (mscalar);

    return 0;
}