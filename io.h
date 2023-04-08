// io.h
// Řešení IJC-DU2, příklad 2), 25.3. 2023
// Autor: Jakub Antonín Štigler, FIT
// Přeloženo: clang 15.0.7
//  Funguje s gcc 12.2.1
//  C standard: C11

#ifndef IO_INCLUDED
#define IO_INCLUDED

#include <stdio.h> // FILE

int read_word(char *s, int max, FILE *f);

#endif // IO_INCLUDED
