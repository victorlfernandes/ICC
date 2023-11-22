#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    //lendo a palavra tabu e calculando seu tamanho
    char tabu[20];
    scanf(" %s\n", tabu);
    int tam_tabu = strlen(tabu);

    //lendo a frase e verificando a presenca do tabu
    char c;
    char *frase = NULL;
    int tam_frase = 0; 
    int qtd_chars_comuns = 0; 
    int indice_tabu = 0; 
    int qtd_tabu = 0;
    while ((c = getchar()) != '$'){
        frase = realloc(frase, tam_frase + 1);
        frase[tam_frase] = c;
        //verifica se o caracter pertence a palavra tabu
        if (frase[tam_frase] == tabu[indice_tabu]){
            qtd_chars_comuns++;
            indice_tabu++;
            //verifica se a contagem dos caracteres em comum e igual ao tamanho do tabu
            if (qtd_chars_comuns == tam_tabu){
                //tirando o tabu da frase
                frase = realloc(frase, (tam_frase - tam_tabu));
                //modificando os contadores
                qtd_tabu++;
                qtd_chars_comuns = 0;
                indice_tabu = 0;
                tam_frase = (tam_frase - tam_tabu);
            }
        }
        else{
            qtd_chars_comuns = 0;
            indice_tabu = 0;
        }
        tam_frase++;
    }

    //adicionando o \0 para printar a frase
    frase[tam_frase] = '\0';

    //printando o resultado
    printf("A palavra tabu foi encontrada %d vezes\n", qtd_tabu);
    printf("Frase: %s\n", frase);

    //desalocando a memoria
    free(frase);

    return 0;
}