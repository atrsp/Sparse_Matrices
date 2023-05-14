#pragma once
#include "cell.h"

typedef struct {

    Cell** head_lines;
    Cell** head_columns;
    int size_lines;
    int size_columns;
    int size_cells;

} Matrix;


//-------------------- memory --------------------

Matrix* create_matrix (int sz_lines, int sz_columns);
void destroy_matrix (Matrix* m);

//-------------------- reading --------------------

void read_matrix (Matrix* m);

//-------------------- binary --------------------

void bin_print_sparse_matrix (); //apenas valores não nulos devem ser impressos
Matrix* bin_read_sparse_matrix ();

//-------------------- functionalities --------------------

void change_value_matrix();
Matrix* sum_matrix ();
Matrix* multiplication_of_matrix ();
Matrix* multiply_scalar_matrix ();
Matrix* multiply_per_cells_matrix ();
Matrix* swap_lines_matrix ();
Matrix* swap_columns_matrix ();
Matrix* slice_matrix ();
Matrix* transpose_matrix ();
Matrix* convolution_matrix ();

//-------------------- print --------------------

void print_sparse_matrix ();
void print_dense_matrix ();

//-------------------- auxiliary --------------------

//-------------------- extras --------------------

Matrix* gauss_elimination_matrix ();
Matrix* determinant_matrix ();
Matrix* inverse_matrix ();