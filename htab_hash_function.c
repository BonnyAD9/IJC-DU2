// htab_hash_function.c
// Řešení IJC-DU2, příklad 2), 25.3. 2023
// Autor: Jakub Antonín Štigler, FIT
// Přeloženo: clang 15.0.7
//  C standard: C11

#include "htab.h"     // htab_key_t, size_t
#include <inttypes.h> // uint32_t

size_t htab_hash_function(htab_key_t str) {
    uint32_t h = 0;
    for (; *str; ++str)
        h = 65599 * h + (unsigned char)*str;
    return h;
}
