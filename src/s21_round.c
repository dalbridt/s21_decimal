#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int flag = 0;
  if (result != NULL) {
    int scale = s21_get_scale(value);

    while (scale > 0) {
      s21_div10(&value, scale == 1 ? 5 : 0);
      scale--;
    }
    s21_set_scale(&value, 0);

    *result = value;
    flag = 1;
  }
  return flag;
}