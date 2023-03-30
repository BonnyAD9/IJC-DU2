// htab_primes.c
// Řešení IJC-DU2, příklad 2), 30.3. 2023
// Autor: Jakub Antonín Štigler, FIT
// Přeloženo: cc - clang 15.0.7

#include "htab_primes.h"

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

// gets prime that is approximatly twice the given one (from the table)
size_t next_prime(size_t num) {
    return prime_at(prime_index(num) + 1);
}

// gets smalles precalculated prime larger or equal the the value
size_t get_prime(size_t num) {
    return DPRIMES[prime_index(num)];
}

// gets the index of the prime in the precalculated values
size_t prime_index(size_t num) {
    for (size_t i = 0; i < DPRIMES_LEN; ++i) {
        if (DPRIMES[i] >= num)
            return i;
    }

    return DPRIMES_LEN - 1;
}

// gets prime from the precalculated primes at the index
size_t prime_at(size_t ind) {
    return DPRIMES[ind >= DPRIMES_LEN ? DPRIMES_LEN - 1 : ind];
}
