#include "matrix.h"
#include "cell.h"

#include <stdio.h>
#include <stdlib.h>

#define SZ_LINES 20
#define SZ_COLUMNS 20

int main (){

    Matrix* m = construct_matrix (SZ_LINES, SZ_COLUMNS);

    for (int i=0;i<SZ_LINES;i++){
        for (int j=0;j<SZ_COLUMNS; j++)
            add_value_matrix(m, i, j, i+j);
    }
        
    print_dense_matrix (m);

    print_sparse_matrix (m);

    destroy_matrix (m);

    return 0;
}