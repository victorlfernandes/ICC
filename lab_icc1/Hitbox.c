#include <stdio.h>

int main(){
	
	long long int x1, y1, largura1, altura1;
	scanf("%lli %lli %lli %lli\n", &x1, &y1, &largura1, &altura1);
	long long int x2, y2, largura2, altura2;
	scanf("%lli %lli %lli %lli", &x2, &y2, &largura2, &altura2);
	
	//condição para ter hit
	if((x1+largura1 >= x2 && x2+largura2 >= x1) && (y1+altura1 >= y2 && y2+altura2 >= y1)){
		
		//coordenadas do vértice superior esquerdo do retêngulo de interseção
		long long int x3, y3; 
		if(x1 >= x2){
			x3 = x1;
		}	
		else{
			x3 = x2;
		}
		if(y1 >= y2){
			y3 = y1;
		}
		else{
			y3 = y2;
		}
		
		unsigned long long int larguraHit;
		//quando x1 é maior que x2 e um retângulo não está contido horizontalmente no outro
		if(x1 > x2 &&  x1+largura1 > x2+largura2){ 
			larguraHit = x2 + largura2 - x1;
		}
		else
			//quando x2 é maior que x1 e um retângulo não está contido horizontalmente no outro
			if(x2 > x1 && x2+largura2 > x1+largura1){ 
				larguraHit = x1 + largura1 - x2;
			}
			else
				//quando x1 é maior ou igual a x2 e um retângulo está contido horizontalmente no outro 
				//e a largura1 é menor ou igual a largura2
				if(x1 >= x2 && largura1 <= largura2){ 
					larguraHit = largura1;
				}
				else{
					//quando x2 é maior ou igual a x1 e um retângulo está contido horizontalmente no outro
					//e a largura2 é menor que a largura1
					larguraHit = largura2;
				}
		
		unsigned long long int alturaHit;
		//quando y1 é maior que y2 e um retângulo não está contido verticalmente no outro
		if(y1 > y2 && y1+altura1 > y2+altura2){ 
			alturaHit = y2 + altura2 - y1;	
		}
		else
			//quando y2 é maior que y1 e um retângulo não está contido verticalmente no outro
			if(y2 > y1 && y2+altura2 > y1+altura1){ 
				alturaHit = y1 + altura1 - y2;
			}
			else
				//quando y1 é maior ou igual a y2 e um retângulo está contido verticalmente no outro
				//e a altura1 é menor ou igual a altura2
				if(y1 >= y2 && altura1 <= altura2){ 
					alturaHit = altura1;					
				}
				else{
					//quando y2 é maior que y1 e um retângulo está contido verticalmente no outro
					//e a altura2 é menor que a altura1
					alturaHit = altura2;
				}
		
		printf("HIT: %lli %lli %llu %llu\n", x3, y3, larguraHit, alturaHit);
	}
	else{
		printf("MISS\n");
	}
	
	return 0;
} 
