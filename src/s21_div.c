#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  am_code flag = AM_OK;

  if (s21_is_zero(value_2)) {
    flag = AM_DIV0;
  } else if (s21_is_equal(value_1, value_2)) {
    s21_set_one(result);
  } else {
    s21_big_decimal value_big_1, value_big_2, big_rem, big_res;

    s21_decimal_to_big(value_1, &value_big_1);
    s21_decimal_to_big(value_2, &value_big_2);

    s21_divide_big(value_big_1, value_big_2, &big_res, &big_rem, 0);

    // debug_display_big_decimal("big res", big_res);

    s21_big_to_decimal(big_res, result);
  }

  return flag;
}