#include "io.h" // FILE, EOF, fgetc, feof

#include <ctype.h> // isspace

int read_word(char *s, int max, FILE *f) {
    while (isspace(fgetc(f)))
        ;

    if (feof(f))
        return EOF;

    int c;
    int i = 0;
    for (; i < max - 1 && (c = fgetc(f)) != EOF && !isspace(c); ++i) {
        s[i] = c;
    }

    return i;
}
