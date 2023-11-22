#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

char *read_line(FILE *stream){
    char c;
    int n_chars = 0;
    char *line = NULL;
    while ((c = fgetc(stream)) != '\n' && c != EOF){
        line = realloc (line, (n_chars + 1));
        line[n_chars] = c;
        n_chars++; 
    }
    line = realloc (line, (n_chars + 1));
    line[n_chars] = '\0';
    return line;
}

double calcula_expressao(char *expressao, int indice){
    if (expressao[indice] == '('){
        double primeiro_termo = calcula_expressao(expressao, indice + 2);
        double segundo_termo = calcula_expressao(expressao, indice + 3);
        switch (expressao[indice + 1]){
            case '+':
                return primeiro_termo + segundo_termo;
            case '-':
                return primeiro_termo - segundo_termo;
            case '*':
                return primeiro_termo * segundo_termo;
            case '/':
                return primeiro_termo / segundo_termo;
        }
    }
    if (isdigit(expressao[indice]) != 0){
        return isdigit(expressao[indice]);
    }
    return 1; 
}

int main(){

    //lendo os dados de entrada
    char **expressao = NULL;
    int qtd_expressoes = 0;
    char c;
    bool lendo = true;
    while (lendo){
        c = fgetc(stdin);
        if (c == EOF){
            lendo = false;
        }
        else{
            ungetc(c, stdin);
            expressao = realloc(expressao, (qtd_expressoes + 1) * sizeof(char *));
            expressao[qtd_expressoes] = read_line(stdin);
            qtd_expressoes++;
        }
    }
    
    //calculando os valores das expressoes e printando os resultados
    double *resultado = malloc(qtd_expressoes * sizeof(double));
    for (int i = 0; i < qtd_expressoes; i++){
        resultado[i] = calcula_expressao(expressao[i], 0);
        printf("%.6lf\n", resultado[i]);
    }

    //desalocando a memoria
    for (int i = 0; i < qtd_expressoes; i++){
        free(expressao[i]);
    }
    free(expressao);
    free(resultado);

    return 0;
}