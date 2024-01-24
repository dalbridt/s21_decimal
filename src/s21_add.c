#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  int exp_1 = get_scale(value_1);
  int exp_2 = get_scale(value_2);

  if (exp_1 != exp_2) {
    printf("exp1 : %d | exp2: %d", exp_1, exp_2);
  }

  int ctrl = 0;
  int mask = 1;

  for (int arr_idx = 2; arr_idx >= 0; arr_idx--) {
    for (int bit_idx = 31; bit_idx >= 0; bit_idx--) {
      // add bits by applying mask

    }
  }

  return flag;
}
