#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_greater_or_equal(value_1, value_2);
}

int s21_is_less_big(s21_big_decimal value_1, s21_big_decimal value_2) {
  return !s21_is_greater_or_equal_big(value_1, value_2);
}