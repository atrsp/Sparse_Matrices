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

    Matrix *m1 = construct_matrix(SZ_LINES, SZ_COLUMNS);

    for (int i = 0; i < SZ_LINES; i++)
    {
        for (int j = 0; j < SZ_COLUMNS; j++)
            add_value_matrix(m1, i, j, -i - j);
    }

    // MATRIX PRINTING TEST
    printf("PRINT:\n\n");
    print_dense_matrix(m);
    print_sparse_matrix(m);
    printf("--------------------------------------\n\n");

    printf("PRINT:\n\n");
    print_dense_matrix(m1);
    print_sparse_matrix(m1);
    printf("--------------------------------------\n\n");

    // SWAP TEST
    Matrix *swap_columns = swap_columns_matrix(m, 1, 2);
    Matrix *swap_lines = swap_lines_matrix(m, 1, 2);
    destroy_matrix(swap_columns);
    destroy_matrix(swap_lines);

    // MULTIPLICATION PER SCALAR TEST
    Matrix *mscalar = multiply_scalar_matrix(m, 2);
    destroy_matrix(mscalar);

    // TRANSPOSED MATRIX TESTE
    Matrix *transp = transpose_matrix(m);

    // SUM TEST
    Matrix *sum = sum_matrix(m1, m);
    destroy_matrix(sum);

    // BINARY FILES TEST
    bin_print_sparse_matrix("bin", m);
    Matrix *read = bin_read_sparse_matrix(argv[1]);
    destroy_matrix(read);

    // SLICE MATRIX TEST
    printf("SLICE MATRIX:\n\n");

    Matrix *slice = slice_matrix(m, 1, 1, 2, 2);

    printf("\033[92mPrevious matrix:\033[0m\n");
    print_dense_matrix(m);

    printf("\033[95mResult:\n\033[0m");
    print_dense_matrix(slice);

    printf("--------------------------------------\n\n");

    destroy_matrix(slice);

    // GET VALUE TEST
    printf("GET VALUE:\n\n");
    for (int i = 0; i < SZ_LINES; i++)
    {
        for (int j = 0; j < SZ_COLUMNS; j++)
            printf("val: %.0f   ", get_value_matrix(m, i, j));
        printf("\n");
    }
    printf("\n--------------------------------------\n\n");

    // MULTIPLICATION OF MATRICES TEST
    Matrix *mult = multiplication_of_matrix(m, transp);
    Matrix *mult2 = multiplication_of_matrix(transp, m);
    destroy_matrix(mult2);
    destroy_matrix(mult);
    destroy_matrix(transp);

    // MULTIPLICATION PER CELLS TEST

    printf("MULTIPLICATION PER CELLS:\n\n");
    Matrix *mult_cells = multiply_per_cells_matrix(m, m1);

    printf("\033[92mPrevious matrix (1):\033[0m\n");
    print_dense_matrix(m);

    printf("\033[92mPrevious matrix (2):\033[0m\n");
    print_dense_matrix(m1);

    printf("\033[95mResult:\n\033[0m");
    print_dense_matrix(mult_cells);

    printf("--------------------------------------\n\n");

    destroy_matrix(mult_cells);
    destroy_matrix(m);
    destroy_matrix(m1);

    Matrix *m2 = construct_matrix(SZ_LINES, SZ_COLUMNS);

    for (int i = 0; i < SZ_LINES; i++)
    {
        for (int j = 0; j < SZ_COLUMNS; j++)
            add_value_matrix(m2, i, j, 6);
    }

    add_value_matrix(m2, 0, -1, 0);
    float a = get_value_matrix(m2, 0, -1);

    /*EXPECTED OUPUT:

    PRINT:

0.00  1.00  2.00  3.00  4.00

1.00  2.00  3.00  4.00  5.00

2.00  3.00  4.00  5.00  6.00

3.00  4.00  5.00  6.00  7.00



[0][1] -> 1.00
[0][2] -> 2.00
[0][3] -> 3.00
[0][4] -> 4.00
[1][0] -> 1.00
[1][1] -> 2.00
[1][2] -> 3.00
[1][3] -> 4.00
[1][4] -> 5.00
[2][0] -> 2.00
[2][1] -> 3.00
[2][2] -> 4.00
[2][3] -> 5.00
[2][4] -> 6.00
[3][0] -> 3.00
[3][1] -> 4.00
[3][2] -> 5.00
[3][3] -> 6.00
[3][4] -> 7.00


--------------------------------------

PRINT:

0.00  -1.00  -2.00  -3.00  -4.00

-1.00  -2.00  -3.00  -4.00  -5.00

-2.00  -3.00  -4.00  -5.00  -6.00

-3.00  -4.00  -5.00  -6.00  -7.00



[0][1] -> -1.00
[0][2] -> -2.00
[0][3] -> -3.00
[0][4] -> -4.00
[1][0] -> -1.00
[1][1] -> -2.00
[1][2] -> -3.00
[1][3] -> -4.00
[1][4] -> -5.00
[2][0] -> -2.00
[2][1] -> -3.00
[2][2] -> -4.00
[2][3] -> -5.00
[2][4] -> -6.00
[3][0] -> -3.00
[3][1] -> -4.00
[3][2] -> -5.00
[3][3] -> -6.00
[3][4] -> -7.00


--------------------------------------

SWAP COLUMNS:

Previous matrix:
0.00  1.00  2.00  3.00  4.00

1.00  2.00  3.00  4.00  5.00

2.00  3.00  4.00  5.00  6.00

3.00  4.00  5.00  6.00  7.00



Result:
0.00  2.00  1.00  3.00  4.00

1.00  3.00  2.00  4.00  5.00

2.00  4.00  3.00  5.00  6.00

3.00  5.00  4.00  6.00  7.00



--------------------------------------

SWAP LINES:

Previous matrix:
0.00  1.00  2.00  3.00  4.00

1.00  2.00  3.00  4.00  5.00

2.00  3.00  4.00  5.00  6.00

3.00  4.00  5.00  6.00  7.00



Result:
0.00  1.00  2.00  3.00  4.00

2.00  3.00  4.00  5.00  6.00

1.00  2.00  3.00  4.00  5.00

3.00  4.00  5.00  6.00  7.00



--------------------------------------

MULTIPLICATION PER SCALAR 2.00:

Previous matrix:
0.00  1.00  2.00  3.00  4.00

1.00  2.00  3.00  4.00  5.00

2.00  3.00  4.00  5.00  6.00

3.00  4.00  5.00  6.00  7.00



Result:
0.00  2.00  4.00  6.00  8.00

2.00  4.00  6.00  8.00  10.00

4.00  6.00  8.00  10.00  12.00

6.00  8.00  10.00  12.00  14.00



--------------------------------------

TRANSPOSE MATRIX:

Previous matrix:
0.00  1.00  2.00  3.00  4.00

1.00  2.00  3.00  4.00  5.00

2.00  3.00  4.00  5.00  6.00

3.00  4.00  5.00  6.00  7.00



Result:
0.00  1.00  2.00  3.00

1.00  2.00  3.00  4.00

2.00  3.00  4.00  5.00

3.00  4.00  5.00  6.00

4.00  5.00  6.00  7.00



--------------------------------------

SUM OF MATRICES:

Previous matrix (1):
0.00  -1.00  -2.00  -3.00  -4.00

-1.00  -2.00  -3.00  -4.00  -5.00

-2.00  -3.00  -4.00  -5.00  -6.00

-3.00  -4.00  -5.00  -6.00  -7.00



Previous matrix (2):
0.00  1.00  2.00  3.00  4.00

1.00  2.00  3.00  4.00  5.00

2.00  3.00  4.00  5.00  6.00

3.00  4.00  5.00  6.00  7.00



Result:
0.00  0.00  0.00  0.00  0.00

0.00  0.00  0.00  0.00  0.00

0.00  0.00  0.00  0.00  0.00

0.00  0.00  0.00  0.00  0.00



--------------------------------------

PRINT BINARY FILE:

Matrix printed:
0.00  1.00  2.00  3.00  4.00

1.00  2.00  3.00  4.00  5.00

2.00  3.00  4.00  5.00  6.00

3.00  4.00  5.00  6.00  7.00



--------------------------------------

READ BINARY FILE:

Matrix read:
0.00  1.00  2.00  3.00  4.00

1.00  2.00  3.00  4.00  5.00

2.00  3.00  4.00  5.00  6.00

3.00  4.00  5.00  6.00  7.00



--------------------------------------

SLICE MATRIX:

Previous matrix:
0.00  1.00  2.00  3.00  4.00

1.00  2.00  3.00  4.00  5.00

2.00  3.00  4.00  5.00  6.00

3.00  4.00  5.00  6.00  7.00



Result:
2.00  3.00

3.00  4.00



--------------------------------------

GET VALUE:

val: 0   val: 1   val: 2   val: 3   val: 4
val: 1   val: 2   val: 3   val: 4   val: 5
val: 2   val: 3   val: 4   val: 5   val: 6
val: 3   val: 4   val: 5   val: 6   val: 7

--------------------------------------

MULTIPLICATION OF MATRICES:

Previous matrix (1):
0.00  1.00  2.00  3.00  4.00

1.00  2.00  3.00  4.00  5.00

2.00  3.00  4.00  5.00  6.00

3.00  4.00  5.00  6.00  7.00



Previous matrix (2):
0.00  1.00  2.00  3.00

1.00  2.00  3.00  4.00

2.00  3.00  4.00  5.00

3.00  4.00  5.00  6.00

4.00  5.00  6.00  7.00



Result:
30.00  40.00  50.00  60.00

40.00  55.00  70.00  85.00

50.00  70.00  90.00  110.00

60.00  85.00  110.00  135.00



--------------------------------------

MULTIPLICATION OF MATRICES:

Previous matrix (1):
0.00  1.00  2.00  3.00

1.00  2.00  3.00  4.00

2.00  3.00  4.00  5.00

3.00  4.00  5.00  6.00

4.00  5.00  6.00  7.00



Previous matrix (2):
0.00  1.00  2.00  3.00  4.00

1.00  2.00  3.00  4.00  5.00

2.00  3.00  4.00  5.00  6.00

3.00  4.00  5.00  6.00  7.00



Result:
14.00  20.00  26.00  32.00  38.00

20.00  30.00  40.00  50.00  60.00

26.00  40.00  54.00  68.00  82.00

32.00  50.00  68.00  86.00  104.00

38.00  60.00  82.00  104.00  126.00



--------------------------------------

MULTIPLICATION PER CELLS:

Previous matrix (1):
0.00  1.00  2.00  3.00  4.00

1.00  2.00  3.00  4.00  5.00

2.00  3.00  4.00  5.00  6.00

3.00  4.00  5.00  6.00  7.00



Previous matrix (2):
0.00  -1.00  -2.00  -3.00  -4.00

-1.00  -2.00  -3.00  -4.00  -5.00

-2.00  -3.00  -4.00  -5.00  -6.00

-3.00  -4.00  -5.00  -6.00  -7.00



Result:
0.00  -1.00  -4.00  -9.00  -16.00

-1.00  -4.00  -9.00  -16.00  -25.00

-4.00  -9.00  -16.00  -25.00  -36.00

-9.00  -16.00  -25.00  -36.00  -49.00



--------------------------------------

add_value_matrix(0, -1, 0.00) -> Invalid indexes.

get_value_matrix(0, -1) -> Invalid indexes.

*/

    return 0;
}
