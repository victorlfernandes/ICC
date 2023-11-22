#include <stdio.h>
#include <string.h>

int main(){
	
    char linha[77];
    int logicSpam = 0;
    int proibida[12];
    int cont_proibidas = 0;
    char *palavra;
        
    while (scanf(" %[^\n]", linha) != EOF){
        
        //verificando tamanho da linha
        if (strlen(linha) > 76) 
            logicSpam = 1;
        
        //procurando por palavras proibidas
        palavra = strtok(linha, ", !s");
        while (palavra != NULL){

            proibida[0]  = strcmp(palavra, "gratuito");
            proibida[1]  = strcmp(palavra, "atencao"); 
            proibida[2]  = strcmp(palavra, "urgente");
            proibida[3]  = strcmp(palavra, "imediato");
            proibida[4]  = strcmp(palavra, "zoombie");
            proibida[5]  = strcmp(palavra, "oferta");
            proibida[6]  = strcmp(palavra, "dinheiro");
            proibida[7]  = strcmp(palavra, "renda");
            proibida[8]  = strcmp(palavra, "fundo");
            proibida[9]  = strcmp(palavra, "limitado");
            proibida[10] = strcmp(palavra, "ajuda");
            proibida[11] = strcmp(palavra, "SOS");

            palavra = strtok(NULL, ", !s");

            for(int i=0; i<12; i++){
    				if(proibida[i] == 0)
    					cont_proibidas++;
				}
        }
    }

    if(cont_proibidas >= 2)
		logicSpam = 1; 
     
    if (logicSpam) printf("Spam\n");
    else printf("Inbox\n");

    return 0;
}