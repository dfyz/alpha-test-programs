OBJECTS=$(SOURCES:.c=.o)

CC=~/build/bin/clang
WARN_OPTS=-Wall -pedantic
FLAGS=-O2 -std=c11 -g
PLATFORM_FLAGS=--target=alpha-linux-gnu --sysroot=/usr/alpha-linux-gnu/
LLVM_FLAGS=
LINKER_FLAGS=
CFLAGS=$(WARN_OPTS) $(FLAGS) $(PLATFORM_FLAGS) $(LLVM_FLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: main
main: $(OBJECTS)
	$(CC) $(PLATFORM_FLAGS) $(LINKER_FLAGS) -o main $(OBJECTS)

.PHONY: clean
clean:
	rm -f *.o

