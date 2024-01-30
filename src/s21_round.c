#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int flag = 0;
  if (result != NULL) {
    int sign = get_sign(value);
    float val, whole;
    s21_from_decimal_to_float(value, &val);
    val = fabs(val);
    modff(val, &whole);
    val = val - whole;
    if (val >= 0.5) {
      whole += 1;
    }
    s21_from_float_to_decimal(whole, result);
    set_sign(result, sign);

    // int scale = get_scale(value);
    // while (scale > 0) {
    //   decimal_div10(&value, scale == 1 ? 5 : 1);
    //   scale--;
    // }
    // set_scale(&value, 0);

    // *result = value;
    flag = 1;
  }
  return flag;
}