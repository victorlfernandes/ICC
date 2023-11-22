#include <stdio.h>

void calcula_troco(int troco, int *real, int *cinq, int *vint5, int *dez, int *cinco, int *cent){
    
    if ((troco / 100) > 0){
        *real = (troco / 100);
        troco = troco % 100;
    }
    if ((troco / 50) > 0){
        *cinq = (troco / 50);
        troco = troco % 50;
    }
    if ((troco / 25) > 0){
        *vint5 = (troco / 25);
        troco = troco % 25;
    }
    if ((troco / 10) > 0){
        *dez = (troco / 10);
        troco = troco % 10;
    }
    if ((troco / 5) > 0){
        *cinco = (troco / 5);
        troco = troco % 5;
    }
    if (troco > 0){
        *cent = troco;
    }
}

int main(){

    int troco;
    scanf(" %d", &troco);

    int real = 0; 
    int cinq = 0;
    int vint5 = 0;
    int dez = 0;
    int cinco = 0;
    int cent = 0;

    calcula_troco(troco, &real, &cinq, &vint5, &dez, &cinco, &cent);
    
    printf("O valor consiste em %d moedas de 1 real\n", real);
    printf("O valor consiste em %d moedas de 50 centavos\n", cinq);
    printf("O valor consiste em %d moedas de 25 centavos\n", vint5);
    printf("O valor consiste em %d moedas de 10 centavos\n", dez);
    printf("O valor consiste em %d moedas de 5 centavos\n", cinco);
    printf("O valor consiste em %d moedas de 1 centavo\n", cent);

    return 0;
}