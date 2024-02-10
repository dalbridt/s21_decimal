#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_reset(result);
  int flag = AM_OK;
  if (result != NULL) {
    flag = s21_decimal_validation(value);
    int scale = s21_get_scale(value);
    while (scale != 0) {
      s21_div10(&value, false);
      scale--;
    }
    s21_set_scale(&value, 0);
    *result = value;
  } else {
    flag = AM_OF;
  }
  return flag;
}