#pragma once 

typedef struct {

    float value;
    int line;
    int column;
    struct Cell* next_line;
    struct Cell* next_column;

}Cell;


//-------------------- memory --------------------

Cell* construct_cell (int line, int column, float value);
void destroy_cell (Cell* c);

//-------------------- auxiliary --------------------
