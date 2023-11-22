#include <stdio.h>
#include <math.h>

/* Função que calcula a distância percorrida por um dos irmãos 
quando ele anda pela calçada, ou seja, pelas laterais do quarteirão */
int lateral(int x1, int y1, int x2, int y2);

/* Função que calcula a distância percorrida por um dos irmãos 
quando ele anda pelo caminho mais curto, ou seja, a diagonal do quarteirão */
double diagonal(int x1, int y1, int x2, int y2);

int main(){
	
	int qtd_pontos;
	scanf(" %d", &qtd_pontos);
	if(qtd_pontos <= 0){
		printf("Falha no processamento dos dados.\n");
		return 0;
	}
	
	int x[qtd_pontos], y[qtd_pontos], i[qtd_pontos]; 
	int c;
	for(c=0; c<qtd_pontos; c++){
		scanf(" %d %d %d", &x[c], &y[c], &i[c]); 
	}
	
	int cont_bald = 0, cont_res = 0, cont_parq = 0;
	double distancia_hermann = 0, distancia_euclides = 0;
	for(c=0; c<qtd_pontos; c++){
		switch(i[c]){ 
			case -1: //baldio, os dois vão pela diagonal
				if(c != (qtd_pontos-1)){ //ida
					distancia_hermann += diagonal(x[c], y[c], x[c+1], y[c+1]);
					distancia_euclides += diagonal(x[c], y[c], x[c+1], y[c+1]);
				}
				else{ //volta
					distancia_hermann += diagonal(x[c], y[c], x[0], y[0]);
					distancia_euclides += diagonal(x[c], y[c], x[0], y[0]);	
				}
				cont_bald++;
				break;
			case 0: //residencial, os dois vão pelas laterais
				if(c != (qtd_pontos-1)){ //ida
					distancia_hermann += lateral(x[c], y[c], x[c+1], y[c+1]);
					distancia_euclides += lateral(x[c], y[c], x[c+1], y[c+1]);
				}
				else{ //volta
					distancia_hermann += lateral(x[c], y[c], x[0], y[0]);
					distancia_euclides += lateral(x[c], y[c], x[0], y[0]);
				}
				cont_res++;
				break;
			case 1: //parque, hermann vai pelas laterais e euclides pela diagonal
				if(c != (qtd_pontos-1)){ //ida
					distancia_hermann += lateral(x[c], y[c], x[c+1], y[c+1]);
					distancia_euclides += diagonal(x[c], y[c], x[c+1], y[c+1]);
				}
				else{ //volta
					distancia_hermann += lateral(x[c], y[c], x[0], y[0]);
					distancia_euclides += diagonal(x[c], y[c], x[0], y[0]);
				}
				cont_parq++;
				break;
			default:
				printf("Falha no processamento dos dados.\n");
				return 0;
		}
	}
	
	double diferenca = distancia_hermann - distancia_euclides;
	
	printf("Ao todo, foi passado por %d terrenos baldios, %d terrenos residenciais e %d parques.\n", cont_bald, cont_res, cont_parq);
	printf("A diferenca total de distancia percorrida foi de %.2lf metros.\n", diferenca);
		
	return 0;
}

int lateral(int x1, int y1, int x2, int y2){
	int d_horizontal = 0, d_vertical = 0;
	(x1 > x2) ? (d_horizontal = (x1 - x2)) : (d_horizontal = (x2 - x1));
	(y1 > y2) ? (d_vertical = (y1 - y2)) : (d_vertical = (y2 - y1));
	return d_horizontal + d_vertical;
}

double diagonal(int x1, int y1, int x2, int y2){
	int d_horizontal = 0, d_vertical = 0;
	(x1 > x2) ? (d_horizontal = (x1 - x2)) : (d_horizontal = (x2 - x1));
	(y1 > y2) ? (d_vertical = (y1 - y2)) : (d_vertical = (y2 - y1));
	return sqrt((pow(d_horizontal, 2)) + (pow(d_vertical, 2)));
}

