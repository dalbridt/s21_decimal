#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  reset_decimal(dst);
  set_sign(dst, signbit(src));
  if (signbit(src)) {
    src *= -1;
  }
  dst->bits[0] = src | BLANK;
  return 0;
}