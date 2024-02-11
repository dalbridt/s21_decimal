#include "s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  bool value;
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  if (sign_1 != sign_2) {
    value = sign_1 < sign_2;
  } else {
    s21_big_decimal value_big_1, value_big_2;
    int exp_1 = s21_get_scale(value_1);
    int exp_2 = s21_get_scale(value_2);
    s21_decimal_to_big(value_1, &value_big_1);
    s21_decimal_to_big(value_2, &value_big_2);
    if (exp_1 != exp_2) {
      s21_equalize_scale_big(&value_big_1, &value_big_2);
    }
    value = sign_1 ? (s21_mantisa_compare_big(value_big_2, value_big_1) == 1)
                   : (s21_mantisa_compare_big(value_big_1, value_big_2) == 1);
  }
  return value;
}