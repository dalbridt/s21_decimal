#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int flag = AM_OK;
  if (result != NULL) {
    int scale = s21_get_scale(value);
    flag = s21_decimal_validation(value);
    while (scale > 0) {
      s21_div10(&value, scale == 1 ? 5 : 0);
      scale--;
    }
    s21_set_scale(&value, 0);
    *result = value;
  } else {
    flag = AM_OF;
  }
  return flag;
}