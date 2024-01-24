#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float* dst) {
  unsigned int* b = &src.bits[0];
  unsigned int byte;

  int sign = get_sign(src);
  int exp = get_scale(src);

  long double mantissa = get_mantissa(&src);

  while (exp > 0) {
    mantissa /= 10;
    exp--;
  }

  *dst = mantissa * (sign ? -1 : 1);

  return 0;
}