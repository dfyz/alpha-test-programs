int fib(int);
int fib_rec(int);

int scanf(const char *format, ...);
int printf(const char *format, ...);

int main() {
  int n;
  if (scanf("%d", &n) == 1) {
    printf("%d\n", fib(n));
    printf("%d\n", fib_rec(n));
  }
}
