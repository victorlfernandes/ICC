#include <stdio.h>
#include <stdlib.h>

int main(){

    int qtd_tipos;
    scanf(" %d", &qtd_tipos);
    float **matriz = malloc(qtd_tipos * sizeof(float *));
    for (int i = 0; i < qtd_tipos; i++){
        *(matriz + i) = malloc(qtd_tipos * sizeof(float));
        for (int j = 0; j < qtd_tipos; j++){
            scanf(" %f", &matriz[i][j]);
        }
    }

    int *poder_ataque = malloc(qtd_tipos * sizeof(int));
    int *indice_ataque = malloc(qtd_tipos * sizeof(int));
    for (int i = 0; i < qtd_tipos; i++){
        scanf(" %d", &poder_ataque[i]);
        scanf(" %d", &indice_ataque[i]);
    }
    int recebe_menos1;
    scanf(" %d", &recebe_menos1);

    int inimigo;
    scanf(" %d", &inimigo);

    float melhor_ataque = 0;
    int i_melhor_ataque = 0;
    for (int i = 0; i < qtd_tipos; i++){
        if ((poder_ataque[i] * matriz[i][inimigo]) > melhor_ataque){
            melhor_ataque = (poder_ataque[i] * matriz[i][inimigo]);
            i_melhor_ataque = i;
        } 
    }

    printf("O melhor ataque possui indice %d e dano %.2f\n", i_melhor_ataque, melhor_ataque);

    //desalocando a memoria
    for (int i = 0; i < qtd_tipos; i++){
        free(matriz[i]);
    }
    free(matriz);
    free(poder_ataque);

    return 0;
}