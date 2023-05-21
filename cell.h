#pragma once

typedef struct cell
{

    float value;
    int line;
    int column;
    struct cell *next_line;
    struct cell *next_column;

} Cell;

//-------------------- memory --------------------

Cell *construct_cell(int line, int column, float value);
void destroy_cell(Cell *c);
