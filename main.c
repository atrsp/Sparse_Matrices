#include "matrix.h"
#include "cell.h"

#include <stdio.h>
#include <stdlib.h>

#define SZ_LINES 4
#define SZ_COLUMNS 7

int main (){

    Matrix* m = construct_matrix (SZ_LINES, SZ_COLUMNS);

    add_value_matrix(m, 2, 3, 1);
    print_dense_matrix (m);

    printf ("\n\n");

    add_value_matrix(m, 2, 3, 4);
    print_dense_matrix (m);

    printf ("\n\n");

    add_value_matrix(m, 2, 4, 5);
    add_value_matrix(m, 2, 6, 8);
    add_value_matrix(m, 2, 5, 9);

    for (int i=0;i<SZ_LINES;i++){
        for (int j=0;j<SZ_COLUMNS; j++)
            add_value_matrix(m, i, j, i+j);
    }
        
    print_dense_matrix (m);

    //print_sparse_matrix (m);

    destroy_matrix (m);

    return 0;
}