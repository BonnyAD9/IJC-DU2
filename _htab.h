// _htab.h
// Řešení IJC-DU2, příklad 2), 25.3. 2023
// Autor: Jakub Antonín Štigler, FIT
// Přeloženo: clang 15.0.7
//  Funguje s gcc 12.2.1
//  C standard: C11

#ifndef _HTAB_INCLUDED
#define _HTAB_INCLUDED

#include "htab.h" // size_t, htab_pair_t

typedef struct htab_item_t node_t;

struct htab_item_t {
    htab_pair_t data;
    node_t *next;
};

struct htab {
    size_t size;
    size_t arr_size;
    node_t **arr_ptr;
};

#endif // _HTAB_INCLUDED
