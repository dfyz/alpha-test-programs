int fib(int n) {
  int a = 0;
  int b = 0;
  int c = 1;

  if (n <= 0) {
    return 0;
  }

  while (n > 1) {
    a = b;
    b = c;
    c = a + b;
    --n;
  }

  return c;
}

int fib_rec(int n) {
  if (n <= 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  return fib_rec(n - 1) + fib_rec(n - 2);
}
