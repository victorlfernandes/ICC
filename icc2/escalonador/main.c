/*******************************************************************************
 |                       USP - Universidade de São Paulo                       |
 |            ICMC - Instituto de Ciências Matemáticas e de Computação         |
 *******************************************************************************
 |                    Bacharelado em Ciências de Computação                    |
 |                                 2021/2                                      |
 |                 SCC0201 - Introdução à Ciências da Computação 2             |
 |                                                                             |
 |             Autor: Victor Lucas de Almeida Fernandes (12675399)             |
 *******************************************************************************
 >                           Escalonador de processos
 ******************************************************************************/

#include "dllist.h"
#include <stdlib.h>

int main() {

    // creating data structure
    list_t *list = list_create();

    // reading all data
    int n_process = 0;
    process_t **process = read_process(&n_process);    

    // processing with round robin algorithm
    round_robin(list, process);

    // deallocating memory
    for (int i = 0; i < n_process; i++) free(process[i]);
    free(process);
    list_delete(list);

    return 0;
}
