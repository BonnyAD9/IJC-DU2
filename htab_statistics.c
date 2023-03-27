// htab_statistics.c
// Řešení IJC-DU2, příklad 2), 25.3. 2023
// Autor: Jakub Antonín Štigler, FIT
// Přeloženo: clang 15.0.7
//  C standard: C11

#include "_htab.h" // htab_t, size_t, node_t

#include <inttypes.h> // SIZE_MAX
#include <stdio.h>    // fprintf, stderr

void htab_statistics(const htab_t *t) {
    size_t min_bucket = SIZE_MAX;
    size_t max_bucket = 0;
    size_t lists = 0;

    for (size_t i = 0; i < t->arr_size; ++i) {
        size_t c = 0;
        lists += t->arr_ptr[i] != NULL;
        for (node_t *n = t->arr_ptr[i]; n; n = n->next)
            ++c;
        if (c > max_bucket)
            max_bucket = c;
        if (c < min_bucket)
            min_bucket = c;
    }

    fprintf(
        stderr,
        "bucket count:  %zu\n"
        "max in bucket: %zu\n"
        "min in bucket: %zu\n"
        "avg in bucket: %lf\n",
        t->arr_size,
        max_bucket,
        min_bucket,
        (double)t->size / lists
    );
}
