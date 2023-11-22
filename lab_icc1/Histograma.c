#include <stdio.h>

/* Função que imprime a frequência de cada cor */
void imprime(int contador, int tom);
/* Vetor global para que possa ser acessado na função imprime */
int cor[5] = {0, 1, 2, 3, 4};

int main(){
	
	int i;
	int pixel[25] = {};
	int cont[5] = {};
	for(i=0; i<25; i++){
		//recebendo a cor de cada pixel
		scanf(" %d", &pixel[i]);
		//verificando qual é a cor do pixel recebido
		if(pixel[i] == cor[0]){
			cont[0]++;
		}
		else if(pixel[i] == cor[1]){
			cont[1]++;
		}
		else if(pixel[i] == cor[2]){
			cont[2]++;
		}
		else if(pixel[i] == cor[3]){
			cont[3]++;
		}
		else{
			cont[4]++;
		}
	}
	
	//imprimindo a frequência de cada cor
	imprime(cont[0], cor[0]);
	imprime(cont[1], cor[1]);
	imprime(cont[2], cor[2]);
	imprime(cont[3], cor[3]);
	imprime(cont[4], cor[4]);
	
	//verificando a cor mais frequente
	int maisFreq;
	if(cont[0] > cont[1] && cont[0] > cont[2] && cont[0] > cont[3] && cont[0] > cont[4]){
		maisFreq = cor[0];
	}
	else if(cont[1] > cont[0] && cont[1] > cont[2] && cont[1] > cont[3] && cont[1] > cont[4]){
		maisFreq = cor[1];
	}
	else if(cont[2] > cont[0] && cont[2] > cont[1] && cont[2] > cont[3] && cont[2] > cont[4]){
		maisFreq = cor[2];
	}
	else if(cont[3] > cont[0] && cont[3] > cont[1] && cont[3] > cont[2] && cont[3] > cont[4]){
		maisFreq = cor[3];
	}
	else{
		maisFreq = cor[4];
	}
	
	//imprimindo os índices da cor mais frequente
	for(i=0; i<25; i++){
		if(pixel[i] == maisFreq){
			printf("%d\n", i);
		}
	}
	
	return 0;
}

void imprime(int contador, int tom){
	printf("%d: |", cor[tom]);
	int i;
	for(i=0; i<contador; i++){
		printf("#");
	}
	printf("\n");
}
