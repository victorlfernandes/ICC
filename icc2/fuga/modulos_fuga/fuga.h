#define PESSOA '#'
#define PERCORRIDO '*'
#define N_PERCORRIDO '.'

char *le_string(FILE *stream);

void processa_labirinto(
    char **matriz,
    int i,
    int j,
    int qtd_linhas,
    int qtd_colunas,
    bool *saida);

void detalhes_fuga(
    char **matriz,
    int qtd_linhas,
    int qtd_colunas,
    int *validos,
    int *pessoas,
    int *visitados,
    char checagem);

void imprime_matriz(
    FILE *stream,
    char **matriz, 
    int qtd_linhas, 
    int qtd_colunas);