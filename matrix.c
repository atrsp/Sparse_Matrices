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
    
    Cell* prev = NULL;

    for (int i=0; i< m->size_columns; i++)
    {   
        Cell* c = m->head_columns[i];

        while (c!= NULL)
        {   
            prev = c;
            free (c);
            c = prev->next_line;
        }
    }
    

    free (m->head_lines);
    free (m->head_columns);
    free (m);
}

//-------------------- binary --------------------


//-------------------- functionalities --------------------

void add_value_matrix(Matrix* m, int idx_line, int idx_column, float value)
{       

    if (value != 0 && idx_line > 0 && idx_line < m->size_lines && idx_column > 0 && idx_column < m->size_columns)
    {   
        Cell* aux = m->head_lines [idx_line];
        Cell* prev = NULL;

        while (aux != NULL)
        {   
            if (aux->column == idx_column)
            {
                aux->value = value;
                break;
            }

            if (prev != NULL)
            {
                if (prev->column < idx_column && aux->column > idx_column)
                {   
                    Cell* c = construct_cell (idx_line, idx_column, value);
                    prev->next_column = c;
                    c->next_column = aux;
                    m->size_cells++;

                    break;
                }
            }

            prev = aux;
            aux = aux->next_column;
        }

        if (aux == NULL)
        {
            Cell* c = construct_cell (idx_line, idx_column, value);

            if (prev != NULL)
                prev->next_column = c;

            else
                m->head_lines[idx_line] = c;

            m->size_cells++;
        }
    }
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
                printf ("0  ");

        }

        printf ("\n\n");
    }


}