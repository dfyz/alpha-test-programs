OBJECTS=$(SOURCES:.c=.o)

CC=~/llvm-build/bin/clang
WARN_OPTS=-Wall -pedantic
FLAGS=-O2 -std=c11 -g -mcpu=ev67
PLATFORM_FLAGS=--target=alpha-linux-gnu --sysroot=/usr/alpha-linux-gnu
LLVM_FLAGS=
CFLAGS=$(WARN_OPTS) $(FLAGS) $(PLATFORM_FLAGS) $(LLVM_FLAGS)

LD=alpha-linux-gnu-gcc-10

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: all
all: $(OBJECTS)
	$(LD) -o $(notdir $(CURDIR)) $(OBJECTS) -lm

.PHONY: clean
clean:
	rm -f *.o $(notdir $(CURDIR))

.PHONY: deploy
deploy: all
	scp $(notdir $(CURDIR)) alpha:
