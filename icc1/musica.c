#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SONG_LIMIT 15

struct SONGS{
        char *s_name;
        char *s_artist;
        unsigned int s_length;
};

struct PLAYLIST{
    char *p_name;
    int n_songs;
    short int current_s;
    struct SONGS songs[SONG_LIMIT];
};

//reads a line from the buffer
//and return it as a string (with a \0 at the end)
char *read_line(){
    char c;
    int n_chars = 0;
    char *line = NULL;
    while ((c = getchar()) != '\n'){
        line = realloc (line, (n_chars + 1));
        line[n_chars] = c;
        n_chars++; 
    }
    //adding one memory space to allocate \0
    line = realloc (line, (n_chars + 1));
    line[n_chars] = '\0';
    return line;
}   

//adds a song to the end of playlist
void add_song(struct PLAYLIST *playlist){
    //ingnoring \n 
    getchar();

    //reading song name
    playlist->songs[playlist->n_songs].s_name = read_line();
    //reading artist name
    playlist->songs[playlist->n_songs].s_artist = read_line();
    //reading song length
    scanf(" %u", &playlist->songs[playlist->n_songs].s_length);
    printf("Musica %s de %s adicionada com sucesso.\n", 
            playlist->songs[playlist->n_songs].s_name, 
            playlist->songs[playlist->n_songs].s_artist);

    playlist->n_songs++;
}

//prints all data from playlist
void print_playlist(struct PLAYLIST *playlist){
    printf("---- Playlist: %s ----\n", playlist->p_name);
    printf("Total de musicas: %d\n\n", playlist->n_songs);
    int i;
    for (i=0; i<playlist->n_songs; i++){
        if (playlist->current_s == i){
            printf("=== NOW PLAYING ===\n");
        }
        printf("(%d). '%s'\n", i+1, playlist->songs[i].s_name);
        printf("Artista: %s\n", playlist->songs[i].s_artist);
        printf("Duracao: %d segundos\n\n", playlist->songs[i].s_length);
    }   
}

int main(){

    //allocating the struct 
    struct PLAYLIST *playlist = calloc(1, sizeof(struct PLAYLIST));

    //reading the playlist name
    playlist->p_name = read_line();

    bool is_managing = true;
    while (is_managing){
        int command;
        scanf(" %d", &command);
        switch (command){
            case 1: //adds song to playlist
                if (playlist->n_songs == SONG_LIMIT){
                    printf("Playlist cheia!\n");
                    continue;
                }
                else{
                    add_song(playlist);    
                    if (playlist->n_songs == 1){
                        playlist->current_s = 0;
                    }
                }
                break;
            case 2: //prints playlist
                print_playlist(playlist);
                break;
            case 3: //advances player
                playlist->current_s++;
                break;
            case 4: //retreats player
                playlist->current_s--;
                break;
            case 5: //quit
                is_managing = false;
        }
    }

    //deallocating the memory
    free(playlist->p_name);
    for (int i=0; i<playlist->n_songs; i++){
        free(playlist->songs[i].s_name);
        free(playlist->songs[i].s_artist);
    }
    free(playlist);

    return 0;
}