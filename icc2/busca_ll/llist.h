#ifndef _LLIST_H_
#define _LLIST_H_

#include "str.h"
#include <stdbool.h>

typedef char * element_t;
typedef struct list list_t;
typedef struct node node_t;

#define INVALID -19203
#define ALPHA_S 26
#define ASCII_ALPHA 97

list_t *list_create();
void list_delete(list_t *list);

void list_insert_sorted(list_t *list, element_t element);

int list_size(list_t *list);
void list_search(list_t *list, node_t **array, element_t element);
void list_print(list_t *list, char *format, int n_elements);

void read_and_insert(list_t *list);
void update_index_array(list_t *list, node_t **array);

#endif
