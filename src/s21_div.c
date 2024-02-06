#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal dec_rem;

  s21_divide(value_1, value_2, result, &dec_rem, 0);
  return 0;
}