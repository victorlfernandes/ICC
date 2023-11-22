#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    //lendo os nomes
    char **nome = NULL;
    char c;
    int qtd_nomes = 0;
    int qtd_caracteres = 0;
    while ((c = getchar()) != '$'){
        nome = realloc(nome, (qtd_nomes + 1) * sizeof(char *));
        if (c != '\n'){
            nome[qtd_nomes] = realloc(nome[qtd_nomes], qtd_caracteres + 1);
            nome[qtd_nomes][qtd_caracteres] = c;
            qtd_caracteres++;
        }
        else{
            nome[qtd_nomes][qtd_caracteres]  = '\0';
            qtd_nomes++;
            qtd_caracteres = 0;
        }
    }
    //precisamos fazer esse incremento para contar o ultimo nome
    qtd_nomes++;

    //adicionando os sobrenomes:
    //precisamos saber se a quantidade de nomes e par ou impar para saber a qtd de iteracoes
    int par_ou_impar;
    if ((qtd_nomes % 2) == 0){
        par_ou_impar = 1;
    }
    else{
        par_ou_impar = 2;
    }
    for (int i = 0; i < qtd_nomes - par_ou_impar; i += 2){
        //criando uma variavel auxiliar com o nome do indice par
        char nome_auxiliar[strlen(nome[i])];
        for (int j = 0; j < strlen(nome[i]); j++){
            nome_auxiliar[j] = nome[i][j];
        }
        nome_auxiliar[strlen(nome[i])] = '\0';
        //criando uma variavel auxiliar que vai recebendo todos os sobrenomes
        char *sobrenome_auxiliar = strtok(nome_auxiliar, " ");
        char *sobrenome;
        while (sobrenome_auxiliar != NULL){
            sobrenome = sobrenome_auxiliar;
            sobrenome_auxiliar = strtok(NULL, " "); 
        }
        //passando o ultimo sobrenome do nome de indice par para o proximo nome
        nome[i+1] = realloc(nome[i+1], (strlen(nome[i+1]) + strlen(sobrenome) + 1));
        strcat(nome[i+1], " ");
        strcat(nome[i+1], sobrenome);
    }

    //printando os nomes
    for (int i = 0; i < qtd_nomes; i++){
        printf("%s\n", nome[i]);
    }

    //desalocando a memoria
    for (int i = 0; i < qtd_nomes; i++){
        free(nome[i]);
    }
    free(nome);

    return 0;
}