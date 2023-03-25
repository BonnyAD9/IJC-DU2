CFLAGS:=-g -Wall -std=c17 -fsanitize=address
LDFLAGS:=-g -Wall -std=c17 -fsanitize=address
RFLAGS:=-std=c17 -DNDEBUG -O3

.PHONY: all clean

all: tail wordcount

T:=$(shell $(CC) -MM *.c > dep.d)
-include dep.d

tail:

libhtab.a: htab_basic.o htab_clean.o htab_for_each.o htab_hash_function.o \
htab_lookup.o htab_statistics.c
	ar r libhtab.a $^

wordcount: io.o wordcount.o libhtab.a
	$(CC) $(LDFLAGS) -o wordcount -L. io.o wordcount.o -lhtab

clean:
	-rm *.o tail *.a wordcount
