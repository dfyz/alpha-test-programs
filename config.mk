OBJECTS=$(SOURCES:.c=.o)

COMPILER ?= clang
MODE ?= release

ifeq ($(COMPILER),gcc)
    CC=alpha-linux-gnu-gcc-10
    PLATFORM_FLAGS=-mcpu=ev67
else
    CC=~/llvm-build/bin/clang
    PLATFORM_FLAGS=--target=alpha-linux-gnu --sysroot=/usr/alpha-linux-gnu
endif

ifeq ($(MODE),debug)
    OPT_FLAGS=-O0
else
    OPT_FLAGS=-O2
endif

WARN_OPTS=-Wall -pedantic
FLAGS=-std=c11 -g
CFLAGS=$(WARN_OPTS) $(FLAGS) $(OPT_FLAGS) $(PLATFORM_FLAGS)

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
