#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_truncate(value, result);
  if (get_sign(value) && get_scale(value)) {
    s21_decimal one = {
        .bits[0] = 0b00000000000000000000000000000001,
        .bits[1] = 0b00000000000000000000000000000000,
        .bits[2] = 0b00000000000000000000000000000000,
        .bits[3] = 0b00000000000000000000000000000000,
    };
    *result = add_decimals_mantissa(result, &one);
  }
  return 0;
}