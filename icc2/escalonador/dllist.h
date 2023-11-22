#ifndef _DLLIST_H_
#define _DLLIST_H_

#include <stdbool.h>
#include <limits.h>

typedef struct process {
    int code;
    int ini_time;
    int p_left;
    int priority;
} process_t;

typedef struct node node_t;
typedef process_t * element_t;
typedef struct list list_t;

#define INVALID INT_MIN
#define MAX_PROCESS 4

list_t *list_create();
void list_delete(list_t *list);

void list_insert(list_t *list, element_t element);
void list_remove(list_t *list, element_t element);

bool list_search(list_t *list, element_t element);
int list_size(list_t *list);
void list_rotate(list_t *list);
void list_antirotate(list_t *list);
void sort_list(list_t *list);

process_t **read_process(int *n_process);
void round_robin(list_t *list, process_t **process);
bool run_process(node_t *node, int time);

#endif
