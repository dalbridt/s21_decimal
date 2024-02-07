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

    int scale = s21_post_normalization(&big_res);
    if (scale != AM_OK){
      flag = scale;
      s21_reset_big(&big_res);
    } else {
    s21_big_to_decimal(big_res, result);
    s21_set_scale(result, scale);
    }
    s21_set_sign(result, s21_get_sign(value_1) ^ s21_get_sign(value_2));

    // debug_display_big_decimal("big res", big_res);
  }

  return flag;
}