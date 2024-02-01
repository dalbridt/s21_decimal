#include "s21_decimal.h"

void s21_decreace_scale_big_decimal(s21_big_decimal *dst, int n) {
  int scale = get_scale_big_decimal(*dst);
  for (int i = 0; i < n; i++) {
    scale--;
  }
  set_scale_big_decimal(dst, scale);
}

int s21_post_normalization(s21_big_decimal *result, int scale) {
  while ((result->bits[3] || result->bits[4] || result->bits[5] ||
          result->bits[6]) &&
         scale > 0) {
    s21_decreace_scale_big_decimal(result, 1);
    big_decimal_mantissa_shift_r(result, 1);
  }

  return scale;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, scale = 0;
  s21_big_decimal val_1 = {0}, val_2 = {0}, res = {0};
  import_to_big_decimal(value_1, &val_1);
  import_to_big_decimal(value_2, &val_2);
  if (get_sign(value_1) != get_sign(value_2)) set_sign(result, 1);
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
  return error;
}