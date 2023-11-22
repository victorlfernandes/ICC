#include <stdio.h>

int main(){
	
	char tab[3][4];
	int i, j;
	int logic = 1;
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			scanf(" %c", &tab[i][j]);
			if(tab[i][j] == '-')
				logic = 0;
		}
	}
	
	if((tab[0][0] == 'x' && tab[0][1] ==  tab[0][0] && tab[0][2] == tab[0][0])
	|| (tab[1][0] == 'x' && tab[1][1] ==  tab[1][0] && tab[1][2] == tab[1][0])
	|| (tab[2][0] == 'x' && tab[2][1] ==  tab[2][0] && tab[2][2] == tab[2][0])
	|| (tab[0][0] == 'x' && tab[1][0] ==  tab[0][0] && tab[2][0] == tab[0][0])
	|| (tab[0][1] == 'x' && tab[1][1] ==  tab[0][1] && tab[2][1] == tab[0][1])
	|| (tab[0][2] == 'x' && tab[1][2] ==  tab[0][2] && tab[2][2] == tab[0][2])
	|| (tab[0][0] == 'x' && tab[1][1] ==  tab[0][0] && tab[2][2] == tab[0][0])
	|| (tab[0][2] == 'x' && tab[1][1] ==  tab[0][2] && tab[2][0] == tab[0][2])
	)
	printf("x ganhou\n");
	
	else
	if((tab[0][0] == 'o' && tab[0][1] ==  tab[0][0] && tab[0][2] == tab[0][0])
	|| (tab[1][0] == 'o' && tab[1][1] ==  tab[1][0] && tab[1][2] == tab[1][0])
	|| (tab[2][0] == 'o' && tab[2][1] ==  tab[2][0] && tab[2][2] == tab[2][0])
	|| (tab[0][0] == 'o' && tab[1][0] ==  tab[0][0] && tab[2][0] == tab[0][0])
	|| (tab[0][1] == 'o' && tab[1][1] ==  tab[0][1] && tab[2][1] == tab[0][1])
	|| (tab[0][2] == 'o' && tab[1][2] ==  tab[0][2] && tab[2][2] == tab[0][2])
	|| (tab[0][0] == 'o' && tab[1][1] ==  tab[0][0] && tab[2][2] == tab[0][0])
	|| (tab[0][2] == 'o' && tab[1][1] ==  tab[0][2] && tab[2][0] == tab[0][2])
	)
	printf("o ganhou\n");
	
	else
	if(logic)
	printf("empate\n");
	
	else
	printf("em jogo\n");
	
	return 0;
}
