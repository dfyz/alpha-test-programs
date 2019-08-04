CC=/home/dfyz/build/bin/clang
WARN_OPTS=-Wall -pedantic
FLAGS=-O2 -std=c11 -g
PLATFORM_FLAGS=-target alpha-linux-gnu
LLVM_FLAGS=

CFLAGS=$(WARN_OPTS) $(FLAGS) $(PLATFORM_FLAGS) $(LLVM_FLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f *.o

.PHONY: all
