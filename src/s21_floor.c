#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_truncate(value, result);
  if (get_sign(value) && get_scale(value)) {
    // s21_decimal one;
    // decimal_one(&one);
    // *result = add_decimals_mantissa(result, &one);
    //??????
  }
  return 0;
}