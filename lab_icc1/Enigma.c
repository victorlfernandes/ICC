#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int i, j;
	char alfabeto[2][26];
	//alfabeto[0][n]: letras minúsculas
	//alfabeto[1][n]: letras maiúsculas
	for(i=0; i<2; i++){
		for(j=0; j<26; j++){
			if(i == 0){
				alfabeto[i][j] = 97 + j;
			}
			else{
				alfabeto[i][j] = 65 + j;
			}	
		}
	}
	
	//ignorando linha "Rotores"
	scanf("%*[^\r\n]s");
	
	//preenchendo os rotores
	int rotor[3][26];
	for(i=0; i<3; i++){
		for(j=0; j<26; j++){
			scanf(" %d", &rotor[i][j]);	
		}	
	}
	
	//ignorando pulo de linha 
	scanf("%*[\r\n]s");
	//ignorando linha "Mensagem"
	scanf("%*[^\r\n]s");
	//ignorando pulo de linha
	scanf("%*[\r\n]s");
	
	char mensagem, decodificada;
	int contPrimeiro = 0, contSegundo = 0;
	while(scanf("%c", &mensagem) != EOF){
		
		//decodificando
		int contador = 0;
		for(i=0; i<2; i++){
			for(j=0; j<26; j++){
				if(mensagem == alfabeto[i][j]){
					decodificada = alfabeto[i][rotor[2][rotor[1][rotor[0][j]]]];
					contador = contador + 1;
					//imprimindo se for do alfabeto
					printf("%c", decodificada);
				}
			}
		}
		//imprimindo se nao for do alfabeto
		if(contador == 0){
			printf("%c", mensagem);
			continue;
		}
		
		//girando o primeiro rotor
		int aux1 = rotor[0][0];
		for(i=0; i<25; i++){
			rotor[0][i] = rotor[0][i+1];
		}
		rotor[0][25] = aux1; 
		contPrimeiro = contPrimeiro + 1;
		
		//girando o segundo rotor
		if(contPrimeiro == 26){
			int aux2 = rotor[1][0];
			for(i=0; i<25; i++){
				rotor[1][i] = rotor[1][i+1];
			}
			rotor[1][25] = aux2; 
			contSegundo = contSegundo + 1;
			contPrimeiro = 0;
		}
		
		//girando o terceiro rotor
		if(contSegundo == 26){
			int aux3 = rotor[2][0];
			for(i=0; i<25; i++){
				rotor[2][i] = rotor[2][i+1];
			}
			rotor[2][25] = aux3; 
			contSegundo = 0;
		}
		
	}
	
	return 0;
}
