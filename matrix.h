#include "cell.h"

typedef struct {

    Cell** head_lines;
    Cell** head_columns;
    int size_lines;
    int size_columns;

} Matrix;


//-------------------- MEMÓRIA --------------------

Matrix* create_matrix ();
void realloc_matrix ();
Matrix* destroy_matrix ();

//-------------------- LEITURA --------------------

Matrix* read_matrix ();

//-------------------- BINÁRIO --------------------

void bin_print_sparse_matrix (); //apenas valores não nulos devem ser impressos
Matrix* bin_read_sparse_matrix ();

//-------------------- FUNCIONALIDADES --------------------

Matrix* sum_matrix ();
Matrix* multiplication_of_matrix ();
Matrix* multiply_scalar_matrix ();
Matrix* multiply_per_cells_matrix ();
Matrix* swap_lines_matrix ();
Matrix* swap_columns_matrix ();
Matrix* slice_matrix ();
Matrix* transpose_matrix ();
Matrix* convolution_matrix ();

//-------------------- PRINT --------------------

void print_sparse_matrix ();
void print_dense_matrix ();

//-------------------- AUXILIARES --------------------

//-------------------- EXTRAS --------------------

Matrix* gauss_elimination_matrix ();
Matrix* determinant_matrix ();
Matrix* inverse_matrix ();