#include "cell.h"
#include <stdio.h>
#include <stdlib.h>

//-------------------- memory --------------------

Cell* create_cell (int line, int column, int value)
{
    Cell* c = (Cell*)calloc(1, sizeof(Cell));

    c->value = value;
    c->line = line;
    c->column = column;
    
    c->next_column = NULL;
    c->next_line = NULL;

    return c;
}

void destroy_cell (Cell* c)
{
    free (c);
}
