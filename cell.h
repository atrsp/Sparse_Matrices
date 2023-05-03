
typedef struct {

    int value;
    int line;
    int column;
    Cell* next_line;
    Cell* next_column;

} Cell;


//-------------------- MEMÓRIA --------------------

Cell* create_cell ();
Cell* destroy_cell ();

//-------------------- AUXILIARES --------------------
