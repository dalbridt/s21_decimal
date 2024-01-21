#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  int exp_1 = get_scale(value_1);
  int exp_2 = get_scale(value_2);

  if (exp_1 != exp_2) {
    // equalize to get the same scale
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

void equalize_scale(s21_decimal *value, int scale_required) {
  int scale_cur = get_scale(*value);
  long double mantissa = get_mantissa(value);
  printf("TEST equalizer of scale:\nold mantissa: %Lf| old scale: %d\n",
         mantissa, scale_cur);

  if (scale_cur < scale_required) {
    for (scale_cur; scale_cur < scale_required; scale_cur++) {
      mantissa *= 10;
    }
  } else if (scale_cur > scale_required) {
    for (scale_cur; scale_cur > scale_required; scale_cur--) {
      mantissa /= 10;
    }
  }
  printf("new mantissa:  %Lf | new scale: %d\n", mantissa, scale_cur);
  // mantissa  ->  value (написала функцию флоат ту бин, нужно довести до ума)

  // required scale -> value
  set_scale(value, scale_cur);
}

