#include <stdio.h>

int main(){
	
	char esteira[32][65];
	int i, j;
	int iDoInicio, jDoInicio;
	for(i=0; i<32; i++){
		for(j=0; j<65; j++){
			scanf("%c", &esteira[i][j]);
			if(esteira[i][j] == '['){
				iDoInicio = i;
				jDoInicio = j;
			}	
		}
	}
	
	i = iDoInicio;
	j = jDoInicio;
	//enquanto a esteira não achar uma falha, um loop infinito ou um ], rodar os comandos da esteira
	while(esteira[i][j] != ' ' && esteira[i][j] != '.' && esteira[i][j] != ']'){ 
		switch(esteira[i][j]){
			case '[':
				j = j+2;
				break;
			case '>':
				esteira[i][j] = '.';
				j = j+2;
				break;
			case '<':
				esteira[i][j] = '.';
				j = j-2;
				break;
			case '^':
				esteira[i][j] = '.';
				i = i-1;
				break;
			case 'v':
				esteira[i][j] = '.';
				i = i+1;
				break;
			case '#':
				//deslizar para baixo
				if((esteira[i-1][j] == '.' || esteira[i-1][j] == '#') && esteira[i+1][j] != '.'){
					i = i+1;
				}
				//deslizar para direita
				else if((esteira[i][j-2] == '.' || esteira[i][j-2] == '#') && esteira[i][j+2] != '.'){
					j = j+2;
				}
				//deslizar para esquerda
				else if((esteira[i][j+2] == '.' || esteira[i][j+2] == '#') && esteira[i][j-2] != '.'){
					j = j-2;
				}
				//deslizar para cima
				else{
					i = i-1;
				}
			}
	}
	
	//printando o resultado da esteira
	if(esteira[i][j] == ' '){
		printf("Falha na esteira.\n");
	}
	else
	if(esteira[i][j] == '.'){
		printf("Loop infinito.\n");
	}
	else{ //nesse caso, esteira[i][j] == ']'
		printf("Ok.\n");
	}
	
	//printando o estado final da esteira
	for(i=0; i<32; i++){
		for(j=0; j<65; j++){
			printf("%c", esteira[i][j]);	
		}
	}
	
	return 0;
}
