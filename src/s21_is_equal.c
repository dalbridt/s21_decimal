#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  bool value = 0;
  if (decimal_is_zero(value_1) && decimal_is_zero(value_2)) {
    value = 1;
  } else if (get_sign(value_1) == get_sign(value_2)) {
    if (get_scale(value_1) != get_scale(value_2)) {
      equalize_scale(&value_1, &value_2);
    }
    value = get_mantissa(&value_1) == get_mantissa(&value_2);
  }
  return value;
}