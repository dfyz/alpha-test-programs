#include "bignum.h"

#include <string.h>

struct bignum {
  size_t size;
  digit_t digits[];
};

const static int DIGIT_SIZE = sizeof(digit_t) * 8;

static digit_t lower(double_digit_t ddigit) {
  return ddigit & (((double_digit_t)1 << DIGIT_SIZE) - 1);
}

static digit_t higher(double_digit_t ddigit) {
  return ddigit >> DIGIT_SIZE;
}

static double_digit_t compose(digit_t high, digit_t low) {
  return ((double_digit_t)high << DIGIT_SIZE) + (double_digit_t)low;
}

size_t bignum_size(size_t digits) {
  return sizeof(size_t) + digits * sizeof(digit_t);
}

void reset_bignum(struct bignum *num) {
  num->size = 0;
}

struct bignum *init_bignum(void *memory) {
  struct bignum *rv = memory;
  reset_bignum(rv);
  return rv;
}

void bignum_mov(struct bignum *lhs, const struct bignum *rhs) {
  lhs->size = rhs->size;
  memcpy(lhs->digits, rhs->digits, sizeof(digit_t) * (lhs->size));
}

size_t bignum_digits(const struct bignum *num) {
  return num->size;
}

digit_t bignum_at(const struct bignum *num, size_t pos) {
  return num->digits[pos];
}

void bignum_fma(struct bignum *num, double_digit_t mul, digit_t add) {
  digit_t overflow = add;
  for (size_t i = 0; i != num->size; ++i) {
    double_digit_t product =
        (double_digit_t)num->digits[i] * mul + (double_digit_t)overflow;
    num->digits[i] = lower(product);
    overflow = higher(product);
  }

  if (overflow)
    num->digits[num->size++] = overflow;
}

digit_t bignum_divmod(struct bignum *num, double_digit_t div) {
  double_digit_t dividend = num->digits[num->size - 1];
  if (dividend < div && --num->size)
    dividend = compose(dividend, num->digits[num->size - 1]);
  digit_t rem = dividend % div;

  for (size_t i = num->size; i-- != 0;) {
    num->digits[i] = dividend / div;
    if (i > 0) {
      dividend = compose(rem, num->digits[i - 1]);
      rem = dividend % div;
    }
  }
  return rem;
}


static int compare_sizes(size_t lhs, size_t rhs) {
  return lhs < rhs ? -1 : lhs > rhs;
}

static int compare_digits(digit_t lhs, digit_t rhs) {
  return lhs < rhs ? -1 : lhs > rhs;
}

int bignum_cmp(const struct bignum *lhs, const struct bignum *rhs) {
  int rv = compare_sizes(lhs->size, rhs->size);
  if (rv)
    return rv;

  for (size_t i = lhs->size; i-- != 0;)
    if ((rv = compare_digits(lhs->digits[i], rhs->digits[i])))
      break;

  return rv;
}

void bignum_sub(struct bignum *lhs, const struct bignum *rhs) {
  int carry = 0;
  for (size_t i = 0; i != lhs->size; ++i) {
    double_digit_t minuend = compose(
        i == lhs->size - 1 ? 0 : 1, lhs->digits[i]);

    double_digit_t subtrahend =
        (double_digit_t)(i < rhs->size ? rhs->digits[i] : 0) + carry;
    minuend -= subtrahend;
    carry = higher(minuend) == 1 ? 0 : 1;
    lhs->digits[i] = lower(minuend);
  }

  for (size_t i = lhs->size; i-- != 0;)
    if (!lhs->digits[i])
      --lhs->size;
    else
      break;
}
