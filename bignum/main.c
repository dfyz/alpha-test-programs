#include "bignum.h"

#include <stdio.h>

size_t MAX_DIGITS = 1 << 16;

int far(const struct bignum *d, const struct bignum *c,
        struct bignum *t) {
  bignum_mov(t, d);
  bignum_sub(t, c);
  bignum_fma(t, 100, 0);
  bignum_fma(t, 10, 0);
  return bignum_cmp(t, d) > 0;
}

int main(void) {
  unsigned char c_memory[bignum_size(MAX_DIGITS)];
  unsigned char d_memory[bignum_size(MAX_DIGITS)];
  unsigned char t_memory[bignum_size(MAX_DIGITS)];

  struct bignum *c = init_bignum(c_memory);
  struct bignum *d = init_bignum(d_memory);
  struct bignum *t = init_bignum(t_memory);

  for (int i = 2; i != 37; ++i) {
    reset_bignum(c);
    bignum_fma(c, i, i);

    reset_bignum(d);
    bignum_fma(d, 16, 1);
    bignum_fma(d, 16, 0);
    bignum_fma(d, 16, 0);

    unsigned c_pow = 1, d_pow = 1;

    while (far(d, c, t)) {
      bignum_fma(c, i, 0);
      ++c_pow;
      while (bignum_cmp(d, c) < 0) {
        bignum_fma(d, 16, 0);
        bignum_fma(d, 16, 0);
        ++d_pow;
      }
    }

    char exact = bignum_cmp(d, c) ? ' ' : '!';
    printf("%3d %7d %7d %c\n", i, c_pow, d_pow, exact);
  }
}
