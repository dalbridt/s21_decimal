#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  // bool value;

  // bool zeros = decimal_is_zero(value_1) && decimal_is_zero(value_2);

  // if (zeros) {
  //   value = true;
  // } else {
  //   bool equal_exp = get_scale(value_1) == get_scale(value_2);
  //   bool equal_sign = get_sign(value_1) == get_sign(value_2);
  //   // TODO:
  //   bool equal_mantissa = get_mantissa(&value_1) == get_mantissa(&value_2);

  //   value = equal_exp && equal_mantissa && equal_sign;
  // }
  // return value;
  return !s21_is_not_equal(value_1, value_2);
}