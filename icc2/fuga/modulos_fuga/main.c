#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "fuga.h"

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
