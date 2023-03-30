// htab_lookup.c
// Řešení IJC-DU2, příklad 2), 25.3. 2023
// Autor: Jakub Antonín Štigler, FIT
// Přeloženo: clang 15.0.7
//  C standard: C11

#include "_htab.h" // htab_t, htab_pair_t, htab_key_t, NULL, strcmp, strlen, memcpy

#include <stdlib.h>   // calloc, free
#include <inttypes.h> // SIZE_MAX

#include "htab_primes.h" // prime_index

// finds the place where is or where to put node with the given key
static inline node_t **_htab_lookup_node(node_t **node, htab_key_t key) {
    node_t **n = node;
    while (*n && strcmp(key, (**n).data.key) != 0)
        n = &(**n).next;
    return n;
}

// finds the place where node with the key is or should be in the hash table
static inline node_t **_htab_lookup(
    const htab_t *t,
    htab_key_t key,
    size_t hash
) {
    return _htab_lookup_node(t->arr_ptr + hash % t->arr_size, key);
}

// finds the place where node with the given key is, searches only in the
// previous sizes of the table. Returns NULL if the table is the smallest
// returns &NULL if the item is not in the table
static inline node_t **_htab_lookup_small(
    const htab_t *t,
    htab_key_t key,
    size_t hash
) {
    node_t **n = NULL;
    for (size_t i = prime_index(t->arr_size) - 1; i != SIZE_MAX; --i) {
        n = _htab_lookup_node(t->arr_ptr + hash % prime_at(i), key);
    }
    return n;
}

// finds the place where node with the key is or should be, also searches
// smaller tables
static inline node_t **_htab_lookup_any(
    const htab_t *t,
    htab_key_t key
) {
    size_t hash = htab_hash_function(key);
    node_t **cur = _htab_lookup(t, key, hash);
    if (*cur)
        return cur;
    node_t **old = _htab_lookup_small(t, key, hash);
    return old ? old : cur;
}

// finds the place where node with the key is or should be, also searches
// smaller tables and if the key is found in the smaller table it is rehashed
static inline node_t **_htab_lookup_any_rehash(
    const htab_t *t,
    htab_key_t key
) {
    size_t hash = htab_hash_function(key);
    node_t **cur = _htab_lookup(t, key, hash);
    if (*cur)
        return cur;
    node_t **old = _htab_lookup_small(t, key, hash);
    if (!old || !*old)
        return cur;
    *cur = *old;
    *old = (**cur).next;
    (**cur).next = NULL;
    return cur;
}

// returns null if the key is not in the table
htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {
    node_t *n = *_htab_lookup_any_rehash(t, key);
    return n ? &n->data : NULL;
}

// adds the key to the table if it is not there, on success returns pointer
// to the data on that position, otherwise returns NULL. COPIES THE KEY
htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    node_t **n = _htab_lookup_any_rehash(t, key);
    if (!*n) {
        if (t->size + 1 > t->arr_size) {
            size_t new_size = next_prime(t->arr_size);
            node_t **new_arr =
                realloc(t->arr_ptr, new_size * sizeof(*new_arr));
            if (!new_arr) {
                return NULL;
            }
            t->arr_ptr = new_arr;
            for (size_t i = t->arr_size; i < new_size; ++i)
                t->arr_ptr[i] = NULL;
            t->arr_size = new_size;
            n = _htab_lookup(t, key, htab_hash_function(key));
        }
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
    node_t **pn = _htab_lookup_any(t, key);
    if (!*pn)
        return 0;

    node_t *n = *pn;
    *pn = n->next;
    free((void *)n->data.key);
    free(n);

    return 1;
}
