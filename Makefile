# Makefile
# Řešení IJC-DU2, příklad 1) a 2), 25.3. 2023
# Autor: Jakub Antonín Štigler, FIT
# Přeloženo: cc - clang 15.0.7

CFLAGS:=-g -Wall -pedantic -std=c11 -Wextra -fsanitize=address
LDFLAGS:=-g -fsanitize=address
HTAB:=htab_basic.o htab_clean.o htab_for_each.o htab_hash_function.o \
htab_lookup.o htab_statistics.o

.PHONY: all clean

all: tail wordcount wordcount-dynamic

T:=$(shell $(CC) -MM *.c > dep.d)
-include dep.d

tail:

libhtab.a: $(HTAB)
	ar r $@ $^

libhtab.so: $(HTAB)
	$(CC) -shared -o $@ $^

wordcount: io.o wordcount.o libhtab.a
	$(CC) $(LDFLAGS) -o $@ $^

wordcount-dynamic: io.o wordcount.o libhtab.so
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	-rm *.o tail *.a wordcount *.so wordcount-dynamic
