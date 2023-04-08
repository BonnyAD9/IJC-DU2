// htab_clean.c
// Řešení IJC-DU2, příklad 2), 25.3. 2023
// Autor: Jakub Antonín Štigler, FIT
// Přeloženo: clang 15.0.7
//  Funguje s gcc 12.2.1
//  C standard: C11

#include "_htab.h" // htab_t, size_t, node_t, NULL

#include <stdlib.h> // free

void htab_clear(htab_t *t) {
    for (size_t i = 0; i < t->arr_size; ++i) {
        for (node_t *n = t->arr_ptr[i]; n;) {
            node_t *on = n;
            n = n->next;
            free((void *)on->data.key);
            free(on);
        }
        t->arr_ptr[i] = NULL;
    }
}

void htab_free(htab_t *t) {
    htab_clear(t);
    free(t->arr_ptr);
    free(t);
}
