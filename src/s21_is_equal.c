#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  bool value = false;

  s21_big_decimal value_big_1, value_big_2;

  s21_decimal_to_big(value_1, &value_big_1);
  s21_decimal_to_big(value_2, &value_big_2);

  if (s21_is_big_zero(value_big_1) && s21_is_big_zero(value_big_2)) {
    value = true;
  } else if (s21_get_sign_big(value_big_1) == s21_get_sign_big(value_big_2)) {
    if (s21_get_scale_big(value_big_1) != s21_get_scale_big(value_big_2)) {
      s21_equalize_scale_big(&value_big_1, &value_big_2);
    }
    value = (s21_mantisa_compare_big(value_big_1, value_big_2) == -1 &&
             s21_get_scale_big(value_big_1) == s21_get_scale_big(value_big_2));
  }
  return value;
}