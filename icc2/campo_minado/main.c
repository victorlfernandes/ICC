/*******************************************************************************
 |                       USP - Universidade de São Paulo                       |
 |            ICMC - Instituto de Ciências Matemáticas e de Computação         |
 *******************************************************************************
 |                    Bacharelado em Ciências de Computação                    |
 |                                 2021/2                                      |
 |                SCC0201 - Introdução à Ciências da Computação 2              |
 |                                                                             |
 |              Autor: Victor Lucas de Almeida Fernandes (12675399)            |
 *******************************************************************************
 >                              Campo Minado                                  
 ******************************************************************************/

#include "mine_sweeper.h"
#include <stdlib.h>

int main() {
 
    //reading what the program must do
    int option;
    scanf(" %d ", &option);

    //loading board from file
    char file_name[8];
    fgets(file_name, 8, stdin);
    FILE *file_pointer = fopen(file_name, "r");
    if (file_pointer == NULL) {
        printf("File problem\n");
        exit(1);
    }
    int n_lines;
    int n_columns;
    char **board = read_matrix(file_pointer, &n_lines, &n_columns);
    fclose(file_pointer);

    switch (option) {

        case PRINT:
            print_matrix(stdout, board, n_lines, n_columns);
            break;

        case PRINT_WITH_TIPS:
            fills_tips(board, n_lines, n_columns);
            print_matrix(stdout, board, n_lines, n_columns);
            break;

        case USER_CONTROL: {
            fills_tips(board, n_lines, n_columns);
            //reading user play
            int i_move, j_move;
            scanf(" %d %d", &i_move, &j_move);
            if (board[i_move][j_move] == MINE) { //user loss, ends game
                print_matrix(stdout, board, n_lines, n_columns);
            }
            else if (board[i_move][j_move] == EMPTY) { //reveal all empty spaces
                char **hidden_board = create_hidden_board(n_lines, n_columns);
                reveal(board, hidden_board, n_lines, n_columns, i_move, j_move);
                print_matrix(stdout, hidden_board, n_lines, n_columns);
                for (int i = 0; i < n_lines; i++) free(hidden_board[i]);
                free(hidden_board);
            }
            else { //tip selected, reveal only the play position
                print_tip(board, n_lines, n_columns, i_move, j_move);
            } 
            break;
        }
    }

    //deallocating memory
    for (int i = 0; i < n_lines; i++) free(board[i]);
    free(board);

    return 0;
}
