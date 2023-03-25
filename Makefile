CFLAGS:=-g -Wall -std=c17 -fsanitize=address
LDFLAGS:=-g -Wall -std=c17 -fsanitize=address
RFLAGS:=-std=c17 -DNDEBUG -O3

.PHONY: all clean

all: tail

T:=$(shell $(CC) -MM *.c > dep.d)
-include dep.d

tail:

clean:
	-rm *.o tail
