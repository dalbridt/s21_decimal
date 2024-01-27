#include "s21_decimal.h"

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  bool value = 1;
  if (decimal_is_zero(value_1) && decimal_is_zero(value_2)) {
    value = 0;
  } else if (get_sign(value_1) == get_sign(value_2)) {
    if (get_scale(value_1) != get_scale(value_2)) {
      equalize_scale(&value_1, &value_2);
      // TODO:
    }
    bool mantissa_is_equal = get_mantissa(&value_1) == get_mantissa(&value_2);
    if (mantissa_is_equal) {
      value = get_scale(value_1) != get_scale(value_2);
    } else {
      value = 1;
    }
  }
  return value;
}