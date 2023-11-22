#include "llist.h"
#include <stdio.h>
#include <stdlib.h>

#define FINISH 0
#define READ 1
#define INDEX 2
#define SEARCH 3

int main() {

    list_t *list = list_create();
    node_t **index_array = malloc(ALPHA_S * sizeof(node_t *));
    bool updated = false;

    bool working = true;
    do {
            
        int command = read_int_until(stdin, NONE_CHAR);

        if (command == READ) { 
            read_and_insert(list); 
            updated = false;
        }

        else if (command == INDEX) {
            update_index_array(list, index_array);
            updated = true;
        }

        else if (command == SEARCH) {
            string_t str = read_str(stdin);
            if (updated) 
                list_search(list, index_array, str);
            else
                printf("Vetor de indices nao atualizado.\n");
            free(str);
        }

        else if (command == FINISH) 
            working = false;

    } while (working);

    list_delete(list);
    free(index_array);
    return 0;
}