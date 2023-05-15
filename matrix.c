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
    //loops to destroy cells
    free (m->head_lines);
    free (m->head_columns);
    free (m);
}

//-------------------- reading --------------------

void read_matrix (Matrix* m)
{
    float value;
    Cell* c = NULL;
    Cell* prev_l = NULL;
    Cell* prev_c = NULL;

    for (int i=0; i < m->size_lines; i++)
    {
        for (int j=0; j < m->size_columns; j++)
        {
            scanf ("%d", &value);
            
            if (value != 0)
            {   
                c = create_cell (i, j, value);
                m->size_cells++;

                if (m->head_columns[j] == NULL)
                {
                    m->head_columns[j] = c;
                    prev_c = c;                    
                }

                else 
                {
                    //prev_c->next = c;
                    prev_c = c;
                }

                if (m->head_lines[i] == NULL)
                {
                    m->head_lines[i] = c;
                    prev_l = c;                    
                }
                else 
                {
                    //prev_l->next = c;
                    prev_l = c;
                }
            }

        }
    }
}

//-------------------- print --------------------

void print_sparse_matrix ();

void print_dense_matrix (Matrix* m)
{      
    for (int i=0; i< m->size_lines; i++)
    {
        Cell* c = m->head_lines [i];

        while (c != NULL)
        {

        }
    }


}