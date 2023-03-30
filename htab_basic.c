// htab_basic.c
// Řešení IJC-DU2, příklad 2), 25.3. 2023
// Autor: Jakub Antonín Štigler, FIT
// Přeloženo: clang 15.0.7
//  C standard: C11

#include "_htab.h"        // size_t, htab_t, NULL

#include <stdlib.h> // calloc, malloc, free

#include "htab_primes.h" // get_prime

htab_t *htab_init(const size_t n) {
    htab_t *tab = malloc(sizeof(*tab));
    if (!tab)
        return NULL;

    tab->size = 0;
    // the size of the table is always prime to ensure better distribution
    // even for poor hashing functions
    tab->arr_size = get_prime(n);
    tab->arr_ptr = calloc(tab->arr_size, sizeof(*tab->arr_ptr));
    if (!tab->arr_ptr) {
        free(tab);
        return NULL;
    }

    return tab;
}

size_t htab_size(const htab_t *t) {
    return t->size;
}

size_t htab_bucket_count(const htab_t *t) {
    return t->arr_size;
}
