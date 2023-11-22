#include "llist.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    element_t val;
    node_t   *nxt;
};

struct list {
    node_t *start;
    node_t *end;
    int     size;
};

node_t *node_create() {
    node_t *node = malloc(sizeof(node_t));
    node->val    = (element_t)0;
    node->nxt    = NULL;
    return node;
}

list_t *list_create() {
    list_t *list = malloc(sizeof(list_t));
    assert(list != NULL);
    list->start  = NULL;
    list->end    = NULL;
    list->size   = 0;
    return list;
}

void node_delete(node_t *node) {
    assert(node != NULL);
    free(node->val);
    free(node);
}

void list_delete(list_t *list) {
    assert(list != NULL);
    node_t *node = list->start;
    while (node != NULL) {
        list->start = node->nxt;
        node_delete(node);
        node = list->start;
    }
    free(list);
}

void list_insert_sorted(list_t *list, element_t element) {
    assert(list != NULL);
    node_t *new_node = node_create();
    new_node->val = element;
    if (list->size == 0) {
        new_node->nxt = NULL;
        list->start = new_node;
        list->end = new_node;
        list->size++;
        return;
    }
    node_t *node = list->start;
    node_t *prev_node = node;
    while (node != NULL && node->val[0] < element[0]) {
        prev_node = node;
        node = node->nxt;
    }
    if (node == list->start) {
        new_node->nxt = list->start;
        list->start = new_node;
    }
    else if (node == NULL) {
        new_node->nxt = NULL;
        list->end->nxt = new_node;
        list->end = new_node;
    }
    else {
        new_node->nxt = prev_node->nxt;
        prev_node->nxt = new_node;
    }
    list->size++;
}

int list_size(list_t *list) {
    assert(list != NULL);
    return list->size;
}

void list_search(list_t *list, node_t **array, element_t element) {
    assert(list != NULL);
    node_t *node = array[element[0] - ASCII_ALPHA];
    int node_counter = 0;
    while (node != NULL && node->val[0] == element[0]) {
        if (str_cmp(node->val, element)) {
            printf("%d\n", node_counter);
            return;
        }
        node = node->nxt;
        node_counter++;
    }
    printf("Palavra nao existe na lista.\n");
}

void list_print(list_t *list, char *format, int n_elements) {
    assert(list != NULL && format != NULL);
    node_t *node = list->start;
    int i = 0;
    while (node != NULL && i < n_elements) {
        printf(format, node->val);
        node = node->nxt;
        i++;
    }
}

void read_and_insert(list_t *list) {

    string_t file_name = read_str(stdin);
    FILE *file_pointer = fopen(file_name, "r");

    bool reading = true;
    do {

        string_t word = read_str(file_pointer);
        list_insert_sorted(list, word);

        char ch = fgetc(file_pointer);
        if (ch == EOF)
            reading = false;
        else
            ungetc(ch, file_pointer);

    } while (reading); 

    list_print(list, "%s\n", 3);

    free(file_name);
    fclose(file_pointer);
}

void update_index_array(list_t *list, node_t **array) {

    assert(list != NULL && array != NULL);

    int assignment_counter = 0;
    for (int i = 0; i < ALPHA_S; i++) {

        node_t *node = list->start;
        while (node != NULL && node->val[0] != (i + ASCII_ALPHA))
            node = node->nxt;

        if (node == NULL)
            array[i] = NULL;
        else {
            array[i] = node;
            assignment_counter++;
        }

    }

    printf("%d\n", assignment_counter);
}