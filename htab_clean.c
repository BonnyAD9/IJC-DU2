#include "_htab.h" // htab_t, size_t, node_t, NULL

#include <stdlib.h> // free

void htab_clear(htab_t *t) {
    for (size_t i = 0; i < t->arr_size; ++i) {
        for (node_t *n = t->arr_ptr[i]; n;) {
            n = n->next;
            free((void *)n->data.key);
            free(n);
        }
        t->arr_ptr[i] = NULL;
    }
}

void htab_free(htab_t *t) {
    htab_clear(t);
    free(t->arr_ptr);
    free(t);
}
