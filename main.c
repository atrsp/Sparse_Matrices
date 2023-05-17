#include "matrix.h"
#include "cell.h"

#include <stdio.h>
#include <stdlib.h>

#define SZ_LINES 3
#define SZ_COLUMNS 2

int main (int argc, char** argv){

    Matrix* m = construct_matrix (SZ_LINES, SZ_COLUMNS);

    for (int i=0;i<SZ_LINES;i++){
        for (int j=0;j<SZ_COLUMNS; j++)
            add_value_matrix(m, i, j, i+j);
    }

    Matrix* m1 = construct_matrix (SZ_LINES, SZ_COLUMNS);

    for (int i=0;i<SZ_LINES;i++){
        for (int j=0;j<SZ_COLUMNS; j++)
            add_value_matrix(m1, i, j, -i-j);
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

    //Matrix* mscalar = multiply_scalar_matrix (m, 2);
    //print_dense_matrix(mscalar);

    Matrix* transp = transpose_matrix (m);

    //Matrix* sum = sum_matrix (m, m1);
    //bin_print_sparse_matrix ("bin", m);
    //bin_read_sparse_matrix(argv[1]);

    //Matrix* slice = slice_matrix (m, 1, 1, 3, 6);

    //Matrix* result = multiply_per_cells_matrix (m, m1);

    Matrix* mult = multiplication_of_matrix (m, transp);

    destroy_matrix (m);
    destroy_matrix (m1);
    //destroy_matrix (sum);
    destroy_matrix (transp);
    //destroy_matrix (mscalar);

    return 0;
}