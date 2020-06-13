#include <stdio.h>

int fib(int);
int fib_rec(int);

#define N 40

int main() {
    printf("%d\n", fib(N));
    printf("%d\n", fib_rec(N));
}
