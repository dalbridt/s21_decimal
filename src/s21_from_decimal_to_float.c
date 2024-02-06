#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float* dst) {
  int sign = s21_get_sign(src);
  int exp = s21_get_scale(src);

  long double mantissa = s21_get_mantissa(&src);

  while (exp > 0) {
    mantissa /= 10;
    exp--;
  }

  *dst = mantissa * (sign ? -1 : 1);

  return 0;
}