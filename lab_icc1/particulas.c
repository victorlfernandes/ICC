#include <stdio.h>

#define AREIA '#'
#define AGUA '~'
#define CIMENTO '@'
#define AR ' '

//32 linhas de partículas + 2 de borda
#define LINHAS 34
//64 colunas de partículas + 2 de borda
#define COLUNAS 66

char matriz[LINHAS][COLUNAS];

void imprime_frame(){
    //o for comeca em 1 para nao imprimir as bordas
    //linhas-1 e colunas-1 pelo mesmo motivo
    for (int i=1; i<LINHAS-1; i++){
        for (int j=1; j<COLUNAS-1; j++){
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
}

void fisica(){

    //copiando o conteudo de 'matriz' para 'copia'
    char copia[LINHAS][COLUNAS];
    for (int i=0; i<LINHAS; i++){
        for (int j=0; j<COLUNAS; j++){
            copia[i][j] = matriz[i][j];
        }
    }

    //atualizando a matriz copia
    for (int i=0; i<LINHAS; i++){
        for (int j=0; j<COLUNAS; j++){
            switch (matriz[i][j]){
                case AREIA:
                    //verifica se pode mover para baixo
                    if (matriz[i+1][j] == AGUA || matriz[i+1][j] == AR){
                        char tmp = copia[i][j];
                        copia[i][j] = copia[i+1][j];
                        copia[i+1][j] = tmp;
                    }
                    //verifica se pode mover para a diagonal esquerda
                    else if (matriz[i+1][j-1] == AGUA || matriz[i+1][j-1] == AR){
                        char tmp = copia[i][j];
                        copia[i][j] = copia[i+1][j-1];
                        copia[i+1][j-1] = tmp;                        
                    }
                    //verifica se pode mover para a diagonal direita
                    else if (matriz[i+1][j+1] == AGUA || matriz[i+1][j+1] == AR){
                        char tmp = copia[i][j];
                        copia[i][j] = copia[i+1][j+1];
                        copia[i+1][j+1] = tmp;
                    }
                    break;
                case AGUA:
                    //verifica se pode mover para baixo
                    if (matriz[i+1][j] == AR){
                        char tmp = copia[i][j];
                        copia[i][j] = copia[i+1][j];
                        copia[i+1][j] = tmp;
                    }
                    //verifica se pode mover para a diagonal esquerda
                    else if (matriz[i+1][j-1] == AR){
                        char tmp = copia[i][j];
                        copia[i][j] = copia[i+1][j-1];
                        copia[i+1][j-1] = tmp;
                    }
                    //verifica se pode mover para a diagonal direita
                    else if (matriz[i+1][j+1] == AR){
                        char tmp = copia[i][j];
                        copia[i][j] = copia[i+1][j+1];
                        copia[i+1][j+1] = tmp;
                    }
                    //verifica se pode mover para a esquerda
                    else if (matriz[i][j-1] == AR){
                        char tmp = copia[i][j];
                        copia[i][j] = copia[i][j-1];
                        copia[i][j-1] = tmp;
                    }
                    //verifica se pode mover para a direita
                    else if (matriz[i][j+1] == AR){
                        char tmp = copia[i][j];
                        copia[i][j] = copia[i][j+1];
                        copia[i][j+1] = tmp;
                    }
                    break;
            }
        }
    }

    //copiando o conteudo de 'copia' para 'matriz'
    for (int i=0; i<LINHAS; i++){
        for (int j=0; j<COLUNAS; j++){
            matriz[i][j] = copia[i][j];
        }
    } 
}
 
int main(){

    //inicializando todas as partículas como AR
    //e as bordas como CIMENTO
    for (int i=0; i<LINHAS; i++){
        for (int j=0; j<COLUNAS; j++){
            if (i == 0 || j == 0 || i == LINHAS-1 || j == COLUNAS-1){
                matriz[i][j] = CIMENTO;
            }
            else{
                matriz[i][j] = AR;
            }
        }
    }

    int n_frames, frame, x, y;
    char nova_particula;

    scanf("%d", &n_frames);

    int contador = 0;
    while (contador < n_frames) {

        // `scanf` retorna EOF quando chega ao fim da entrada.
        int n_lido = scanf(" %d: %d %d %c", &frame, &x, &y, &nova_particula);

        // Se não há mais partículas a serem criadas, continue até o final
        // da simulação.
        if (n_lido == EOF) {
            frame = n_frames;
        }

        // Calcula todos os frames até o próximo frame onde queremos criar
        // uma partícula.
        while (contador < frame) {
            printf("frame: %d\n", contador + 1);
            imprime_frame();
            fisica();
            contador++;
        }

        // Se há uma particula a ser criada, crie ela.
        if (n_lido != EOF) {
            //precisamos adicionar 1 em cada coordenada por causa das bordas
            matriz[y+1][x+1] = nova_particula;
        }
    }

    return 0;
}