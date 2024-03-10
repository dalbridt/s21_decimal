#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  rnd_code flag = RND_ERR;

  if (result != NULL //
      && s21_decimal_validation(value)) {
    s21_reset(result);
    flag = RND_OK;

    int scale = s21_get_scale(value);
    while (scale != 0) {
      s21_div10(&value, false);
      scale--;
    }
    s21_set_scale(&value, 0);
    *result = value;
  }

  return flag;
}