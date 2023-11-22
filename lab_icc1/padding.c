#include <stdio.h>
#include <stdlib.h>

int main(){

    //declarando as variaveis e recebendo os valores de entrada
    int largura, altura;
    scanf (" %d %d", &largura, &altura);
    int **imagem = malloc (altura * sizeof (int *));
    for (int i = 0; i < altura; i++){
        *(imagem + i) = malloc (largura * sizeof (int));
        for (int j = 0; j < largura; j++){
            scanf (" %d", &imagem[i][j]);
        }
    }
    int tam_borda;
    scanf (" %d", &tam_borda);

    //criando uma nova matriz para adicionar as bordas:
    //precisamos adicionar '2 * tam_borda' linhas porque tem borda em cima e embaixo
    //mesma logica para as colunas, mas na esquerda e na direita
    int altura_com_borda = (2 * tam_borda + altura);
    int largura_com_borda = (2 * tam_borda + largura);
    int **padding = malloc (altura_com_borda * sizeof (int *));
    for (int i = 0; i < altura_com_borda; i++){
        *(padding + i) = malloc (largura_com_borda * sizeof (int));
    }

    //preenchendo a nova matriz
    for (int i = 0; i < altura_com_borda; i++){
        for (int j = 0; j < largura_com_borda; j++){
            if (i < tam_borda || i > (tam_borda + altura - 1) || 
                j < tam_borda || j > (tam_borda + largura - 1)){
                    padding[i][j] = 0;
            }
            else {
                padding[i][j] = imagem[i - tam_borda][j-tam_borda];
            }
        }
    }

    //printando a imagem com padding
    for (int i = 0; i < altura_com_borda; i++){
        for (int j = 0; j < largura_com_borda; j++){
            printf ("%d ", padding[i][j]);
        }
        printf ("\n");
    }

    printf("\n");

    //printando a imagem sem padding
    for (int i = 0; i < altura; i++){
        for (int j = 0; j < largura; j++){
            printf ("%d ", imagem[i][j]);
        }
        printf ("\n");
    }

    //desalocando a memoria
    for (int i = 0; i < altura_com_borda; i++){
        free (padding[i]);
    }
    free (padding);
    for (int i = 0; i < altura; i++){
        free (imagem[i]);
    }
    free (imagem);

    return 0;
}