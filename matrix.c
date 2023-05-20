#include "matrix.h"
#include "cell.h"

#include <stdio.h>
#include <stdlib.h>

//-------------------- memory --------------------

Matrix* construct_matrix (int sz_lines, int sz_columns)
{   

    if (sz_lines <= 0 || sz_columns <= 0)
    {
        printf ("\033[91mInvalid size of matrix\n\033[0m");
        return NULL;
    }

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

void bin_print_sparse_matrix (char* file_name, Matrix* m)
{   

    if (m != NULL)
    {
        FILE *file = fopen(file_name, "wb");

        if (file == NULL)
        {
            printf("\033[91mERROR: Could not create file named '%s'.\n\033[0m", file_name);
            destroy_matrix (m);
            exit (0);
        }

        fwrite(&m->size_lines, sizeof(int), 1, file);
        fwrite(&m->size_columns, sizeof(int), 1, file);
        //printf ("lines: %d, columns: %d\n", m->size_lines, m->size_columns);

        for (int i=0; i< m->size_lines; i++)
        {   
            Cell* c = m->head_lines[i];
            while (c != NULL)
            {
                fwrite(&c->line, sizeof(int), 1, file);
                fwrite(&c->column, sizeof(int), 1, file);
                fwrite(&c->value, sizeof(float), 1, file);
                c = c->next_column;
            }
        }

        //print_dense_matrix (m);

        fclose (file);
    }
}

Matrix* bin_read_sparse_matrix (char* file_name)
{
    FILE *file = fopen(file_name, "rb");

    if (file == NULL)
    {
        printf("\033[91mERROR: Unable to open file named '%s'.\n\033[0m", file_name);
        return NULL;
    }

    int sz_lines = 0;
    int sz_columns = 0;

    fread(&sz_lines, sizeof(int), 1, file);
    fread(&sz_columns, sizeof(int), 1, file);
    //printf ("lines: %d, columns: %d\n", sz_lines, sz_columns);

    Matrix* m = construct_matrix (sz_lines, sz_columns);
    if (m != NULL)
    {
        float value;
        int idx_line;
        int idx_column;

        while (!feof (file))
        {   
            fread(&idx_line, sizeof(int), 1, file);
            fread(&idx_column, sizeof(int), 1, file);
            fread(&value, sizeof(float), 1, file);

            add_value_matrix (m, idx_line, idx_column, value);
        }

        print_dense_matrix (m);

        fclose (file);

        return m;
    }

    return NULL;
}

//-------------------- functionalities --------------------

void add_value_matrix(Matrix* m, int idx_line, int idx_column, float value)
{       
    //TRATAR CASO: SE FOR 0, DESTRUIR NÓ E REASSOCIAR

    if (m == NULL || idx_column >= m->size_columns || idx_line >= m->size_lines || idx_column < 0 || idx_line < 0)
    {
        printf ("\033[91mInvalid indexes.\033[0m\n");
        return;
    }   

    else if (value == 0)
    {
        if (m->head_lines[idx_line] == NULL || m->head_columns[idx_column] == NULL)
            return;


        Cell* aux = m->head_lines [idx_line];
        Cell* prev = NULL;

        while (aux != NULL)
        {
            if (aux->column == idx_column)
            {   
                if (prev != NULL)
                {
                    prev->next_column = aux->next_column;
                    break;
                }
                else 
                {
                    m->head_lines[idx_line] = m->head_lines[idx_line]->next_column;
                    
                    break;
                }
            }
            else if (aux->column > idx_column)
                return;

            prev = aux;
            aux = aux->next_column;
        }

        if (aux == NULL)
            return;

        aux = m->head_columns [idx_column];
        prev = NULL;

        while (aux != NULL)
        {
            if (aux->line == idx_line)
            {   
                if (prev != NULL)
                {
                    prev->next_line = aux->next_line;
                    destroy_cell(aux);
                    break;
                }
                else 
                {   
                    m->head_columns[idx_column] = m->head_columns[idx_column]->next_line;
                    destroy_cell (aux);
                    break;
                }  
            }

            else if (aux->line > idx_line)
                return;

            prev = aux;
            aux = aux->next_line;
        }
    }

    else 
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
        printf ("\033[91mInvalid indexes.\033[0m\n");
        destroy_matrix (m);
        exit (0);
    }
}

Matrix* sum_matrix (Matrix* m1, Matrix* m2)
{   
    if (m1->size_lines == m2->size_lines && m1->size_columns == m2->size_columns)
    {
        Matrix* sum = construct_matrix(m1->size_lines, m1->size_columns);

        for (int i=0; i< m1->size_lines; i++)
        {
            for (int j=0; j< m1->size_columns; j++)
            {   
                float v1 = get_value_matrix(m1, i, j);
                float v2 = get_value_matrix(m2, i, j);
                add_value_matrix(sum, i, j, v1+v2);
            }
        }

        
        //print_dense_matrix (m1);
        //print_dense_matrix(m2);
        print_dense_matrix(sum);
        

        return sum;
    }

    else 
    {   
        printf ("\033[91mInvalid sizes of matrices.\033[0m\n");
        return NULL;
    }
    
}

Matrix* multiplication_of_matrix (Matrix* m1, Matrix* m2)
{
    if (m1->size_columns == m2->size_lines && m1 != NULL && m2 != NULL)
    {
        Matrix* result = construct_matrix (m1->size_lines, m2->size_columns);

        for (int i=0; i < m1->size_lines; i++)
        {   
            int sum = 0;

            for (int j=0; j < m2->size_columns; j++)
            {
                for (int h=0; h< m1->size_columns; h++)
                    sum += (get_value_matrix(m1, i, h) * get_value_matrix(m2, h, j));  
                
                add_value_matrix (result, i, j, sum);
                sum = 0;
            }
        }

        //print_dense_matrix (m1);
        //print_dense_matrix(m2);
        print_dense_matrix(result);
        
        return result;
    }
    
    printf ("\033[91mInvalid matrices.\n\033[0m");
    return NULL;
}

Matrix* multiply_scalar_matrix (Matrix* m, float scalar)
{   
    if (m != NULL)
    {
        Matrix* cpp = copy_matrix(m);

        //fazer a cópia durante o loop, para evitar 2 loops

        for (int i=0; i< m->size_lines; i++)
        {
            Cell* c = cpp->head_lines[i];
            while (c != NULL)
            {
                c->value *= scalar;
                c = c->next_column;
            }
        }

        //print_dense_matrix (m);
        print_dense_matrix (cpp);

        return cpp;
    }
    
    else
    {
        printf ("\033[91mInvalid matrix.\033[0m\n");
        return NULL;
    }
}

Matrix* multiply_per_cells_matrix (Matrix* m1, Matrix* m2)
{   

    if (m1->size_lines == m2->size_lines && m1->size_columns == m2->size_columns)
    {
        Matrix* result = construct_matrix (m1->size_lines, m1->size_columns);

        for (int i=0; i< m1->size_lines; i++)
        {
            for (int j=0; j< m1->size_columns; j++)
            {   
                float v1 = get_value_matrix(m1, i, j);
                float v2 = get_value_matrix(m2, i, j);
                add_value_matrix(result, i, j, v1*v2);
            }
        }

        print_dense_matrix (m1);
        print_dense_matrix (m2);
        print_dense_matrix (result);

        return result;
    }
    
    else
    {   
        printf ("\033[91mInvalid matrix.\033[0m\n");
        return NULL;
    }

}

Matrix* swap_lines_matrix (Matrix* m, int idx_line1, int idx_line2)
{
    if (idx_line1 >= m->size_lines || idx_line1 < 0 || idx_line2 >= m->size_lines || idx_line2 < 0 || idx_line1 == idx_line2)
    {
        printf ("\033[91mInvalid Indexes.\033[0m\n");
        return NULL;
    }   

    print_dense_matrix (m);

    Matrix* swap = construct_matrix (m->size_lines, m->size_columns);
    int line;

    for( int i = 0; i< m->size_columns; i++)
    {
        Cell* c = m->head_columns[i];
        while (c != NULL)
        {   
            if (c->line == idx_line1)
                line = idx_line2;
            
            else if (c->line == idx_line2)
                line = idx_line1;
            
            else 
                line = c->line;

            add_value_matrix (swap, line, c->column, c->value);
            c = c->next_line;
        }
    }

    print_dense_matrix(swap);
    return swap;
}

Matrix* swap_columns_matrix (Matrix* m, int idx_column1, int idx_column2)
{
    if (idx_column1 >= m->size_columns || idx_column1 < 0 || idx_column2 >= m->size_columns || idx_column2 < 0 || idx_column1 == idx_column2)
    {
        printf ("\033[91mInvalid Indexes.\033[0m\n");
        return NULL;
    }   

    print_dense_matrix (m);

    Matrix* swap = construct_matrix (m->size_lines, m->size_columns);
    int column;

    for( int i = 0; i< m->size_lines; i++)
    {
        Cell* c = m->head_lines[i];
        while (c != NULL)
        {   
            if (c->column == idx_column1)
                column = idx_column2;
            
            else if (c->column == idx_column2)
                column = idx_column1;
            
            else 
                column = c->column;

            add_value_matrix (swap, c->line, column, c->value);
            c = c->next_column;
        }
    }

    print_dense_matrix(swap);
    return swap;
}

Matrix* slice_matrix (Matrix* m, int fst_line, int fst_column, int last_line, int last_column)
{   

    if (fst_line < 0 || fst_line >= m->size_lines || last_line < 0 || last_line >= m->size_lines || fst_column < 0 || fst_column >= m->size_columns || last_column < 0 || last_column >= m->size_columns)
    {
        printf ("\033[91mInvalid Indexes.\033[0m\n");
        return NULL;
    }

    if (fst_line == last_line && last_column == fst_column)
    {
        printf ("\033[91mInvalid Indexes.\033[0m\n");
        return NULL;
    }


    if (fst_line == 0 && fst_column == 0 && last_line == m->size_lines - 1 && last_column == m->size_columns - 1)
    {   
        printf ("\n\033[91mNo slicing needed.\033[0m\n\n");
        print_dense_matrix (m);
        return NULL;
    }

    int lines = last_line - fst_line + 1;
    int columns = last_column - fst_column + 1;

    Matrix* slice = construct_matrix (lines, columns);
    for (int i = fst_line; i <= last_line; i++)
    {
        for (int j = fst_column; j <= last_column; j++)
        {
            add_value_matrix (slice, i - fst_line, j-fst_column, get_value_matrix(m, i, j));
            //print_sparse_matrix (slice);
        }
    }

    print_dense_matrix (m);
    print_dense_matrix (slice);

    return slice;
}

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
    print_dense_matrix(transp);
        
    return transp;
}

Matrix* convolution_matrix ();





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
    if (m == NULL)
    {
        printf ("Invalid Matrix.\n");
        return;
    }

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
