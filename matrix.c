#include "matrix.h"
#include "cell.h"

#include <stdio.h>
#include <stdlib.h>

//-------------------- memory --------------------

Matrix* construct_matrix (int sz_lines, int sz_columns)
{
    Matrix* m = (Matrix*)calloc(1, sizeof(Matrix));
    
    m->size_columns = sz_columns;
    m->size_lines = sz_lines;
    m->size_cells = 0;

    m->head_columns = (Cell**)calloc(m->size_columns, sizeof(Cell));
    m->head_lines = (Cell**)calloc(m->size_lines, sizeof(Cell));

    return m;
}

void destroy_matrix (Matrix* m)
{
    if (m != NULL)
    {
        
    for (int i = 0; i < m->size_lines; i++)
    {   
        Cell* c = m->head_lines[i];
        Cell* prev = NULL;

        while (c != NULL)
        {   
            prev = c->next_column;
            destroy_cell(c);
            c = prev;
        }
    }
    
    free (m->head_lines);
    free (m->head_columns);
    free (m);
    }
}

//-------------------- binary --------------------

void bin_print_sparse_matrix (); 
Matrix* bin_read_sparse_matrix ();

//-------------------- functionalities --------------------

void add_value_matrix(Matrix* m, int idx_line, int idx_column, float value)
{       

    if (m != NULL && value != 0 && idx_line >= 0 && idx_line < m->size_lines && idx_column >= 0 && idx_column < m->size_columns)
    {   

        //por colunas

        Cell* aux = m->head_lines [idx_line];
        Cell* prev = NULL;

        Cell* c = construct_cell (idx_line, idx_column, value);
        m->size_cells++;

        if (m->head_lines[idx_line] == NULL)
            m->head_lines[idx_line] = c;
        

        else 
        {
            while (aux != NULL)
            {   
                if (idx_column < aux->column)
                {
                    if (prev != NULL)
                    {
                        prev->next_column = c;
                        c->next_column = aux;
                        break;
                    }

                    else 
                    {
                        prev = m->head_lines[idx_line];
                        m->head_lines[idx_line] = c;
                        c->next_column = prev;
                        break;
                    }

                }

                if (aux->column == idx_column)
                {   
                    m->size_cells--;
                    destroy_cell (c);
                    aux->value = value;
                    break;
                }

                prev = aux;
                aux = aux->next_column;
            }

            if (aux == NULL)
                if (prev != NULL)
                    prev->next_column = c;
        
        }

        // por linhas

        aux = m->head_columns[idx_column];
        prev = NULL;

        if (m->head_columns[idx_column] == NULL)
            m->head_columns[idx_column] = c;

        else 
        {
            while (aux != NULL)
            {   
                if (idx_line < aux->line)
                {
                    if (prev != NULL)
                    {
                        prev->next_line = c;
                        c->next_line = aux;
                        m->size_cells++;
                        break;
                    }

                    else 
                    {
                        prev = m->head_columns[idx_column];
                        m->head_columns[idx_column] = c;
                        c->next_line = prev;
                        break;
                    }
                }

                if (aux->line == idx_line)
                {
                    aux->value = value;
                    break;
                }

                prev = aux;
                aux = aux->next_line;
            }

            if (aux == NULL)
                if (prev != NULL)
                    prev->next_line = c;
        
        }
    }

    if (idx_column > m->size_columns || idx_line > m->size_lines || idx_column < 0 || idx_line < 0)
    {
        printf ("Invalid indexes.\n");
        destroy_matrix (m);
        exit (0);
    }
}

float get_value_matrix (Matrix* m, int idx_line, int idx_column)
{   
    
    //como tratar o caso de eu passar uma matriz não inicializada? -> quebra o código

    if (m != NULL && idx_line >= 0 && idx_line < m->size_lines && idx_column >= 0 && idx_column < m->size_columns)
    {
        Cell* c = m->head_columns[idx_column];
        while (c != NULL)
        {
            if (c->line == idx_line)
                return c->value; 
            
            c = c->next_line;
        }

        return 0;
    }
    
    else {
        printf ("Invalid indexes.\n");
        destroy_matrix (m);
        exit (0);
    }
}

Matrix* sum_matrix (Matrix* m1, Matrix* m2)
{
    Matrix* sum = copy_matrix(m1);

    for (int i=0; i< m1->size_lines; i++)
    {
        Cell* c = m1->head_lines[i];
        while (c != NULL)
        {
            c = c->next_column;
        }
    }

    return sum;
}

Matrix* multiplication_of_matrix ();

Matrix* multiply_scalar_matrix (Matrix* m, float scalar)
{   
    if (m != NULL)
    {
        Matrix* cpp = copy_matrix(m);

        for (int i=0; i< m->size_lines; i++)
        {
            Cell* c = cpp->head_lines[i];
            while (c != NULL)
            {
                c->value *= scalar;
                c = c->next_column;
            }
        }

        print_dense_matrix (m);
        print_dense_matrix (cpp);

        return cpp;
    }
    
    else
    {
        printf ("Invalid matrix.\n");
        exit (0);
    }
}

Matrix* multiply_per_cells_matrix ();
Matrix* swap_lines_matrix ();
Matrix* swap_columns_matrix ();
Matrix* slice_matrix ();

Matrix* transpose_matrix (Matrix* m)
{
    Matrix* transp = construct_matrix(m->size_columns, m->size_lines);

    for (int i=0; i< m->size_lines; i++)
    {
        Cell* c = m->head_lines[i];

        while (c != NULL)
        {
            add_value_matrix (transp, c->column, c->line, c->value);
            c = c->next_column;
        }
    }

    //print_dense_matrix (m);
    //print_dense_matrix(transp);
        
    return transp;
}


//-------------------- print --------------------

void print_sparse_matrix (Matrix* m)
{
    for (int i=0; i< m->size_lines; i++)
    {   
        Cell* c = m->head_lines[i];
        while (c != NULL)
        {
            printf ("(%d, %d) - %.2f\n", c->line, c->column, c->value);
            c = c->next_column;
        }
    }

    printf ("\n\n");
}

void print_dense_matrix (Matrix* m)
{     
    //por colunas
    for (int i=0; i< m->size_lines; i++)
    {
        Cell* c = m->head_lines [i];

        for (int j=0; j < m->size_columns; j++)
        {   
            if (c != NULL && c->line == i && c->column == j)
            {
                printf ("%.2f  ", c->value);
                c = c->next_column;
            }
            else
                printf ("0.00  ");

        }

        printf ("\n\n");
    }

    printf ("\n\n");

    //por linhas
    /*
    for (int i=0; i< m->size_columns; i++)
    {
        Cell* c = m->head_columns [i];

        for (int j=0; j < m->size_lines; j++)
        {   
            if (c != NULL && c->column == i && c->line == j)
            {
                printf ("%.0f  ", c->value);
                c = c->next_line;
            }
            else
                printf ("0  ");

        }

        printf ("\n\n");
    }

    printf ("\n\n");

    */
}


//-------------------- auxiliary --------------------

Matrix* copy_matrix (Matrix* m)
{
    Matrix* cpp = construct_matrix (m->size_lines, m->size_columns);

    for (int i=0; i< m->size_lines; i++)
    {
        Cell* c = m->head_lines[i];
        while (c != NULL)
        {
            add_value_matrix(cpp, c->line, c->column, c->value);
            c = c->next_column;
        }
    }

    //print_dense_matrix (cpp);
    return cpp;
}

//-------------------- extras --------------------