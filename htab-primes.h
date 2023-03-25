#ifndef HTAB_PRIMES_INCLUDED
#define HTAB_PRIMES_INCLUDED

#include <stddef.h> // size_t

// gets the smallest prime larger than the number
size_t get_close_prime(size_t num);
// gets the prime on the given index, or the last if the index is too large
size_t get_prime(size_t num);
// gets the index of the prime
size_t prime_index(size_t num);
// returns the number of precomputed primes
size_t primes_count(void);

#endif HTAB_PRIMES_INCLUDED
