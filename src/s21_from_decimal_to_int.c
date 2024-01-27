#include "s21_decimal.h"

// maybe scale check should be included?

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL) {
    return 1;
  }
  *dst = src.bits[0];

  unsigned int sign = get_sign(src);
  *dst = *dst & ~(1 << 31);

  if (sign) {
    *dst = -1 * *dst;
  }

  return 0;
}