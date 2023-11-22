#include "dllist.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    element_t val;
    node_t   *next;
    node_t   *prev;
};

struct list {
    node_t *start;
    node_t *end;
    int     size;
};

list_t *list_create() {
    list_t *list = malloc(sizeof(list_t));
    assert(list != NULL);
    list->start = NULL;
    list->end   = NULL;
    list->size  = 0;
    return list;
}

node_t *node_create() {
    node_t *node = malloc(sizeof(node_t));
    node->val    = (element_t)0;
    node->next   = NULL;
    node->prev   = NULL;
    return node;
}

void node_delete(node_t *node) {
    assert(node != NULL);
    free(node);
}

void list_delete(list_t *list) {
    assert(list != NULL);
    node_t *node = list->start;
    while (list->size > 0 && node != NULL) {
        list->start = node->next;
        node_delete(node);
        node = list->start;
    }
    free(list);
}

bool list_search(list_t *list, element_t element) {
    assert(list != NULL);
    node_t *node = list->start;
    while (node != NULL) {
        if (node->val->code == element->code) return true;
        node = node->next;
    }
    return false;
}

void list_insert(list_t *list, element_t element) {
    assert(list != NULL);
    node_t *node = node_create();
    node->val = element;
    if (list->size == 0) {
        list->start = node;
        list->end   = node;
        list->start->prev = NULL;
        list->start->next  = NULL;
    }
    else {
        node->next = NULL;
        node->prev = list->end;
        list->end->next = node;
        list->end = node;
    }   
    list->size++;
}

void list_remove(list_t *list, element_t element) {
    assert(list != NULL);
    if (!list_search(list, element)) return;
    node_t *node = list->start;
    while (node != NULL) {
        if (node->val == element) {
            if (list->size == 1) {
                node->next = NULL;
                node->prev = NULL;
            }
            else if (node == list->start) {
                list->start = node->next;
                list->start->prev = NULL;
            }
            else if (node == list->end) {
                list->end = node->prev;
                list->end->next = NULL;
            }
            else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
            node_delete(node);
            list->size--;
            return;
        }
        else 
            node = node->next;
    }
}

int list_size(list_t *list) {
    assert(list != NULL);
    return list->size;
}

void list_rotate(list_t *list) {
    assert(list != NULL);
    node_t *node = node_create();
    node->val = list->start->val;
    node->prev = list->end;
    node->next = NULL;
    list->end->next = node;
    list->end = node;
    list->start = list->start->next;
    if (list->start != NULL && list->start->prev != NULL){
    node_delete(list->start->prev);
    list->start->prev = NULL;
    }
}

void list_antirotate(list_t *list) {
    assert(list != NULL);
    node_t *node = node_create();
    node->val = list->end->val;
    node->prev = NULL;
    node->next = list->start;
    list->start->prev = node;
    list->start = node;
    list->end = list->end->prev;
    if (list->end != NULL && list->end->next != NULL){
    node_delete(list->end->next);
    list->end->next = NULL;
    }
}

void sort_list(list_t *list) {
    assert(list != NULL);
    node_t *i = NULL;
    node_t *j = NULL;
    for (i = list->start; i->next != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (
                (i->val->priority < j->val->priority) ||
                (i->val->priority == j->val->priority && i->val->code > j->val->code)
            ) {
                element_t aux = i->val;
                i->val = j->val;
                j->val = aux;
            }
        }
    }
}

process_t **read_process(int *n_process) {

    // allocating an array with all the process data
    process_t **process = malloc(MAX_PROCESS * sizeof(process_t *));
    for (int i = 0; i < MAX_PROCESS; i++)
        process[i] = malloc(sizeof(process_t));

    // reading info
    bool reading = true;
    do {

        scanf(" %d", &process[*n_process]->code);
        scanf(" %d", &process[*n_process]->ini_time);
        scanf(" %d", &process[*n_process]->p_left);
        scanf(" %d", &process[*n_process]->priority);

        (*n_process)++;

        // verifying if the reading is done
        char ch = getchar();
        if (ch == EOF)
            reading = false;
        else
            ungetc(ch, stdin);

    } while (reading);

    return process;
}

void round_robin(list_t *list, process_t **process) {

    int time = 1;
    bool working = true;
    do {

        // checking if a node must be inserted at this time
        bool inserted = false;
        for (int i = 0; i < MAX_PROCESS; i++) {
            if (process[i]->ini_time == time) {
                // verifying if this code already exists
                while (list_search(list, process[i])) 
                   process[i]->code++;
                list_insert(list, process[i]);
                // if the node we are inserting has greater priority than 
                // the next running element, we must sort all nodes by 
                // priority and code
                if (list->size > 1 && process[i]->priority >= list->start->val->priority)
                    sort_list(list);
                else if (!inserted && list->size > 1) {
                    list_remove(list, process[i]);
                    list_antirotate(list);
                    list_insert(list, process[i]);
                    list_rotate(list);
                }
                inserted = true;
            }
        }

        // processing the first element of the list
        bool finished = run_process(list->start, time);

        // removing the finished process or rotating the list
        if (finished) 
            list_remove(list, list->start->val);
        else 
            list_rotate(list);

        time++;

        // checking if its finished
        if (list_size(list) == 0)
            working = false;

    } while (working);

}

bool run_process(node_t *node, int time) {
    
    // reducing the number of times this process needs to run
    node->val->p_left--;

    // checking if this process is done
    bool process_finished = false;
    if (node->val->p_left <= 0) {
        printf("%d %d\n", node->val->code, time);
        process_finished = true;
    }

    return process_finished;
}
