#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  reset_decimal(dst);

  dst->bits[0] = src & (~MINUS);

  // (unsigned int)src & (~MINUS);
  // set_sign(dst, signbit(src));
  return 0;
}