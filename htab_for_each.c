// htab_for_each.c
// Řešení IJC-DU2, příklad 2), 25.3. 2023
// Autor: Jakub Antonín Štigler, FIT
// Přeloženo: clang 15.0.7
//  Funguje s gcc 12.2.1
//  C standard: C11

#include "_htab.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    for (size_t i = 0; i < t->arr_size; ++i) {
        for (node_t *n = t->arr_ptr[i]; n; n = n->next)
            f(&n->data);
    }
}
