#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


//reads alphanumeric characters, spaces or slashes from
//the buffer and return it as a uppercase string 
char *read_line();

//verifies if the string is a palindrome
bool palindrome(char *string, int first_index, int second_index, int equal_counter);

int main(){

    //reading an uppercase string with alphanumeric characters, spaces or slashes
    char *string = read_line();

    //creating an auxiliary string without spaces and slashes
    char *aux_string = malloc(strlen(string));
    for (int i = 0, j = 0; i <= strlen(string); i++, j++){
        if (string[i] == ' ' || string[i] == '/'){
            i++;
        }
        aux_string[j] = string[i];
    }

    //checking if the string is a palindrome
    bool result = palindrome(aux_string, 0, strlen(aux_string) - 1, 0);
    if (result){
        //checking if the palindrome is direct or indirect
        bool type = palindrome(string, 0, strlen(string) - 1, 0);
        if (type){
            printf("Palindromo direto\n");
        }
        else{
            printf("Palindromo indireto\n");
        }
    }
    else{
        printf("Nao eh um palindromo\n");
    }

    //deallocating the memory
    free(string);
    free(aux_string);

    return 0;
}

char *read_line(){
    char c;
    int n_chars = 0;
    char *line = NULL;
    while ((c = getchar()) != '\n'){
        if ((isalnum(c) != 0) || (c == ' ') || (c == '/')){
            line = realloc (line, (n_chars + 1));
            line[n_chars] = toupper(c);
            n_chars++; 
        }
    }
    //adding one memory space to allocate \0
    line = realloc (line, (n_chars + 1));
    line[n_chars] = '\0';
    return line;
}   

bool palindrome(char *string, int first_index, int second_index, int equal_counter){
    //checking if the characters differ
    if (string[first_index] != string[second_index]){
        return false;
    }
    //checking if the process is done
    if (first_index == second_index || equal_counter == (strlen(string) / 2)){ 
        return true;
    }
    //continuing the proces
    return palindrome(string, first_index + 1, second_index - 1, equal_counter + 1);
}