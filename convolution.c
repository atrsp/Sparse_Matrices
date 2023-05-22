#include "matrix.h"
#include "cell.h"

#include <stdio.h>
#include <stdlib.h>

#define SZ_LINES 4
#define SZ_COLUMNS 5

// always odd numbers for the kernel size
#define LINES_KERNEL 7
#define COLUMNS_KERNEL 5

int main(int argc, char **argv)
{

    Matrix *m = construct_matrix(SZ_LINES, SZ_COLUMNS);

    for (int i = 0; i < SZ_LINES; i++)
    {
        for (int j = 0; j < SZ_COLUMNS; j++)
            add_value_matrix(m, i, j, i + j);
    }

    Matrix *k = construct_matrix(LINES_KERNEL, COLUMNS_KERNEL);

    for (int i = 0; i < LINES_KERNEL; i++)
    {
        for (int j = 0; j < COLUMNS_KERNEL; j++)
            add_value_matrix(k, i, j, 6);
    }

    Matrix *conv1 = convolution_matrix(m, k);
    destroy_matrix(conv1);
    destroy_matrix(k);
    destroy_matrix(m);

    Matrix *new = construct_matrix(7, 7);
    Matrix *kernel = construct_matrix(3, 3);

    add_value_matrix(kernel, 0, 0, 1);
    add_value_matrix(kernel, 0, 2, 1);
    add_value_matrix(kernel, 1, 1, 1);
    add_value_matrix(kernel, 2, 0, 1);
    add_value_matrix(kernel, 2, 2, 1);

    // print_dense_matrix (kernel);

    add_value_matrix(new, 0, 1, 1);
    add_value_matrix(new, 0, 2, 1);
    add_value_matrix(new, 0, 3, 1);
    add_value_matrix(new, 1, 2, 1);
    add_value_matrix(new, 1, 3, 1);
    add_value_matrix(new, 1, 4, 1);
    add_value_matrix(new, 2, 3, 1);
    add_value_matrix(new, 2, 4, 1);
    add_value_matrix(new, 2, 5, 1);
    add_value_matrix(new, 3, 3, 1);
    add_value_matrix(new, 3, 4, 1);
    add_value_matrix(new, 4, 2, 1);
    add_value_matrix(new, 4, 3, 1);
    add_value_matrix(new, 5, 1, 1);
    add_value_matrix(new, 5, 2, 1);
    add_value_matrix(new, 6, 0, 1);
    add_value_matrix(new, 6, 1, 1);

    // print_dense_matrix (new);

    Matrix *conv = convolution_matrix(new, kernel);

    destroy_matrix(new);
    destroy_matrix(kernel);
    destroy_matrix(conv);

    /*EXPECTED OUTPUT:

180.00  288.00  420.00  384.00  324.00

180.00  288.00  420.00  384.00  324.00

180.00  288.00  420.00  384.00  324.00

180.00  288.00  420.00  384.00  324.00



0.00  2.00  2.00  3.00  1.00  1.00  0.00

1.00  1.00  4.00  3.00  4.00  1.00  1.00

0.00  1.00  2.00  4.00  3.00  3.00  0.00

0.00  1.00  2.00  3.00  4.00  1.00  1.00

1.00  1.00  3.00  3.00  1.00  1.00  0.00

1.00  3.00  3.00  1.00  1.00  0.00  0.00

2.00  2.00  1.00  1.00  0.00  0.00  0.00

    */

    return 0;
}
