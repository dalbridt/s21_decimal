#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int flag = AM_OK;
  flag = s21_decimal_validation(src);
  int scale = s21_get_scale(src);

  for (int i = 0; i < scale; i++) {
    s21_div10(&src, true);
  }
  *dst = src.bits[0];
  if (s21_get_sign(src)) {  // нужно ли не?
    *dst *= -1;
  }

  return flag;
}