#include "hash.h"
#include <stdlib.h>
#include <math.h>

#define P 1000000007
#define X 263

hash_t *create_hash_table(int size) {

    hash_t *ht = malloc(size * sizeof(hash_t));

    for (int i = 0; i < size; i++) 
        ht[i] = list_create();

    return ht;
}

void delete_hash_table(hash_t *ht, int size) {

    for (int i = 0; i < size; i++) 
        list_delete(ht[i]);

    free(ht);
}

lli hash_function(string_t str, int hash_size) {

    lli pos = 0;
    for (int i = 0; i < str_len(str) - 1; i++) 
        pos += (lli)(str[i] * pow(X, i));
    pos = pos % P;
    pos = pos % hash_size;
    return pos;
}

void insert(hash_t *hash, int hash_size, string_t str) {

    lli pos = hash_function(str, hash_size);
    list_insert(hash[pos], str);

}

void rmv(hash_t *hash, int hash_size, string_t str) {

    lli pos = hash_function(str, hash_size);
    list_remove(hash[pos], str);
    free(str);

}

bool search(hash_t *hash, int hash_size, string_t str) {

    lli pos = hash_function(str, hash_size);
    bool b = list_search(hash[pos], str);
    free(str);

    return b;
}

void print(hash_t *hash, lli pos) {

    list_print(hash[pos], "%s ");

}