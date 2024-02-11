#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  rnd_code flag = RND_ERR;

  if (result != NULL && s21_decimal_validation(value)) {
    flag = RND_OK;
    *result = value;
    s21_set_sign(result, s21_get_sign(value) == 0 ? 1 : 0);
  }
  return flag;
}