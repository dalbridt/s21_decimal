#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  am_code flag = AM_ERR;
  if (result != NULL                     //
      && s21_decimal_validation(value_1) //
      && s21_decimal_validation(value_2)) {
    flag = AM_OK;
    if (s21_is_zero(value_1) || s21_is_zero(value_2)) {
      s21_reset(result);
    } else {
      s21_big_decimal val_1 = {0}, val_2 = {0}, res = {0};
      s21_decimal_to_big(value_1, &val_1);
      s21_decimal_to_big(value_2, &val_2);
      s21_mul_big(val_1, val_2, &res);
      s21_set_sign_big(&res, s21_get_sign(value_1) ^ s21_get_sign(value_2));
      flag = s21_big_to_decimal(res, result);
      if (s21_is_zero(*result)) {
        flag = AM_NOF;
      }
    }
  }

  return flag;
}