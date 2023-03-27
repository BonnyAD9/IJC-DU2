// wordcount.c
// Řešení IJC-DU2, příklad 1), 25.3. 2023
// Autor: Jakub Antonín Štigler, FIT
// Přeloženo: clang 15.0.7
//  C standard: C11

#include "io.h"   // fprintf, EOF, read_word
#include "htab.h" // htab_t, htab_lookup_add, htab_pair_t

#include <stdlib.h> // EXIT_FAILURE

// arbitrary value, lare eough for larger files but not too large
// htab will automatically choose a some prime larger than this
#define TABLE_SIZE 4000

#define MAX_WORD_LEN 256

void print_table(htab_pair_t *val);

int main(void) {
    htab_t *m = htab_init(4000);
    if (!m) {
        fprintf(stderr, "failed to allocate hash table");
        return EXIT_FAILURE;
    }

    char buffer[MAX_WORD_LEN];

    while (read_word(buffer, MAX_WORD_LEN, stdin) != EOF) {
        htab_pair_t *val = htab_lookup_add(m, buffer);
        if (!val) {
            fprintf(stderr, "failed to add to hash table");
            goto panic; // when allocation fails it is time to panic
        }

        ++val->value;
    }

    htab_for_each(m, print_table);

    htab_statistics(m);

    htab_free(m);
    return EXIT_SUCCESS;

    // frees the resources and exits with failure
panic:
    htab_free(m);
    return EXIT_FAILURE;
}

void print_table(htab_pair_t *val) {
    printf("%s\t%d\n", val->key, val->value);
}
