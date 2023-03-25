#include <stdio.h>  // size_t, FILE, fprintf, fopen, fclose, fscanf, fputs,
                    // NULL
#include <stdlib.h> // strtoul, EXIT_FAILURE, EXIT_SUCCESS, free, malloc,
                    // calloc
#include <assert.h> // assert
#include <string.h> // strcmp

// ANSI escape codes colorful prints
#ifdef NO_COLOR_PRINT
#define MAGENTA
#define RESET
#define RED
#else
#define RED "\e[91m"
#define MAGENTA "\e[95m"
#define RESET "\e[0m"
#endif

// Circular buffer headers >>==================================================

// curcular buffer
typedef struct {
    size_t size;
    size_t write;
    size_t read;
    char **buffer;
} cb_t;

// creates new circular buffer that can hold up to 'n' items at once, n must
// be at least 1. returns buffer with size 0 if the creation fails
cb_t cb_create(size_t n);
// adds line to the buffer. Returns the overwritten line or NULL if no line
// was overwritten
char *cb_put(cb_t *cb, char *line);
// gets the line from the read position and moves to the next position, returns
// null if the buffer is empty
char *cb_get(cb_t *cb);
// frees the memory allocated by the budder DOESN'T FREE THE ITEMS
void cb_free(cb_t cb);


// Tail implementation >>======================================================

// line length implementation limit
#define MAX_LINE_LEN ((size_t)4095)

// writes the last 'line_count' lines from 'in' to 'out'. returns true on
// success, otherwise false
_Bool tail(FILE *in, FILE* out, size_t line_count);
// my implementation of gets that returns the position of the last readed
// character. Len must be at least 1 (the behavior is undefined for 0) as
// it also includes the newline character
char *getline(FILE *in, char *buffer, size_t len);

int main(int argc, char **argv) {
    char *filename = NULL;
    size_t line_count = 10;

    // parse the arguments, only one filename allowed
    // multiple -n arguments allowed, the last takes effect
    while (*++argv) { // C standard says that argv[argc] shall be NULL
        if (strcmp(*argv, "-n") == 0) {
            if (!*++argv) {
                fprintf(
                    stderr,
                    RED "failure:" RESET " Expected positive integer after "
                    "'-n', but there are no more arguments\n"
                );
                return EXIT_FAILURE;
            }
            char *res;
            line_count = strtoul(*argv, &res, 10);
            if (*res || **argv == '-') {
                fprintf(
                    stderr,
                    RED "failure:" RESET " Expected positive integer after "
                    "'-n', found '%s'\n",
                    *argv
                );
                return EXIT_FAILURE;
            }
        } else if (filename) {
            fprintf(
                stderr,
                RED "failure:" RESET " Multiple files specified\n"
            );
            return EXIT_FAILURE;
        } else {
            filename = *argv;
        }
    }

    FILE *in = filename ? fopen(filename, "r") : stdin;
    int ret = EXIT_SUCCESS;

    if (!tail(in, stdout, line_count)) {
        fprintf(
            stderr,
            RED "failure:" RESET " An unrecoverable failure occured (maybe "
            "not enough memory)\n"
        );
        ret = EXIT_FAILURE;
    }

    if (filename)
        fclose(in);

    return ret;
}

_Bool tail(FILE *in, FILE *out, size_t line_count) {
    _Static_assert(MAX_LINE_LEN, "Invalid max line length (was 0)");

    cb_t lines = cb_create(line_count);
    if (lines.size == 0)
        return 0;
    char *buffer = NULL;

    // whether to print long line warning at the end
    _Bool warn = 0;
    size_t warndist = 0;

    // read the lines
    for (;; ++warndist) {
        // allocate the buffer if it isn't
        if (!buffer) {
            buffer = malloc(MAX_LINE_LEN);
            // when allocation fails it is time to panic
            if (!buffer)
                goto panic;
        }

        char *end = getline(in, buffer, MAX_LINE_LEN);
        if (end == buffer) // reached EOF
            break;
        // check if line is too long
        if (end[-1] != '\n' && end - buffer + 1 == MAX_LINE_LEN) {
            // skip all characters on the line (including newline)
            fscanf(in, "%*[^\n]");
            fscanf(in, "%*c");
            // make sure that all lines end with newline
            end[-1] = '\n';
            warn = 1;
            warndist = 0;
        }

        buffer = cb_put(&lines, buffer);
    }

    // print the lines and free the memory
    if (buffer)
        free(buffer);
    while ((buffer = cb_get(&lines))) {
        fputs(buffer, out);
        free(buffer);
    }
    cb_free(lines);

    // print the warning only if the long lines are actually printed
    if (warn && warndist <= line_count) {
        fprintf(
            stderr,
            "tail: " MAGENTA "warning:" RESET " some long lines were trimmed "
            "to %zu characters\n",
            MAX_LINE_LEN - 2
        );
    }

    return 1;

panic: // on error, free all memory and return false
    if (buffer)
        free(buffer);
    while ((buffer = cb_get(&lines)))
        free(buffer);
    cb_free(lines);

    return 0;
}

char *getline(FILE *in, char *buffer, size_t len) {
    assert(len);

    int c = 0;
    while (--len && c != '\n' && (c = fgetc(in)) != EOF)
        *buffer++ = c;
    *buffer = 0;

    return buffer;
}


// Curcular buffer implementation >>===========================================

cb_t cb_create(size_t n) {
    cb_t cb = {
        .size = n + 1,
        .write = 0,
        .read = 0,
        .buffer = NULL,
    };

    if (n < 1) {
        cb.size = 0;
        return cb;
    }

    cb.buffer = calloc(n + 1, sizeof(char *));
    if (!cb.buffer)
        cb.size = 0;

    return cb;
}

char *cb_put(cb_t *cb, char *line) {
    char *ret = (cb->write + 1) % cb->size == cb->read ? cb_get(cb) : NULL;

    cb->buffer[cb->write] = line;
    cb->write = (cb->write + 1) % cb->size;

    return ret;
}

char *cb_get(cb_t *cb) {
    if (cb->read == cb->write)
        return NULL;

    char *ret = cb->buffer[cb->read];
    cb->read = (cb->read + 1) % cb->size;

    return ret;
}

void cb_free(cb_t cb) {
    if (cb.buffer)
        free(cb.buffer);
}
