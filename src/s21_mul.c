#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, scale = 0;
  s21_big_decimal val_1 = {0}, val_2 = {0}, res = {0};
  reset_big_decimal(&val_1);
  decimal_to_big(value_1, &val_1);
  decimal_to_big(value_2, &val_2);

  scale = get_scale(value_1) + get_scale(value_2);
  error = mul_big_decimal(val_1, val_2, &res);
  scale = s21_post_normalization(&res, scale);
  if (scale >= 0) {
    set_scale(result, scale);
    import_to_small_decimal(res, result);
  } else {
    error = 1;
  }
  if (error == 1 && get_sign(*result)) error = 2;
  if (error) reset_decimal(result);
  set_sign(result, get_sign(value_1) ^ get_sign(value_2));
  return error;
}