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
 >                              Tabela Hash
 ******************************************************************************/

#include "hash.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    int hash_size = read_int_until(stdin, NONE_CHAR);
    hash_t *hash = create_hash_table(hash_size);
    int n_ops = read_int_until(stdin, NONE_CHAR);

    for (int i = 0; i < n_ops; i++) {

        string_t op = read_until(stdin, ' ');

        if (str_cmp(op, "add")) {
            string_t word = read_str(stdin);
            insert(hash, hash_size, word);
        }

        else if (str_cmp(op, "del")) {
            string_t word = read_str(stdin);
            rmv(hash, hash_size, word);
        }

        else if (str_cmp(op, "check")) {
            string_t word = read_str(stdin);
            bool b = search(hash, hash_size, word);
            b ? printf("sim\n") : printf("não\n");
        }

        else if (str_cmp(op, "get")) {
            int i = read_int_until(stdin, NONE_CHAR);
            print(hash, i);
        }

        free(op);
    }

    delete_hash_table(hash, hash_size);

    return 0;
}