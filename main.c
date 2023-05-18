#include "matrix.h"
#include "cell.h"

#include <stdio.h>
#include <stdlib.h>

#define SZ_LINES 3
#define SZ_COLUMNS 3

int main (int argc, char** argv){

    Matrix* m = construct_matrix (SZ_LINES, SZ_COLUMNS);

    //print_dense_matrix (m);
    for (int i=0;i<SZ_LINES;i++){
        for (int j=0;j<SZ_COLUMNS; j++)
            add_value_matrix(m, i, j, i+j);
    }

    Matrix* m1 = construct_matrix (SZ_LINES, SZ_COLUMNS);

    /*for (int i=0;i<SZ_LINES;i++){
        for (int j=0;j<SZ_COLUMNS; j++)
            add_value_matrix(m1, i, j, -i-j);
         
    }*/

    /* 
    //TESTE GET VALUE
    for (int i=0;i<SZ_LINES;i++){
        for (int j=0;j<SZ_COLUMNS; j++)
            printf ("val: %.0f,   ", get_value_matrix(m, i, j));
        printf ("\n");
    }
    */

    //TESTE PRINTS
    //print_dense_matrix (m);
    //print_sparse_matrix (m);

    /*
    //TESTE DE MULTIPLICAÇÃO POR ESCALAR
    Matrix* mscalar = multiply_scalar_matrix (m, 26);
    destroy_matrix (mscalar);
    */

    /*
    //TESTE TRANSPOSTA
    Matrix* transp = transpose_matrix (m);
    destroy_matrix (transp);
    */
    

    /*
    //TESTE DE SOMA
    Matrix* sum = sum_matrix (m1, m1);
    destroy_matrix (sum);
    */

    /*
    //TESTE BINÁRIO
    bin_print_sparse_matrix ("bin", m);
    Matrix* read = bin_read_sparse_matrix(argv[1]);
    destroy_matrix (read);
    */

    //Matrix* slice = slice_matrix (m, 1, 1, 3, 6);

    //Matrix* mult_cells = multiply_per_cells_matrix (m, m1);

    /*
    //TESTE MULTIPLICAÇÃO DE MATRIZES
    Matrix* mult = multiplication_of_matrix (m, m);
    //funciona para matrizes quadradas, mas não de tamanhos diferentes (c(m1) == l(m2)
    destroy_matrix (mult);
    */

   /*
   //TESTE MULTIPLICAÇÃO POR CELL
   Matrix* mult = multiply_per_cells_matrix (m, m1);
   destroy_matrix (mult);
   */
   

    destroy_matrix (m);
    destroy_matrix (m1);
    
    
    return 0;
}
