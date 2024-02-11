#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float* dst) {
  cnv_code flag = CNV_ERR;
  if (dst != NULL && s21_decimal_validation(src)) {
    flag = CNV_OK;
    int sign = s21_get_sign(src);
    int exp = s21_get_scale(src);

    long double mantissa = s21_get_mantissa(&src);

    while (exp > 0) {
      mantissa /= 10;
      exp--;
    }

    *dst = (float)mantissa * (sign ? -1 : 1);
  };

  return flag;
}