#include "_htab.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    for (size_t i = 0; i < t->arr_size; ++i) {
        for (node_t *n = t->arr_ptr[i]; n; n = n->next)
            f(&n->data);
    }
}
