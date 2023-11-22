#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct REGISTRO{
    int identificador;
    char nome[50];
    char curso[50];
    int idade;
};

int main(){

    struct REGISTRO *aluno = NULL;
    int qtd_alunos = 0;

    //cadastrando os alunos
    bool cadastrando = true;
    while (cadastrando){
        int verificacao;
        scanf(" %d", &verificacao);
        if (verificacao == -1){
            cadastrando = false;
        }
        else{
            aluno = realloc(aluno, (qtd_alunos + 1) * sizeof(struct REGISTRO));
            aluno[qtd_alunos].identificador = verificacao;
            scanf(" %[^\n]", aluno[qtd_alunos].nome);
            scanf(" %[^\n]", aluno[qtd_alunos].curso);
            scanf(" %d", &aluno[qtd_alunos].idade);
            qtd_alunos++;
        }
    }

    //realizando as operacoes
    bool operando = true;
    while (operando){
        int verificacao;
        scanf(" %d", &verificacao);
        int id;
        char curso[50];
        if (verificacao == -1){
            operando = false;
        }
        else{
            int operacao = verificacao;
            switch (operacao){
                case 1: //imprimir o registro do aluno
                    scanf(" %d", &id);
                    for (int i = 0; i < qtd_alunos; i++){
                        if (aluno[i].identificador == id){
                            printf("Nome: %s\n", aluno[i].nome);
                            printf("Curso: %s\n", aluno[i].curso);
                            printf("N USP: %d\n", aluno[i].identificador);
                            printf("IDADE: %d\n\n", aluno[i].idade);
                        }
                    }
                    break;
                case 2: //imprimir o registro dos alunos do curso
                    scanf(" %[^\n]", curso);
                    for (int i = 0; i < qtd_alunos; i++){
                        if (strcmp(aluno[i].curso, curso) == 0){
                            printf("Nome: %s\n", aluno[i].nome);
                            printf("Curso: %s\n", aluno[i].curso);
                            printf("N USP: %d\n", aluno[i].identificador);
                            printf("IDADE: %d\n\n", aluno[i].idade);
                        }
                    }
                    break;
                case 3: //imprimir todos os registros
                    for (int i = 0; i < qtd_alunos; i++){
                        printf("Nome: %s\n", aluno[i].nome);
                        printf("Curso: %s\n", aluno[i].curso);
                        printf("N USP: %d\n", aluno[i].identificador);
                        printf("IDADE: %d\n\n", aluno[i].idade);
                    }
                    break;
            }
        }
    }

    //desalocando a memoria
    free(aluno);


    return 0;
}