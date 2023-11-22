#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PESSOA '#'
#define PERCORRIDO '*'
#define N_PERCORRIDO '.'

char *le_string(FILE *stream);

void processa_labirinto(
    char **matriz,
    int i,
    int j,
    int qtd_linhas,
    int qtd_colunas,
    bool *saida);

void detalhes_fuga(
    char **matriz,
    int qtd_linhas,
    int qtd_colunas,
    int *validos,
    int *pessoas,
    int *visitados,
    char checagem);

void imprime_matriz(
    FILE *stream,
    char **matriz, 
    int qtd_linhas, 
    int qtd_colunas);

int main() {

    //lendo o nome do arquivo
    char *nome_arquivo = le_string(stdin);
    
    //lendo os dados do arquivo
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo){
        printf("Arquivo inexistente\n");
        free(nome_arquivo);
        exit(1);
    }
    int qtd_linhas;
    int qtd_colunas;
    fscanf(arquivo, " %d", &qtd_linhas);
    fscanf(arquivo, " %d", &qtd_colunas);
    int i_inicial;
    int j_inicial;
    fscanf(arquivo, " %d", &i_inicial);
    fscanf(arquivo, " %d", &j_inicial);
    fgetc(arquivo); //consumindo o \n
    char **matriz = malloc(qtd_linhas * sizeof(char *));
    for (int i = 0; i < qtd_linhas; i++){
        matriz[i] = malloc((qtd_colunas + 1) * sizeof(char));
        for (int j = 0; j <= qtd_colunas; j++){
            matriz[i][j] = fgetc(arquivo);
        }
    }
    fclose(arquivo);

    //contando a quantidade de caminhos validos
    int validos = 0;
    detalhes_fuga(matriz, qtd_linhas, qtd_colunas, &validos, NULL, NULL, N_PERCORRIDO);

    //percorrendo o labirinto ate a saida
    bool saida = false;
    processa_labirinto(matriz, i_inicial, j_inicial, qtd_linhas, qtd_colunas, &saida);

    //contando a quantidade de pessoas e de caminhos visitados
    int qtd_pessoas = 0;
    detalhes_fuga(matriz, qtd_linhas, qtd_colunas, NULL, &qtd_pessoas, NULL, PESSOA);
    int visitados = 0;
    detalhes_fuga(matriz, qtd_linhas, qtd_colunas, NULL, NULL, &visitados, PERCORRIDO);

    //imprimindo o estado final do labirinto
    imprime_matriz(stdout, matriz, qtd_linhas, qtd_colunas);

    //imprimindo os detalhes da fuga
    printf("\n\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
    printf("Veja abaixo os detalhes da sua fuga:\n");
    printf("----Pessoas te procurando: %d\n", qtd_pessoas);
    printf("----Numero total de caminhos validos:   %d\n", validos);
    printf("----Numero total de caminhos visitados: %d\n", visitados);
    printf("----Exploracao total do labirinto: %.1lf%%\n", (double)(visitados * 100 / validos));

    //desalocando a memoria
    free(nome_arquivo);
    for (int i = 0; i < qtd_linhas; i++){
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}

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