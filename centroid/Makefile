WARN_OPTS=-Wall -pedantic
FLAGS=-O2 -target alpha-linux-gnu -std=c11 -g

CFLAGS=$(WARN_OPTS) $(FLAGS)

.PHONY: all
all: main.o

.PHONY: clean
clean:
	rm -f *.o

main.o: main.c
