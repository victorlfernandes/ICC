#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int maxRodadas, jogadores, pingu;
	scanf("%u %u %u", &maxRodadas, &jogadores, &pingu);
	
	int i, j;
	int contador = 1;
	for(i=1; i<=maxRodadas; i++){
		for(j=1; j<=i; j++){
			if(contador<=maxRodadas){
				if(contador>=pingu && ((contador-pingu)%jogadores) == 0){
					if(contador == 1){
						printf("%d pinguim\n", i);	
					}
					else{
						printf("%d pinguins\n", i);
					}						
				}
				contador = contador + 1;
			}
			else{
				exit(0);
			}
		}
		for(j=1; j<=i; j++){
			if(contador<=maxRodadas){
				if(contador>=pingu && ((contador-pingu)%jogadores) == 0){
					printf("no gelo\n");
				}
				contador = contador + 1;
			}
			else{
				exit(0);
			}
		}
		for(j=1; j<=i; j++){
			if(contador<=maxRodadas){
				if(contador>=pingu && ((contador-pingu)%jogadores) == 0){
					printf("uhuu!\n");
				}
				contador = contador + 1;
			}
			else{
				exit(0);
			}
		}	
	}
	return 0;
}

