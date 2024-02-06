#include "s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  bool value;
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  if (sign_1 != sign_2) {
    value = sign_1 < sign_2;
  } else {
    int exp_1 = s21_get_scale(value_1);
    int exp_2 = s21_get_scale(value_2);
    if (exp_1 != exp_2) {
      s21_equalize_scale(&value_1, &value_2);
    }
    value = s21_get_mantissa(sign_1 ? &value_2 : &value_1) >=
            s21_get_mantissa(sign_1 ? &value_1 : &value_2);
  }
  return value;
}