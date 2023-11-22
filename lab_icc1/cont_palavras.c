#include <stdio.h>

int main(){
	
	char caractere, aux = ' ';
	int contLinhas=0, contPalavras=0, contChars=0;
	while(scanf("%c", &caractere) != EOF){
        
        //uma nova linha deve ser contabilizada se o caracter lido for um pula linha
        //porém, se a sequencia de caracteres for \r\n, o \n nao deve ser motivo de nova linha
        //porque o \r ja contabilizou esse pulo
        if((caractere == '\n' && aux != '\r') || caractere == '\r'){
			contLinhas++;
		}

		//uma nova palavra deve ser contabilizada se o caracter lido for um espaço ou pula linha
        //e o caracter anterior pertencer a uma palavra
        if ((caractere == ' ' || caractere == '\t' || caractere == '\n' || caractere == '\r') 
        &&  (aux != ' ' && aux != '\n' && aux != '\t' && aux != '\r')){
			contPalavras++;
		}
		
        contChars++;
        aux = caractere;
	}

    //uma nova palavra deve ser contabilizada se o último caracter lido antes do EOF pertencer a uma palavra
    if(aux != ' ' && aux != '\n' && aux != '\t' && aux != '\r'){
        contPalavras++;
    }
    
	printf("Linhas\tPalav.\tCarac.\n");
	printf("%d\t%d\t%d", contLinhas, contPalavras, contChars);

	return 0;
}
