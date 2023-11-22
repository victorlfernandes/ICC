#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void calcula_geracoes(char **matriz, int linhas, int colunas, char tipo_vizinhanca);
void vizinhos_moore(char **matriz, int i, int j, int linhas, int colunas, char vizinhos[8]);
void vizinhos_von_neumann(char **matriz, int i, int j, int linhas, int colunas, char vizinhos[8]);

/* msleep(): Sleep for the requested number of milliseconds. */
void msleep(long msec){
    struct timespec ts;

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    nanosleep(&ts, &ts);
}

int main(){

    system("clear");

    //lendo os dados de entrada
    int linhas, colunas;
    scanf(" %d %d", &linhas, &colunas);
    int n_geracoes;
    scanf(" %d", &n_geracoes);
    char tipo_vizinhanca;
    scanf(" %c", &tipo_vizinhanca);
    getchar(); //ignorando o \n deixado pelo scanf
    char **matriz = malloc(linhas * sizeof(char *));
    for (int i=0; i<linhas; i++){
        *(matriz + i) = malloc((colunas+1) * sizeof(char));
    }
    for (int i=0; i<linhas; i++){
        for (int j=0; j<colunas+1; j++){
            matriz[i][j] = getchar();
        }
    }

    //verificando os dados
    if (linhas <= 0 || colunas <= 0 || n_geracoes <= 0 || 
       (tipo_vizinhanca != 'M' && tipo_vizinhanca != 'N') 
       || matriz == NULL){
        printf("Dados de entrada apresentam erro.\n");
        exit(1);
    }

    //processando as geracoes
    for (int i=0; i<n_geracoes; i++){
        for (int i=0; i<linhas; i++){
            for (int j=0; j<colunas+1; j++){
                printf("\033[96m%c", matriz[i][j]);
            }
        }
        msleep(500);
        calcula_geracoes(matriz, linhas, colunas, tipo_vizinhanca); 
        printf("\033[24A");
    }

    //desalocando a memoria
    for (int i=0; i<linhas; i++){
        free(matriz[i]);
    }
    free(matriz);

    system("clear");

    return 0;
}

void calcula_geracoes(char **matriz, int linhas, int colunas, char tipo_vizinhanca){

    //copiando os valores de 'matriz' para 'aux', uma matriz auxiliar
    char **aux = malloc(linhas * sizeof(char *));
    for (int i=0; i<linhas; i++){
        *(aux + i) = malloc((colunas+1) * sizeof(char));
        for (int j=0; j<colunas; j++){
            aux[i][j] = matriz[i][j];
        }
    }

    //iterando por todos os elementos de 'matriz' 
    //e fazendo as mudancas necessarias na matriz 'aux'
    for (int i=0; i<linhas; i++){
        for (int j=0; j<colunas; j++){
            char vizinhos[8];
            if (tipo_vizinhanca == 'M'){
                vizinhos_moore(matriz, i, j, linhas, colunas, vizinhos);    
            }
            else{
                vizinhos_von_neumann(matriz, i, j, linhas, colunas, vizinhos);
            }

            int n_vizinhos_vivos = 0;
            for (int i=0; i<8; i++){
                if (vizinhos[i] == 'x'){
                    n_vizinhos_vivos++;
                }
            }
            if ((matriz[i][j] == 'x') && (n_vizinhos_vivos < 2 || n_vizinhos_vivos > 3)){
                aux[i][j] = '.';
            }
            else if (matriz[i][j] == '.' && n_vizinhos_vivos == 3){
                aux[i][j] = 'x';
            }
        }
    }

    //retornando os valores de 'aux' para 'matriz'
    for (int i=0; i<linhas; i++){
        for (int j=0; j<colunas; j++){
            matriz[i][j] = aux[i][j];
        }
    }

    //desalocando 'aux'
    for (int i=0; i<linhas; i++){
        free(aux[i]);
    }
    free(aux);
}

void vizinhos_moore(char **matriz, int i, int j, int linhas, int colunas, char vizinhos[8]){
    
    //verificando se as linhas estao na borda
    //e determinando a linha de cada vizinho
    int linha_cima, linha_baixo;
    if (i == 0){
        linha_cima = linhas-1; 
        linha_baixo = i+1;
    }
    else if (i == linhas-1){
        linha_cima = i-1;
        linha_baixo = 0;
    }
    else{
        linha_cima = i-1;
        linha_baixo = i+1;
    }

    //verificando se as colunas estao na borda
    //e determinando a coluna de cada vizinho
    int coluna_esquerda, coluna_direita;
    if (j == 0){
        coluna_esquerda = colunas-1; 
        coluna_direita = j+1;
    }
    else if (j == colunas-1){
        coluna_esquerda = j-1;
        coluna_direita = 0;
    }
    else{
        coluna_esquerda = j-1;
        coluna_direita = j+1;
    }
    
    vizinhos[0] = matriz[linha_cima][coluna_esquerda];
    vizinhos[1] = matriz[linha_cima][j];
    vizinhos[2] = matriz[linha_cima][coluna_direita];
    vizinhos[3] = matriz[i][coluna_esquerda];
    vizinhos[4] = matriz[i][coluna_direita];
    vizinhos[5] = matriz[linha_baixo][coluna_esquerda];
    vizinhos[6] = matriz[linha_baixo][j];
    vizinhos[7] = matriz[linha_baixo][coluna_direita];
}

void vizinhos_von_neumann(char **matriz, int i, int j, int linhas, int colunas, char vizinhos[8]){
  
    //verificando se as linhas estao na borda
    //e determinando a linha de cada vizinho
    int linha_cima, linha_2cima, linha_baixo, linha_2baixo;
    if (i == 0){
        linha_cima = linhas-1;
        linha_2cima = linhas-2;
        linha_baixo = i+1;
        linha_2baixo = i+2;
    }
    else if (i == 1){
        linha_cima = i-1;
        linha_2cima = linhas-1;
        linha_baixo = i+1;
        linha_2baixo = i+2; 
    }
    else if (i == linhas-1){
        linha_cima = i-1;
        linha_2cima = i-2;
        linha_baixo = 0;
        linha_2baixo = 1;
    }
    else if (i == linhas-2){
        linha_cima = i-1;
        linha_2cima = i-2;
        linha_baixo = i+1;
        linha_2baixo = 0;
    }
    else{
        linha_cima = i-1;
        linha_2cima = i-2;
        linha_baixo = i+1;
        linha_2baixo = i+2;
    }

    //verificando se as colunas estao na borda
    //e determinando a coluna de cada vizinho
    int coluna_esquerda, coluna_2esquerda, coluna_direita, coluna_2direita;
    if (j == 0){
        coluna_esquerda = colunas-1;
        coluna_2esquerda = colunas-2;
        coluna_direita = j+1;
        coluna_2direita = j+2;
    }
    else if (j == 1){
        coluna_esquerda = j-1;
        coluna_2esquerda = colunas-1;
        coluna_direita = j+1;
        coluna_2direita = j+2; 
    }
    else if (j == colunas-1){
        coluna_esquerda = j-1;
        coluna_2esquerda = j-2;
        coluna_direita = 0;
        coluna_2direita = 1;
    }
    else if (j == colunas-2){
        coluna_esquerda = j-1;
        coluna_2esquerda = j-2;
        coluna_direita = j+1;
        coluna_2direita = 0;
    }
    else{
        coluna_esquerda = j-1;
        coluna_2esquerda = j-2;
        coluna_direita = j+1;
        coluna_2direita = j+2;
    }
    
    vizinhos[0] = matriz[linha_2cima][j];
    vizinhos[1] = matriz[linha_cima][j];
    vizinhos[2] = matriz[i][coluna_2esquerda];
    vizinhos[3] = matriz[i][coluna_esquerda];
    vizinhos[4] = matriz[i][coluna_direita];
    vizinhos[5] = matriz[i][coluna_2direita];
    vizinhos[6] = matriz[linha_baixo][j];
    vizinhos[7] = matriz[linha_2baixo][j];
}