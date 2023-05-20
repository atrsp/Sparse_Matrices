#include "matrix.h"
#include "cell.h"

#include <stdio.h>
#include <stdlib.h>

#define SZ_LINES 4
#define SZ_COLUMNS 5

int main (int argc, char** argv){

    Matrix* m = construct_matrix (SZ_LINES, SZ_COLUMNS);
    Matrix* m2 = construct_matrix (-1, 0);

    //print_dense_matrix (m);
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
    //GET VALUE TEST
    for (int i=0;i<SZ_LINES;i++){
        for (int j=0;j<SZ_COLUMNS; j++)
            printf ("val: %.0f,   ", get_value_matrix(m, i, j));
        printf ("\n");
    }
    */

    //MATRIX PRINTING TEST
    //print_dense_matrix (m);
    //print_sparse_matrix (m);

    /*
    //MULTIPLICATION PER SCALAR TEST
    Matrix* mscalar = multiply_scalar_matrix (m, 26);
    destroy_matrix (mscalar);
    */

    /*
    //TRANSPOSED MATRIX TESTE
    Matrix* transp = transpose_matrix (m);
    destroy_matrix (transp);
    */
    

    /*
    //SUM TEST
    Matrix* sum = sum_matrix (m1, m1);
    destroy_matrix (sum);
    */

    /*
    //BINARY FILES TEST
    bin_print_sparse_matrix ("bin", m);
    Matrix* read = bin_read_sparse_matrix(argv[1]);
    destroy_matrix (read);
    */

    /*
    //SLICE MATRIX TEST
    Matrix* slice = slice_matrix (m, 1, 1, 2, 2);
    destroy_matrix (slice);
    */

    /*
    //MULTIPLICATION OF MATRICES TEST
    Matrix* transp = transpose_matrix(m);
    Matrix* mult = multiplication_of_matrix (m, transp);
    Matrix* mult2 = multiplication_of_matrix (transp, m);
    destroy_matrix(mult2);
    destroy_matrix (mult);
    destroy_matrix (transp);
    */

   /*
   //MULTIPLICATION PER CELLS TEST
   Matrix* mult = multiply_per_cells_matrix (m, m1);
   destroy_matrix (mult);
   */

    destroy_matrix (m);
    destroy_matrix (m1);
    
    return 0;
}
