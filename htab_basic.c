#include "_htab.h"        // size_t, htab_t, NULL

#include <stdlib.h> // calloc, malloc, free

// precomputed prime numbers (32 prime numbers), each approximetly
// double of the previous. Used for the bucket counts of the hash table.
// the largest will be enough for more than 215GB worth of pointers to
// buckets if sizeof(void *) == 8
static const size_t DPRIMES[] = {
    11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437,
    102877, 205759, 411527, 823117, 1646237, 3292489, 6584983, 13169977,
    26339969, 52679969, 105359939, 210719881, 421439783, 842879579, 1685759167,
    3371518343, 6743036717, 13486073473, 26972146961,
};

// size of the DPRIMES array (should be 32)
#define DPRIMES_LEN (sizeof(DPRIMES) / sizeof(*DPRIMES))

static size_t _get_prime(size_t num) {
    for (size_t i = 0; i < DPRIMES_LEN; ++i) {
        if (DPRIMES[i] >= num)
            return DPRIMES[i];
    }

    return DPRIMES[DPRIMES_LEN - 1];
}

htab_t *htab_init(const size_t n) {
    htab_t *tab = malloc(sizeof(*tab));
    if (!tab)
        return NULL;

    tab->arr_size = 0;
    // the size of the table is always prime to ensure better distribution
    // even for poor hashing functions
    tab->arr_size = _get_prime(n);
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
