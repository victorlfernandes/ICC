#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int * le_vetor(
    int *qtd_numeros);

int * cria_vetor_sem_rep(
    int *vetor,
    int qtd_numeros,
    int *qtd_num_dif);

int * calcula_frequencia(
    int *vetor,
    int *vetor_sem_rep,
    int qtd_numeros,
    int qtd_num_dif);

int main() {

    //lendo o vetor com os numeros
    int qtd_numeros;
    int *vetor = le_vetor(&qtd_numeros);

    //criando um vetor sem numeros repetidos
    int qtd_num_dif;
    int *vetor_sem_rep = cria_vetor_sem_rep(vetor, qtd_numeros, &qtd_num_dif);

    //calculando a frequencia de cada numero
    int *frequencia = calcula_frequencia(vetor, vetor_sem_rep, qtd_numeros, qtd_num_dif);

    //exibindo o resultado
    for (int i = 0; i < qtd_num_dif; i++){
        printf("%d (%d)\n", vetor_sem_rep[i], frequencia[i]);
    }

    //desalocando a memoria
    free(vetor);
    free(vetor_sem_rep);
    free(frequencia);

    return 0;
}

int * le_vetor(int *qtd_numeros){
    int *vetor = malloc(sizeof(int));
    int contador = 0;
    bool lendo_vetor = true;
    while (lendo_vetor) {
        char c = getchar();
        if (c == EOF) {
            lendo_vetor = false;
        }
        else{
            ungetc(c, stdin);
            scanf(" %d", &vetor[contador]);
            contador++;
            vetor = realloc(vetor, (contador + 1) * sizeof(int));
        }
    }
    *qtd_numeros = contador;
    return vetor;
}

int * cria_vetor_sem_rep(
    int *vetor,
    int qtd_numeros,
    int *qtd_num_dif)
{
    int *vetor_sem_rep = malloc(sizeof(int));
    int contador = 0;
    for (int i = 0; i < qtd_numeros; i++){
        //determinando se o numero atual ja foi contabilizado
        int auxiliar = 0;
        for (int j = i; j >= 0; j--) {
            if (vetor[i] != vetor[j])
                auxiliar++;
        }
        if (auxiliar == i){ //numero ainda precisa ser contabilizado
            vetor_sem_rep = realloc(vetor_sem_rep, (contador + 1) * sizeof(int));
            vetor_sem_rep[contador] = vetor[i];
            contador++;
        }
    }
    *qtd_num_dif = contador;
    return vetor_sem_rep;
}

int * calcula_frequencia(
    int *vetor,
    int *vetor_sem_rep,
    int qtd_numeros,
    int qtd_num_dif)
{
    int *frequencia = malloc(qtd_num_dif * sizeof(int));
    for (int i = 0; i < qtd_num_dif; i++){
        for (int j = 0; j < qtd_numeros; j++){
            if (vetor_sem_rep[i] == vetor[j]){
                frequencia[i]++;
            }
        }
    }
    return frequencia;
}