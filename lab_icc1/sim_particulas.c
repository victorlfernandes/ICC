#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define AREIA '#'
#define AGUA '~'
#define CIMENTO '@'
#define AR ' '

//32 linhas de partículas + 2 de borda
#define LINHAS 34
//64 colunas de partículas + 2 de borda
#define COLUNAS 66

char matriz[LINHAS][COLUNAS];

/* msleep(): Sleep for the requested number of milliseconds. */
void msleep(long msec){
    struct timespec ts;

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    nanosleep(&ts, &ts);
}

void imprime_frame(){
    for (int i=0; i<LINHAS; i++){
        for (int j=0; j<COLUNAS; j++){
            if (matriz[i][j] == AREIA){
                printf("\033[93m%c", matriz[i][j]);
            }
            else if (matriz[i][j] == AGUA){
                printf("\033[96m%c", matriz[i][j]);
            }
            else if (matriz[i][j] == CIMENTO){
                printf("\033[90m%c", matriz[i][j]);
            }
            else if (matriz[i][j] == AR){
                printf("\033[97m%c", matriz[i][j]);
            }
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

    system("clear");

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
            printf("\033[35A");
            msleep(50);
            fisica();
            contador++;
        }

        // Se há uma particula a ser criada, crie ela.
        if (n_lido != EOF) {
            //precisamos adicionar 1 em cada coordenada por causa das bordas
            matriz[y+1][x+1] = nova_particula;
        }
    }

    system("clear");
    return 0;
}