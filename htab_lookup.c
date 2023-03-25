// htab_lookup.c
// Řešení IJC-DU2, příklad 2), 25.3. 2023
// Autor: Jakub Antonín Štigler, FIT
// Přeloženo: clang 15.0.7
//  C standard: C11

#include "_htab.h" // htab_t, htab_pair_t, htab_key_t, NULL, strcmp, strlen, memcpy

#include <stdlib.h> // calloc, free

// finds the place where node with the key is or should be in the hash table
static node_t **_htab_lookup(const htab_t *t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    node_t **node = t->arr_ptr + index;
    while (*node && strcmp(key, (**node).data.key) != 0)
        node = &(**node).next;
    return node;
}

// returns null if the key is not in the table
htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {
    node_t *n = *_htab_lookup(t, key);
    return n ? &n->data : NULL;
}

// adds the key to the table if it is not there, on success returns pointer
// to the data on that position, otherwise returns NULL. COPIES THE KEY
htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    node_t **n = _htab_lookup(t, key);
    if (!*n) {
        *n = calloc(1, sizeof(**n));
        if (!*n)
            return NULL;

        size_t key_len = strlen(key) + 1;
        char *data_key = malloc(key_len);
        if (!data_key) {
            free(*n);
            return NULL;
        }

        memcpy(data_key, key, key_len);
        (**n).data.key = data_key;
        ++t->size;
    }
    return &(**n).data;
}

// removes the node with the given key from the table. Returns true if the key
// was removed, returns false if the key was not in the table
_Bool htab_erase(htab_t *t, htab_key_t key) {
    node_t **pn = _htab_lookup(t, key);
    if (!*pn)
        return 0;

    node_t *n = *pn;
    *pn = n->next;
    free((void *)n->data.key);
    free(n);

    return 1;
}
