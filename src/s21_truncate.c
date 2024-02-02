#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int flag = 0;
  // if (result != NULL) {
  int scale = get_scale(value);

  while (scale != 0) {
    decimal_div10(&value, false);
    scale--;
  }
  set_scale(&value, 0);

  *result = value;
  flag = 1;
  // }
  return flag;
}