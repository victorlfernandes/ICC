/*****************************************************************************************
 |                            USP - Universidade de São Paulo                            |
 |                 ICMC - Instituto de Ciências Matemáticas e de Computação              |
 *****************************************************************************************
 |                         Bacharelado em Ciências de Computação                         |
 |                                      2021/2                                           |
 |                      SCC0201 - Introdução à Ciências da Computação 2                  |
 |                                                                                       |
 |                  Autor: Victor Lucas de Almeida Fernandes (12675399)                  |
 *****************************************************************************************
 >                                   Campo Minado
 ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define PRINT           1
#define PRINT_WITH_TIPS 2
#define USER_CONTROL    3

#define MINE   '*'
#define EMPTY  '.'
#define HIDDEN 'X'

/**
 * @brief Reads a matrix from stream and return its pointer. Also returns the 
 *        number of lines and columns by reference. 
 * 
 * @param stream    Pointer from where to read.
 * @param n_lines   Number of lines of the matrix.
 * @param n_columns Number of columns of the matrix.
 * 
 * @return char ** - Pointer to the matrix. 
 */
char **read_matrix(FILE *stream, int *n_lines, int *n_columns);

/**
 * @brief Prints the matrix in stream.
 * 
 * @param stream    Pointer from where to print
 * @param matrix    Matrix pointer to be written
 * @param n_lines   Number of lines of the matrix.
 * @param n_columns Number of columns of the matrix.
 * 
 * @return Void.
 */
void print_matrix(FILE *stream, char **matrix, int n_lines, int n_columns);

/**
 * @brief Fills the mine sweeper board with que number of mines next to
 *        each piece.
 * 
 * @param matrix    Board pointer.
 * @param n_lines   Number of lines of the board.
 * @param n_columns Number of columns of the board.
 * 
 * @return Void.
 */
void fills_tips(char **matrix, int n_lines, int n_columns);

/**
 * @brief Creates an matrix with all hidden characters and return its pointer.
 * 
 * @param n_lines   Number of lines of the matrix.
 * @param n_columns Number of columns of the matrix.
 * 
 * @return char ** - Pointer to the matrix.
 */
char **create_hidden_board(int n_lines, int n_columns);

/**
 * @brief Recursively reveals empty spaces on the mine sweeper board until it 
 *        finds an edge or tip. Check the position in 'board' and reveal it in
 *        'hidden_board'.
 * 
 * @param board        Board pointer.
 * @param hidden_board Board filled with hidden characters pointer.
 * @param n_lines      Number of lines of the board.
 * @param n_columns    Number of columns of the board.
 * 
 * @return Void.
 */
void reveal(char **board, char **hidden_board, int n_lines, int n_columns, int i, int j);

/**
 * @brief Prints the mine sweeper board only with the tip selected revealed. 
 *        The other characters are hidden.
 * 
 * @param matrix    Board pointer.
 * @param n_lines   Number of lines of the board.
 * @param n_columns Number of columns of the board.
 * @param i_tip     Line of the selected tip.
 * @param j_tip     Column of the selected tip.
 * 
 * @return Void.
 */
void print_tip(char **matrix, int n_lines, int n_columns, int i_tip, int j_tip);

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

char **read_matrix(FILE *stream, int *n_lines, int *n_columns) {

    //allocating initial bytes
    int init_bytes = 32;
    int l_bytes    = init_bytes;
    int c_bytes    = init_bytes;
    char **matrix  = malloc(l_bytes * sizeof(char *));
    for (int i = 0; i < l_bytes; i++)
        matrix[i]  = malloc(c_bytes * sizeof(char));

    int cur_line   = 0;
    int cur_column = 0;
    bool reading   = true;
    do { 

        //checking if it needs reallocation 
        if (cur_line == l_bytes) {
            l_bytes *= 2;
            matrix = realloc(matrix, l_bytes * sizeof(char *));
            for (int i = l_bytes / 2; i < l_bytes; i++)
                matrix[i] = malloc(c_bytes * sizeof(char));
        }
        if (cur_column == c_bytes) {
            c_bytes *= 2;
            matrix[cur_line] = realloc(matrix[cur_line], c_bytes * sizeof(char *));
        }

        //reading the new character
        char c = fgetc(stream);
        switch (c) {

            case EOF:
                matrix[cur_line][cur_column] = '\n';
                reading = false;
                break;

            case '\n':
                //assigning the line break 
                matrix[cur_line][cur_column] = c;
                *n_columns = cur_column + 1;
                //reallocating the line to its size if necessary
                if (c_bytes > cur_column)
                    matrix[cur_line] = realloc(matrix[cur_line], cur_column + 1);
                cur_column = 0;
                c_bytes = init_bytes;
                cur_line++;
                break;

            default:
                //assigning the read character
                matrix[cur_line][cur_column] = c;
                cur_column++;
                break;
        }

    } while (reading);

    //reallocating the matrix to its size and deallocating the empty lines
    if (l_bytes > cur_line) {
        for (int i = cur_line; i < l_bytes; i++) free(matrix[i]);
        matrix = realloc(matrix, cur_line * sizeof(char *));
    }

    *n_lines = cur_line;
    return matrix;
}

void print_matrix(FILE *stream, char **matrix, int n_lines, int n_columns) {
    for (int i = 0; i < n_lines; i++) {
        for (int j = 0; j < n_columns; j++)
            fprintf(stream, "%c", matrix[i][j]);
    }
}   

void fills_tips(char **matrix, int n_lines, int n_columns) {
    //going through each term of the board
    for (int i = 0; i < n_lines; i++) {
        for (int j = 0; j < n_columns; j++) {
            int mine_counter = 0;
            if (matrix[i][j] == EMPTY) {
                //going through the 8 neighbors of the term 
                //and counting how many are mines
                for (int k = i - 1; k <= i + 1; k++) {
                    for (int w = j - 1; w <= j + 1; w++) {
                        //checking if the neighbor position is valid
                        if (k >= 0 && k < n_lines && w >= 0 && w < n_columns) {
                            if (matrix[k][w] == MINE)
                                mine_counter++;
                        }
                    }
                }
                if (mine_counter > 0)
                    matrix[i][j] = mine_counter + '0';
            } 
        }
    }
}

char **create_hidden_board(int n_lines, int n_columns) {
    char **matrix = malloc(n_lines * sizeof(char *));
    for (int i = 0; i < n_lines; i++) {
        matrix[i] = malloc(n_columns * sizeof(char));
        //fills all the terms with the 'HIDDEN' character
        for (int j = 0; j < n_columns - 1; j++)
            matrix[i][j] = HIDDEN;
        matrix[i][n_columns - 1] = '\n';
    }
    return matrix;
}

void reveal(char **board, char **hidden_board, int n_lines, int n_columns, int i, int j) {
    //edge, first stop condition
    if (i < 0 || j < 0 || i > (n_lines - 1) || j >= (n_columns - 1))
        return;
    //tip, second stop condition
    if (isdigit(board[i][j]) != 0) {
        hidden_board[i][j] = board[i][j];
        return;
    }
    //recursive step
    if (board[i][j] == EMPTY) {
        hidden_board[i][j] = EMPTY;
        board[i][j] = 1; //avoiding to pass twice by the same term
        //calling the recursive function for the 8 neighbors
        for (int k = i - 1; k <= i + 1; k++) {
            for (int w = j - 1; w <= j + 1; w++)
                reveal(board, hidden_board, n_lines, n_columns, k, w);
        }
    }
}

void print_tip(char **matrix, int n_lines, int n_columns, int i_tip, int j_tip) {
    for (int i = 0; i < n_lines; i++) {
        for (int j = 0; j < n_columns - 1; j++) {
            //reveal only the play position
            if (i == i_tip && j == j_tip)
                printf("%c", matrix[i][j]); 
            else
                printf("X");
        }
        printf("\n");
    }
}
