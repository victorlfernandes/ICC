#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ATRIBUTOS{
    int hp;
    int ataques;
    int defesa;
    int ataque_especial;
    int defesa_especial;
    int velocidade;
};

struct ATAQUES{
    char *nome_ataque;
    int poder;
    float acuracia;
    char classe;
};

struct POKEMON{
    char *nome_pokemon;
    char *tipo_primario;
    char *tipo_secundario;
    struct ATRIBUTOS atributos;
    struct ATAQUES ataques[4];
};

char *read_line(FILE *stream){
    char c;
    int n_chars = 0;
    char *line = NULL;
    while ((c = fgetc(stream)) != '\n' && c != EOF){
        line = realloc (line, (n_chars + 1));
        line[n_chars] = c;
        n_chars++; 
    }
    line = realloc (line, (n_chars + 1));
    line[n_chars] = '\0';
    return line;
}  

int main(){

    int qtd_pokemons = 0;
    struct POKEMON *pokemon = NULL;
    int i_pokemon;
    int i_ataque;

    bool funcionando = true;
    while (funcionando){
        int comando;
        scanf(" %d\n\n", &comando);
        switch (comando){
            case 0:
                funcionando = false;
                break;
            case 1: //cadastrar novo pokemon
                pokemon = realloc(pokemon, (qtd_pokemons + 1) * sizeof(struct POKEMON));
                pokemon[qtd_pokemons].nome_pokemon = read_line(stdin);
                pokemon[qtd_pokemons].tipo_primario = read_line(stdin);
                pokemon[qtd_pokemons].tipo_secundario = read_line(stdin);
                scanf(" %d\n", &pokemon[qtd_pokemons].atributos.hp);
                scanf(" %d\n", &pokemon[qtd_pokemons].atributos.ataques);
                scanf(" %d\n", &pokemon[qtd_pokemons].atributos.defesa);
                scanf(" %d\n", &pokemon[qtd_pokemons].atributos.ataque_especial);
                scanf(" %d\n", &pokemon[qtd_pokemons].atributos.defesa_especial);
                scanf(" %d\n", &pokemon[qtd_pokemons].atributos.velocidade);
                qtd_pokemons++;
                break;
            case 2: //adicionar um ataques a lista de um pokemon
                scanf(" %d\n", &i_pokemon);
                scanf(" %d\n", &i_ataque);
                pokemon[i_pokemon].ataques[i_ataque].nome_ataque = read_line(stdin);
                scanf(" %d\n", &pokemon[i_pokemon].ataques[i_ataque].poder);
                scanf(" %f\n", &pokemon[i_pokemon].ataques[i_ataque].acuracia);
                scanf(" %c\n", &pokemon[i_pokemon].ataques[i_ataque].classe);
                break;
            case 3: //imprimir os dados do pokemon
                scanf(" %d\n", &i_pokemon);
                printf("Nome do Pokemon: %s\n", pokemon[i_pokemon].nome_pokemon);
                printf("Tipo primario: %s\n", pokemon[i_pokemon].tipo_primario);
                printf("Tipo secundario: %s\n", pokemon[i_pokemon].tipo_secundario);
                printf("Status:\n");
                printf("\tHP: %d\n", pokemon[i_pokemon].atributos.hp);
                printf("\tAtaque: %d\n", pokemon[i_pokemon].atributos.ataques);
                printf("\tDefesa: %d\n", pokemon[i_pokemon].atributos.defesa);
                printf("\tAtaque Especial: %d\n", pokemon[i_pokemon].atributos.ataque_especial);
                printf("\tDefesa Especial: %d\n", pokemon[i_pokemon].atributos.defesa_especial);
                printf("\tVelocidade: %d\n\n", pokemon[i_pokemon].atributos.velocidade);
                break;
            case 4: //imprimir os dados de um ataques de um pokemon
                scanf(" %d\n", &i_pokemon);
                scanf(" %d\n", &i_ataque);
                printf("Nome do Ataque: %s\n", pokemon[i_pokemon].ataques[i_ataque].nome_ataque);
                printf("Poder base: %d\n", pokemon[i_pokemon].ataques[i_ataque].poder);
                printf("Acuracia: %f\n", pokemon[i_pokemon].ataques[i_ataque].acuracia);
                printf("Classe: %c\n\n", pokemon[i_pokemon].ataques[i_ataque].classe);
                break;
        }
    }

    //desalocando a memoria
    for (int i = 0; i < qtd_pokemons; i++){
        free(pokemon[i].nome_pokemon);
        free(pokemon[i].tipo_primario);
        free(pokemon[i].tipo_secundario);
        for (int j = 0; j < 4; j++){
            free(pokemon[i].ataques[j].nome_ataque);
        }
    }
    free(pokemon);

    return 0;
}