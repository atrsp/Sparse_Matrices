#pragma once 

typedef struct {

    int value;
    int line;
    int column;
    Cell* next_line;
    Cell* next_column;

} Cell;


//-------------------- memory --------------------

Cell* create_cell ();
void destroy_cell (Cell* c);

//-------------------- auxiliary --------------------
