#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int flag = 1;
  if (result != NULL) {
    *result = value;
    s21_set_sign(result, s21_get_sign(value) == 0 ? 1 : 0);
    flag = s21_decimal_validation(value);
  } else {
    flag = AM_OF;
  }
  return flag;
}