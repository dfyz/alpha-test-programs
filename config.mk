OBJECTS=$(SOURCES:.c=.o)

CC=~/build/bin/clang
WARN_OPTS=-Wall -pedantic
FLAGS=-O2 -std=c11 -g
PLATFORM_FLAGS=--target=alpha-linux-gnu --sysroot=/usr/alpha-linux-gnu
LLVM_FLAGS=
CFLAGS=$(WARN_OPTS) $(FLAGS) $(PLATFORM_FLAGS) $(LLVM_FLAGS)

LD=alpha-linux-gnu-gcc-9

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: main
main: $(OBJECTS)
	$(LD) -o main $(OBJECTS) -lm

.PHONY: clean
clean:
	rm -f *.o

