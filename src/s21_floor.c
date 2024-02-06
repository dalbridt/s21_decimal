#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int flag = s21_truncate(value, result);
  if (s21_get_sign(value) && s21_get_scale(value)) {
    // s21_decimal one;
    // s21_set_one(&one);
    // *result = s21_add_mantissas(result, &one);
    //??????
  }
  return flag;
}