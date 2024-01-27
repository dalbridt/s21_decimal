#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int scale = get_scale(src);

  for (int i = 0; i < scale; i++) {
    decimal_div10(&src, true);
  }
  *dst = src.bits[0];
  if (get_sign(src)) {  // нужно ли не?
    *dst *= -1;
  }

  return 0;
}