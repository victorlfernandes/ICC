#include <stdio.h>
#include <stdlib.h>

//reads a line from the buffer
//and return it as a string (with a \0 at the end)
char *read_line(){
    char c;
    int n_chars = 0;
    char *line = NULL;
    while ((c = getchar()) != '\n'){
        line = realloc (line, (n_chars + 1));
        line[n_chars] = c;
        n_chars++; 
    }
    //adding one memory space to allocate \0
    line = realloc (line, (n_chars + 1));
    line[n_chars] = '\0';
    return line;
}

int main(){

    int n_lines;
    scanf(" %d", &n_lines);

    //ignoring \n
    getchar();

    //turning the lines of the buffer into strings 
    //and storing the pointer for each one in 
    //a different position of the array 'line'
    char *line[n_lines];
    for (int i=0; i<n_lines; i++){
        line[i] = read_line();
    }

    //reading which lines are valid
    int n_valid_lines;
    scanf(" %d", &n_valid_lines);
    int valid_lines[n_valid_lines];
    for (int i=0; i<n_valid_lines; i++){
        scanf(" %d", &valid_lines[i]);
    }

    //printing the valid lines
    for (int i=0; i<n_valid_lines; i++){
        printf("%s\n", line[valid_lines[i]]);
    }

    //deallocating the memory 
    for (int i=0; i<n_lines; i++){
        free(line[i]);
    }
      
    return 0;
}