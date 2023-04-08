// htab_primes.h
// Řešení IJC-DU2, příklad 2), 30.3. 2023
// Autor: Jakub Antonín Štigler, FIT
// Přeloženo: cc - clang 15.0.7
//  Funguje s gcc 12.2.1

#ifndef HTAB_PRIMES_INCLUDED
#define HTAB_PRIMES_INCLUDED

#include <stddef.h>

size_t next_prime(size_t num);
size_t get_prime(size_t num);
size_t prime_index(size_t num);
size_t prime_at(size_t ind);

#endif // HTAB_PRIMES_INCLUDED
