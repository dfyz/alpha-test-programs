WARN_OPTS=-Wall -pedantic
FLAGS=-O2 -target alpha-linux-gnu -std=c11 -g

CFLAGS=$(WARN_OPTS) $(FLAGS)

.PHONY: all
all: bignum.o main.o

.PHONY: clean
clean:
	rm -f *.o

bignum.o: defs.h bignum.h bignum.c
main.o: defs.h bignum.h main.c
