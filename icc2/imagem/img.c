#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


unsigned char **read_matrix(int lines, int columns) {

    unsigned char **matrix = malloc(lines * sizeof(unsigned char *));
    for (int i = 0; i < lines; i++)
        matrix[i] = malloc(columns * sizeof(unsigned char));

    char c;
    int i = 0;
    int j = 0;
    while ((c = getchar()) != EOF) {
        if (isdigit(c)) {
            matrix[i][j] = c;
            j++;
        }
        if (c == '\n') {
            i++;
            j = 0;
        }
    }

    return matrix;
}

void quad_tree(unsigned char **matrix, int lines, int columns, int i_start, int j_start) {

    // checking if the terms of the quadrant are the same
    bool equal = true;
    unsigned char prev_term = matrix[i_start][j_start];
    for (int i = i_start; i < lines + i_start; i++) {
        for (int j = j_start; j < columns + j_start; j++) {
            if (matrix[i][j] != prev_term) equal = false;
            prev_term = matrix[i][j];
        }
    }
    
    if (equal) 
        // printing one term representing all the quadrant
        printf("%c ", matrix[i_start][j_start]);

    else {
        // dividing into smaller quadrants
        printf("-1 ");
        int nxt_l = lines / 2;
        int nxt_c = columns / 2;
        quad_tree(matrix, nxt_l, nxt_c, i_start, j_start); 
        quad_tree(matrix, nxt_l, nxt_c, i_start, nxt_c + j_start); 
        quad_tree(matrix, nxt_l, nxt_c, nxt_l + i_start, j_start); 
        quad_tree(matrix, nxt_l, nxt_c, nxt_l + i_start, nxt_c + j_start);
    }
}



int main() {

    int lines;
    int columns;
    scanf(" %d %d\n", &lines, &columns);

    unsigned char **matrix = read_matrix(lines, columns);
    quad_tree(matrix, lines, columns, 0, 0);
    printf("\n");

    for (int i = 0; i < lines; i++) free(matrix[i]);
    free(matrix);
    return 0;
}