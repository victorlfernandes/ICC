#include <stdio.h>
#include <stdlib.h>

int main(){

    //lendo o codigo em brainfuck
    char c;
    char *brainfuck = NULL;
    int qtd_operacoes = 0;
    while ((c = getchar()) != EOF){
        brainfuck = realloc(brainfuck, qtd_operacoes + 1);
        brainfuck[qtd_operacoes] = c;
        qtd_operacoes++;
    }

    //abrindo o arquivo .c
    FILE *arquivo = fopen("jit.c", "w");

    //escrevendo o inicio do codigo
    fprintf(arquivo, "#include <stdio.h>\n\n");
    fprintf(arquivo, "int main(){\n");
    fprintf(arquivo, "\tchar mem[30000];\n");
    fprintf(arquivo, "\tint i = 0;\n\n");
    fprintf(arquivo, "\tfor (int j = 0; j < 30000; j++)\n");
    fprintf(arquivo, "\t\tmem[j] = 0;\n\n");

    //escrevendo a traducao do brainfuck
    for (int i = 0; i < qtd_operacoes; i++){
        switch (brainfuck[i]){
            case '+':
                fprintf(arquivo, "\tmem[i]++;\n");
                break;
            case '-':
                fprintf(arquivo, "\tmem[i]--;\n");
                break;
            case '>':
                fprintf(arquivo, "\ti++;\n");
                break;
            case '<':
                fprintf(arquivo, "\ti--;\n");
                break;
            case '.':
                fprintf(arquivo, "\tputchar(mem[i]);\n");
                break;
            case '[':
                fprintf(arquivo, "\twhile(mem[i]) {\n");
                break;
            case ']':
                fprintf(arquivo, "}\n");
                break;
        }
    }

    //escrevendo o final do codigo
    fprintf(arquivo, "\n\tprintf(\"\\n\");\n");
    fprintf(arquivo, "\tfor (int j = 0; j < 30000; j++){\n");
    fprintf(arquivo, "\t\tif (mem[j] != 0)\n");
    fprintf(arquivo, "\t\t\tprintf(\"%%d \", mem[j]);\n");
    fprintf(arquivo, "\t}\n");
    fprintf(arquivo, "\tprintf(\"\\n\");\n\n");
    fprintf(arquivo, "\treturn 0;\n");
    fprintf(arquivo, "}");

    //fechando o arquivo
    fclose(arquivo);

    //compilando o arquivo
    system("gcc jit.c -o jit");

    //rodando o executavel
    system("./jit");

    //deslocando a memoria
    free(brainfuck);

    return 0;
}