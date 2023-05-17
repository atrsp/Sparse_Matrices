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

Matrix* construct_matrix (int sz_lines, int sz_columns); //done
void destroy_matrix (Matrix* m); //done

//-------------------- binary --------------------

void bin_print_sparse_matrix (char* name, Matrix* m); //done
Matrix* bin_read_sparse_matrix (char* argv); //done

//-------------------- functionalities --------------------

void add_value_matrix(Matrix* m, int idx_line, int idx_column, float value); //done
float get_value_matrix (Matrix* m, int idx_line, int idx_column); //done
Matrix* sum_matrix (Matrix* m1, Matrix* m2); //done
Matrix* multiplication_of_matrix (Matrix* m1, Matrix* m2); //done
Matrix* multiply_scalar_matrix (Matrix* m, float scalar); //done
Matrix* multiply_per_cells_matrix (Matrix* m1, Matrix* m2); //done
Matrix* swap_lines_matrix ();
Matrix* swap_columns_matrix ();
Matrix* slice_matrix (Matrix* m, int fst_line, int fst_column, int last_line, int last_column);
Matrix* transpose_matrix (Matrix* m); //done
Matrix* convolution_matrix ();

//-------------------- print --------------------

void print_sparse_matrix (Matrix* m); //done
void print_dense_matrix (Matrix* m); //done

//-------------------- auxiliary --------------------

Matrix* copy_matrix (Matrix* m); //done

//-------------------- extras --------------------

Matrix* gauss_elimination_matrix ();
Matrix* determinant_matrix ();
Matrix* inverse_matrix ();