#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "fuga.h"

char *le_string(FILE *stream){
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

void processa_labirinto(
    char **matriz,
    int i,
    int j,
    int qtd_linhas,
    int qtd_colunas,
    bool *saida)
{
    //chegou ao final
    if ((i == 0 || j == 0 || i == (qtd_linhas - 1) || j == (qtd_colunas - 1)) 
        && (matriz[i][j] == N_PERCORRIDO))
    {
        matriz[i][j] = PERCORRIDO;
        *saida = true;
        return; 
    }
    
    //bloqueado por pessoa
    if (matriz[i][j] == PESSOA){
        return; 
    }

    //passo recursivo
    if (matriz[i][j] == N_PERCORRIDO){
        matriz[i][j] = PERCORRIDO;
        //cima
        if (*saida == false){
            processa_labirinto(matriz, i - 1, j, qtd_linhas, qtd_colunas, saida);
        }
        //direita
        if (*saida == false){
            processa_labirinto(matriz, i, j + 1, qtd_linhas, qtd_colunas, saida);
        }
        //baixo
        if (*saida == false){
            processa_labirinto(matriz, i + 1, j, qtd_linhas, qtd_colunas, saida);
        }
        //esquerda
        if (*saida == false){
            processa_labirinto(matriz, i, j - 1, qtd_linhas, qtd_colunas, saida);
        }
    }
}

void detalhes_fuga(
    char **matriz,
    int qtd_linhas,
    int qtd_colunas,
    int *validos,
    int *pessoas,
    int *visitados,
    char checagem)
{
    for (int i = 0; i < qtd_linhas; i++){
        for (int j = 0; j < qtd_colunas; j++){
            if (matriz[i][j] == N_PERCORRIDO && checagem == N_PERCORRIDO){
                (*validos)++;
            }
            else if (matriz[i][j] == PESSOA && checagem == PESSOA){
                (*pessoas)++;
            }
            else if (matriz[i][j] == PERCORRIDO && checagem == PERCORRIDO){
                (*visitados)++;
            }
        }
    }
}

void imprime_matriz(
    FILE *stream,
    char **matriz, 
    int qtd_linhas, 
    int qtd_colunas) 
{
    for (int i = 0; i < qtd_linhas; i++){
        for (int j = 0; j < qtd_colunas; j++){
            fprintf(stream, "%c", matriz[i][j]);
        }
        if (i != (qtd_linhas - 1)){
            fprintf(stream, "\n");
        }
    }
}