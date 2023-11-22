#ifndef _MINE_SWEEPER_H_
#define _MINE_SWEEPER_H_

#include <stdio.h>

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

#endif
