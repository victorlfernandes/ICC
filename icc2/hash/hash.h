#ifndef _HASH_H_
#define _HASH_H_

#include "llist.h"
#include <stdbool.h>

typedef list_t * hash_t;
typedef long long int lli;

hash_t *create_hash_table(int size);
void delete_hash_table(hash_t *ht, int size);

void insert(hash_t *hash, int hash_size, string_t str);
void rmv(hash_t *hash, int hash_size, string_t str);

bool search(hash_t *hash, int hash_size, string_t str);
void print(hash_t *hash, lli pos);

#endif
