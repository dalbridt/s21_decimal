#include "s21_decimal.h"

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  // bool value = 1;
  // if (is_decimal_zero(value_1) && is_decimal_zero(value_2)) {
  //   value = 0;
  // } else if (get_sign(value_1) == get_sign(value_2)) {
  //   if (get_scale(value_1) != get_scale(value_2)) {
  //     equalize_scale(&value_1, &value_2);
  //   }
  //   value = get_mantissa(&value_1) != get_mantissa(&value_2);
  // }
  // return value;
  return !s21_is_equal(value_1, value_2);
}