#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  am_code flag = AM_ERR;
  if (result != NULL                     //
      && s21_decimal_validation(value_1) //
      && s21_decimal_validation(value_2)) {
    s21_reset(result);
    flag = AM_OK;
    if (s21_is_zero(value_2)) {
      flag = AM_DIV0;
    } else if (s21_is_zero(value_1)) {
      s21_reset(result);
    } else {
      s21_big_decimal value_big_1, value_big_2, big_rem, big_res;
      s21_decimal_to_big(value_1, &value_big_1);
      s21_decimal_to_big(value_2, &value_big_2);
      s21_divide_big(value_big_1, value_big_2, &big_res, &big_rem, 0);
      s21_set_sign_big(&big_res, s21_get_sign(value_1) ^ s21_get_sign(value_2));
      flag = s21_big_to_decimal(big_res, result);
      if (s21_is_zero(*result)) {
        flag = AM_NOF;
      }
    }
  }

  return flag;
}