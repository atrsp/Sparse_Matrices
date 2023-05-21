#include "cell.h"
#include <stdio.h>
#include <stdlib.h>

//-------------------- memory --------------------

Cell *construct_cell(int line, int column, float value)
{

    // COMPLEXITY
    // The time complexity of this function is O(1) because there is no iteration, which means it's time of execution is constant.

    Cell *c = (Cell *)calloc(1, sizeof(Cell));

    c->value = value;
    c->line = line;
    c->column = column;

    c->next_line = NULL;
    c->next_column = NULL;

    return c;
}

void destroy_cell(Cell *c)
{
    // COMPLEXITY
    // The time complexity of this function is O(1) because there is no iteration, which means it's time of execution is constant.

    if (c != NULL)
        free(c);
}
