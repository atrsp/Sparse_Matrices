#pragma once
#include "cell.h"

typedef struct
{

    Cell **head_lines;
    Cell **head_columns;
    int size_lines;
    int size_columns;
    int size_cells;

} Matrix;

//-------------------- memory --------------------

Matrix *construct_matrix(int sz_lines, int sz_columns);
void destroy_matrix(Matrix *m);

//-------------------- binary --------------------

void bin_print_sparse_matrix(char *name, Matrix *m);
Matrix *bin_read_sparse_matrix(char *argv);

//-------------------- functionalities --------------------

void add_value_matrix(Matrix *m, int idx_line, int idx_column, float value);
float get_value_matrix(Matrix *m, int idx_line, int idx_column);
Matrix *sum_matrix(Matrix *m1, Matrix *m2);
Matrix *multiplication_of_matrix(Matrix *m1, Matrix *m2);
Matrix *multiply_scalar_matrix(Matrix *m, float scalar);
Matrix *multiply_per_cells_matrix(Matrix *m1, Matrix *m2);
Matrix *swap_lines_matrix(Matrix *m, int idx_line1, int idx_line2);
Matrix *swap_columns_matrix(Matrix *m, int idx_column1, int idx_column2);
Matrix *slice_matrix(Matrix *m, int fst_line, int fst_column, int last_line, int last_column);
Matrix *transpose_matrix(Matrix *m);
Matrix *convolution_matrix(Matrix *m, Matrix *kernel);

//-------------------- print --------------------

void print_sparse_matrix(Matrix *m);
void print_dense_matrix(Matrix *m);

//-------------------- auxiliary --------------------

float sum_cells_matrix (Matrix* m);
