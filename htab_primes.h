#ifndef HTAB_PRIMES_INCLUDED
#define HTAB_PRIMES_INCLUDED

#include <stddef.h>

size_t next_prime(size_t num);
size_t get_prime(size_t num);
size_t prime_index(size_t num);
size_t prime_at(size_t ind);

#endif // HTAB_PRIMES_INCLUDED
