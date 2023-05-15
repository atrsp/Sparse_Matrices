#include "matrix.h"
#include "cell.h"

#include <stdio.h>
#include <stdlib.h>

void print_menu ()
{
    printf ("\033[91m\033[1mSparseMatrix\n\033[0m");
    printf ("Choose a function:\n\n");
    printf ("\t1. Print Sparse Matrix;\n");
    printf ("\t2. Print Dense Matrix;\n");
    printf ("\t3. Swap Lines;\n");
    printf ("\t4. Swap Columns;\n");
    printf ("\t5. Swap Lines;\n");
    printf ("\t6. Slice Matrix;\n");
    printf ("\t7. Save as Binary File;\n");
    printf ("\t8. Multiply by scalar;\n");
    printf ("\t9. Multiply matrices;\n");
    printf ("\t10. Multiply cell by cell;\n");
    printf ("\t11. Sum Matrices;\n");
    printf ("\t12. Transpose Matrix;\n");
    printf ("\t13. Matrix Convolution;\n");
    printf ("\t14. Change cell value;\n");
    printf ("\t15. Get cell value;\n");


    printf ("\nType the number of the funcion: \033[91m");

}

int main (){

    int sz_lines = 0;
    int sz_columns = 0;
    int option = -1;


    printf ("Type the number of lines of your matrix: \033[91m");
    scanf ("%d", &sz_lines);

    printf ("\033[0mType the number of columns of your matrix: \033[91m");
    scanf ("%d", &sz_columns);
    printf ("\033\n[0m");

    //o programa pede uma matriz principal e, caso use funções que envolvem 2 ou + matrizes, o código pedirá pela segunda;

    Matrix* m = create_matrix (sz_lines, sz_columns);
    read_matrix (m);
    print_dense_matrix (m);
    
    /*
    print_menu ();
    scanf ("%d", &option);
    printf ("\033[0m");

    switch (option){

        case 1:
        break;

        case 2:
        break;

        case 3:
        break;

        case 4:
        break;

        case 5:
        break;

        case 6:
        break;

        case 7:
        break;

        case 8:
        break;

        case 9:
        break;

        case 10:
        break;

        case 11:
        break;

        case 12:
        break;

        case 13:
        break;

        case 14:
        break;

        case 15:
        break;

        default:
            printf ("\n\033[91mERROR\033[0m\n");
            printf ("There's no option number %d.\n", option);
            printf ("Please type a valid number.\n");
        break;
    }
    */

    return 0;
}