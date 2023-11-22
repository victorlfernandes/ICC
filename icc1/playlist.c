#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SONG_LIMIT 15

struct SONGS{
        int length_s_name;
        char *s_name;
        int length_s_artist;
        char *s_artist;
        int s_length;
};

struct PLAYLIST{
    int length_p_name;
    char *p_name;
    int n_songs;
    int current_s;
    struct SONGS songs[SONG_LIMIT];
};

//reads a line from the buffer
//and return it as a string (with a \0 at the end)
char *read_line();

void binaryToNum(char *binFilename);

//adds a song to the end of playlist
void add_song(struct PLAYLIST *playlist);

//prints all data from playlist
void print_playlist(struct PLAYLIST *playlist);

//saves the playlist in a binary file
void save_playlist(struct PLAYLIST *playlist);

//loads the playlist from file to RAM
void load_playlist(struct PLAYLIST *playlist);

int main(){

    //allocating the struct 
    struct PLAYLIST *playlist = calloc(1, sizeof(struct PLAYLIST));

    //reading the playlist name
    playlist->p_name = read_line();
    playlist->length_p_name = strlen(playlist->p_name);

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
            case 5: //saves playlist
                save_playlist(playlist);
                break;
            case 6: //loads playlist
                load_playlist(playlist);
                break;
            case 7: //quit
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

void binaryToNum(char *binFilename) {
    FILE *fp = fopen(binFilename, "rb");

    double binValue = 0;
    double accumulator = 0.01;
    char ch;
    while (fread(&ch, sizeof(char), 1, fp)) {
        binValue += (double) ch * accumulator;
        accumulator += 0.01;
    }

    fclose(fp);
    printf("%lf\n", binValue);
}

void add_song(struct PLAYLIST *playlist){
    //ingnoring \n 
    getchar();

    //reading song name
    playlist->songs[playlist->n_songs].s_name = read_line();
    playlist->songs[playlist->n_songs].length_s_name = strlen(playlist->songs[playlist->n_songs].s_name);
    //reading artist name
    playlist->songs[playlist->n_songs].s_artist = read_line();
    playlist->songs[playlist->n_songs].length_s_artist = strlen(playlist->songs[playlist->n_songs].s_artist);
    //reading song length
    scanf(" %u", &playlist->songs[playlist->n_songs].s_length);
    printf("Musica %s de %s adicionada com sucesso.\n", 
            playlist->songs[playlist->n_songs].s_name, 
            playlist->songs[playlist->n_songs].s_artist);

    playlist->n_songs++;
}

void print_playlist(struct PLAYLIST *playlist){
    printf("---- Playlist: %.*s ----\n", playlist->length_p_name, playlist->p_name);
    printf("Total de musicas: %d\n\n", playlist->n_songs);
    int i;
    for (i=0; i<playlist->n_songs; i++){
        if (playlist->current_s == i){
            printf("=== NOW PLAYING ===\n");
        }
        printf("(%d). '%.*s'\n", i+1, playlist->songs[i].length_s_name, playlist->songs[i].s_name);
        printf("Artista: %.*s\n", playlist->songs[i].length_s_artist, playlist->songs[i].s_artist);
        printf("Duracao: %d segundos\n\n", playlist->songs[i].s_length);
    }   
}

void save_playlist(struct PLAYLIST *playlist){
    //ingnoring \n 
    getchar();

    //reading file name
    char *file_name = read_line();

    //opening file with the writing mode
    FILE *playlist_file = fopen(file_name, "wb");

    //saving the data
    fwrite(&playlist->length_p_name, sizeof(int), 1, playlist_file);
    fwrite(playlist->p_name, sizeof(char), playlist->length_p_name, playlist_file);
    fwrite(&playlist->n_songs, sizeof(int), 1, playlist_file);
    for (int i=0; i<playlist->n_songs; i++){
        fwrite(&playlist->songs[i].length_s_name, sizeof(int), 1, playlist_file);
        fwrite(playlist->songs[i].s_name, sizeof(char), playlist->songs[i].length_s_name, playlist_file);
        fwrite(&playlist->songs[i].length_s_artist, sizeof(int), 1, playlist_file);
        fwrite(playlist->songs[i].s_artist, sizeof(char), playlist->songs[i].length_s_artist, playlist_file);
        fwrite(&playlist->songs[i].s_length, sizeof(int), 1, playlist_file);
    }

    printf("Playlist %s salva com sucesso.\n", file_name);

    //closing file
    fclose(playlist_file);
    binaryToNum(file_name);
}

void load_playlist(struct PLAYLIST *playlist){
    //ingnoring \n 
    getchar();

    //reading file name
    char *file_name = read_line();

    //opening file with the reading mode
    FILE *playlist_file = fopen(file_name, "rb");
    if (playlist_file == NULL){
        printf("Arquivo %s nao existe.\n", file_name);
        exit(1);
    }
    

    //loading the data
    fread(&playlist->length_p_name, sizeof(int), 1, playlist_file);
    playlist->p_name = realloc(playlist->p_name, playlist->length_p_name);
    fread(playlist->p_name, sizeof(char), playlist->length_p_name, playlist_file);
    fread(&playlist->n_songs, sizeof(int), 1, playlist_file);
    for (int i=0; i<playlist->n_songs; i++){
        fread(&playlist->songs[i].length_s_name, sizeof(int), 1, playlist_file);
        playlist->songs[i].s_name = realloc(playlist->songs[i].s_name, playlist->songs[i].length_s_name);
        fread(playlist->songs[i].s_name, sizeof(char), playlist->songs[i].length_s_name, playlist_file);
        fread(&playlist->songs[i].length_s_artist, sizeof(int), 1, playlist_file);
        playlist->songs[i].s_artist = realloc(playlist->songs[i].s_artist, playlist->songs[i].length_s_artist);
        fread(playlist->songs[i].s_artist, sizeof(char), playlist->songs[i].length_s_artist, playlist_file);
        fread(&playlist->songs[i].s_length, sizeof(int), 1, playlist_file);
    }

    printf("Playlist %s carregada com sucesso.\n", file_name);

    //current song must be the first of the loaded playlist
    playlist->current_s = 0;

    //closing file
    fclose(playlist_file);
    binaryToNum(file_name);
}