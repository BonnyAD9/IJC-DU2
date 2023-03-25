#include <stddef.h>

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


size_t get_close_prime(size_t num) {
    return DPRIMES[prime_index(num)];
}

size_t get_prime(size_t num) {
    return num >= DPRIMES_LEN ? DPRIMES[DPRIMES_LEN - 1] : DPRIMES[num];
}

size_t prime_index(size_t num) {
    for (size_t i = 0; i < DPRIMES_LEN; ++i) {
        if (DPRIMES[i] >= num)
            return i;
    }

    return DPRIMES_LEN - 1;
}

size_t primes_count(void) {
    return DPRIMES_LEN;
}
