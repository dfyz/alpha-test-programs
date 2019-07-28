WARN_OPTS=-Wall -pedantic
FLAGS=-O2 -target alpha-linux-gnu -std=c11 -g

CFLAGS=$(WARN_OPTS) $(FLAGS)

.PHONY: all
all: fib.o main.o

.PHONY: clean
clean:
	rm -f *.o

fib.o: fib.c
main.o: main.c
