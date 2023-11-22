#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//le caracteres de 'stream' ate encontrar um \n ou EOF
char *read_line(FILE *stream);

//realiza o preenchimento dos pixels de forma recursiva
void preenche(
    char **matriz, 
    char cor, 
    char cor_a_ser_preenchida, 
    int i, 
    int j,
    int qtd_linhas,
    int qtd_colunas);

//imprime a matriz da arte em 'stream'
void imprime_arte(
    FILE *stream,
    char **matriz, 
    int qtd_linhas, 
    int qtd_colunas);

//faz o enquadramento da arte
void enquadra_arte(
	char *nome_do_arquivo_da_arte,
	int  altura_do_quadro,
	int  largura_do_quadro);

int main(){

    //lendo os dados de entrada
    char *nome_arquivo = read_line(stdin);
    int qtd_preenchimentos;
    scanf(" %d", &qtd_preenchimentos);
    char *cor       = malloc (qtd_preenchimentos * sizeof(char));
    int  *i_inicial = malloc (qtd_preenchimentos * sizeof(int ));
    int  *j_inicial = malloc (qtd_preenchimentos * sizeof(int ));
    for (int i = 0; i < qtd_preenchimentos; i++){
        scanf(" %c", &cor[i]      );
        scanf(" %d", &i_inicial[i]);
        scanf(" %d", &j_inicial[i]);
    }

    //carregando a arte do arquivo em uma matriz
    FILE *arquivo_leitura = fopen(nome_arquivo, "r");
    char **matriz = NULL;
    int qtd_linhas = 0;
    char c;
    bool lendo = true;
    while (lendo){
        c = fgetc(arquivo_leitura);
        if (c == EOF){
            lendo = false;
        }
        else{
            ungetc(c, arquivo_leitura);
            matriz = realloc(matriz, (qtd_linhas + 1) * sizeof (char *));
            matriz[qtd_linhas] = read_line(arquivo_leitura);
            qtd_linhas++;
        }
    }
    int qtd_colunas = (strlen(matriz[0]));
    fclose(arquivo_leitura);

    //printando a arte inicial
    printf("Arte inicial:\n");
    imprime_arte(stdout, matriz, qtd_linhas, qtd_colunas);

    //preenchendo a matriz
    for (int i = 0; i < qtd_preenchimentos; i++){
        char cor_a_ser_preenchida = matriz[i_inicial[i]][j_inicial[i]];
        preenche(matriz, cor[i], cor_a_ser_preenchida, i_inicial[i], 
                 j_inicial[i], qtd_linhas, qtd_colunas);
        printf("\n\nArte apos a etapa %d:\n", i);
        imprime_arte(stdout, matriz, qtd_linhas, qtd_colunas);
    }

    //escrevendo a matriz final no arquivo
    FILE *arquivo_escrita = fopen(nome_arquivo, "w");
    imprime_arte(arquivo_escrita, matriz, qtd_linhas, qtd_colunas);
    fclose(arquivo_escrita);

    //enquadrando a arte
    printf("\n\nArte enquadrada:\n");
    enquadra_arte(nome_arquivo, qtd_linhas, qtd_colunas);

    //desalocando a memoria
    free(nome_arquivo);
    free(cor);
    free(i_inicial);
    free(j_inicial);
    for (int i = 0; i < qtd_linhas; i++){
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}

char *read_line(FILE *stream){
    char c;
    int n_chars = 0;
    char *line = NULL;
    while ((c = fgetc(stream)) != '\n' && c != EOF){
        line = realloc (line, (n_chars + 1));
        line[n_chars] = c;
        n_chars++; 
    }
    line = realloc (line, (n_chars + 1));
    line[n_chars] = '\0';
    return line;
}   

void preenche(
    char **matriz, 
    char cor, 
    char cor_a_ser_preenchida, 
    int i, 
    int j,
    int qtd_linhas,
    int qtd_colunas) 
{
    //para quando chega em um caractere que nao deve ser preenchido
    if (matriz[i][j] == cor_a_ser_preenchida){
        matriz[i][j] = cor;
        //chamando a funcao para o vizinho da direita
        if (j != (qtd_colunas - 1)){
            preenche(matriz, cor, cor_a_ser_preenchida, 
                     i, (j + 1), qtd_linhas, qtd_colunas);
        }
        //chamando a funcao para o vizinho da esquerda
        if (j != 0){
            preenche(matriz, cor, cor_a_ser_preenchida, 
                     i, (j - 1), qtd_linhas, qtd_colunas);
        }
        //chamando a funcao para o vizinho de cima
        if (i != 0){
            preenche(matriz, cor, cor_a_ser_preenchida, 
                    (i - 1), j, qtd_linhas, qtd_colunas);
        }
        //chamando a funcao para o vizinho de baixo
        if (i != (qtd_linhas - 1)){
            preenche(matriz, cor, cor_a_ser_preenchida, 
                    (i + 1), j, qtd_linhas, qtd_colunas);
        }
    } 
}

void imprime_arte(
    FILE *stream,
    char **matriz, 
    int qtd_linhas, 
    int qtd_colunas) 
{
    for (int i = 0; i < qtd_linhas; i++){
        for (int j = 0; j < qtd_colunas; j++){
            fprintf(stream, "%c", matriz[i][j]);
        }
        if (i != (qtd_linhas - 1)){
            fprintf(stream, "\n");
        }
    }
}

void enquadra_arte(
	char *nome_do_arquivo_da_arte,
	int  altura_do_quadro,
	int  largura_do_quadro)
 {
	FILE *f_arte_ptr = fopen(nome_do_arquivo_da_arte, "r");
	if (f_arte_ptr == NULL) {
		printf(
			"Erro na abertura do arquivo, "
			"Você esqueceu de fechar o arquivo antes? "
			"Ou deu free na string com o nome sem querer?\n"
		);

		exit(EXIT_FAILURE);
	}

	int qtd_espc_comeco;
	const char *apoio;
	if (largura_do_quadro % 2 == 0) {
		qtd_espc_comeco = largura_do_quadro / 2;
		apoio           = "/\\";
	} else {
		qtd_espc_comeco = largura_do_quadro / 2 + 1;
		apoio           = "Ʌ";
	}

	for (int i = 0; i < qtd_espc_comeco; i++) printf(" ");
	printf("%s\n", apoio);

	printf("╭");
	for (int i = 0; i < largura_do_quadro; i++) printf("—");
	printf("╮\n");

	for (int i = 0; i < altura_do_quadro; i++) {
		printf("|");
		for (int j = 0; j < largura_do_quadro; j++) {
			char pixel_atual = fgetc(f_arte_ptr);
			printf("%c", pixel_atual);
		}
		printf("|");

		char quebra = fgetc(f_arte_ptr);
		if (quebra != EOF) printf("%c", quebra);
	};
	fclose(f_arte_ptr);

	printf("\n╰");
	for (int i = 0; i < largura_do_quadro; i++) printf("—");
	printf("╯\n");
}