#include "s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  bool value;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  if (sign_1 != sign_2) {
    value = sign_1 > sign_2;
  } else {
    int exp_1 = get_scale(value_1);
    int exp_2 = get_scale(value_2);
    if (exp_1 != exp_2) {
      if (exp_1 < exp_2) {
        equalize_scale(&value_1, exp_2);
      } else {
        equalize_scale(&value_2, exp_1);
      }
    }
    if (sign_1 == 1) {
      value = get_mantissa(&value_1) < get_mantissa(&value_2);
    } else {
      value = get_mantissa(&value_1) > get_mantissa(&value_2);
    }
  }
  return value;
}