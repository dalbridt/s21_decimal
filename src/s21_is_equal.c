#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  bool value = 0;
  if (s21_is_zero(value_1) && s21_is_zero(value_2)) {
    value = 1;
  } else if (s21_get_sign(value_1) == s21_get_sign(value_2)) {
    if (s21_get_scale(value_1) != s21_get_scale(value_2)) {
      s21_equalize_scale(&value_1, &value_2);
    }
    value = s21_get_mantissa(&value_1) == s21_get_mantissa(&value_2);
  }
  return value;
}