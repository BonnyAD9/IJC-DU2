#include "htab.h"     // htab_key_t, size_t
#include <inttypes.h> // uint32_t

size_t htab_hash_function(htab_key_t str) {
    uint32_t h = 0;
    for (; *str; ++str)
        h = 65599 * h + (unsigned char)*str;
    return h;
}
