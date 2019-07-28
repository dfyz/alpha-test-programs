#pragma once

#include "defs.h"

struct bignum;

size_t bignum_size(size_t digits);

void reset_bignum(struct bignum *num);
struct bignum *init_bignum(void *memory);
void bignum_mov(struct bignum *lhs, const struct bignum *rhs);

size_t bignum_digits(const struct bignum *num);
digit_t bignum_at(const struct bignum *num, size_t pos);

void bignum_fma(struct bignum *num, double_digit_t mul, digit_t add);
digit_t bignum_divmod(struct bignum *num, double_digit_t div);

int bignum_cmp(const struct bignum *lhs, const struct bignum *rhs);
void bignum_sub(struct bignum *lhs, const struct bignum *rhs);
