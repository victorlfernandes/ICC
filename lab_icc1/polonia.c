#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

double *pilha = NULL;
int topo = 0;

//coloca o digito recebido no topo da pilha
void empilha(double digito);
//desempilha o valor do topo e retorna ele
double desempilha();

int main(){

    //recebendo os dados de entrada
    char caractere;
    while ((caractere = getchar()) != EOF){
        if (caractere == ' '){
            continue;
        }
        else if (isdigit(caractere) != 0){
            ungetc(caractere, stdin);
            double digito;
            scanf(" %lf", &digito);
            empilha(digito);
        }
        else{ //se for um operador
            double segundo_termo = desempilha();
            double primeiro_termo = desempilha();
            switch (caractere){
                case '+':
                    empilha(primeiro_termo + segundo_termo);
                    break;
                case '-':
                    empilha(primeiro_termo - segundo_termo);
                    break;
                case '*':
                    empilha(primeiro_termo * segundo_termo);
                    break;
                case '/':
                    empilha(primeiro_termo / segundo_termo);
                    break;
            }
        }
    }

    //desempilhando e printando o resultado
    double resultado = desempilha();
    printf("Resultado: %.6lf\n", resultado);
    
    //desalocando a memoria
    free(pilha);

    return 0;
}

void empilha(double digito){
    pilha = realloc(pilha, (topo + 1) * sizeof(double));
    pilha[topo] = digito;
    topo++;
}

double desempilha(){
    double auxiliar = pilha[topo - 1];
    topo--;
    pilha = realloc(pilha, topo * sizeof(double));
    return auxiliar;
}