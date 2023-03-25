#include "io.h" // FILE, EOF, fgetc, feof

#include <ctype.h> // isspace

int read_word(char *s, int max, FILE *f) {
    int c;
    while (isspace(c = fgetc(f)))
        ;

    if (c == EOF)
        return EOF;

    int i = 0;

    do s[i++] = c;
    while (i < max - 1 && (c = fgetc(f)) != EOF && !isspace(c));

    s[i] = 0;

    // skip the rest of the word if the word was too large
    if (!isspace(c)) {
        while (!isspace(c = fgetc(f)) && c != EOF)
            ;
    }

    return i;
}
