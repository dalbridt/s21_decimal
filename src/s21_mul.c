#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  s21_big_decimal val_1 = {0}, val_2 = {0}, res = {0};
  s21_reset_big(&val_1);
  s21_decimal_to_big(value_1, &val_1);
  s21_decimal_to_big(value_2, &val_2);

  error = s21_mul_big(val_1, val_2, &res);
  s21_set_sign_big(&res, s21_get_sign(value_1) ^ s21_get_sign(value_2));
  error = s21_post_normalization(&res, s21_get_scale_big(res));
  s21_big_to_decimal(res, result);

  return error;
}