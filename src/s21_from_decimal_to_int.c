#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  cnv_code flag = CNV_ERR;
  if (dst != NULL && s21_decimal_validation(src)) {
    flag = CNV_OK;
    int scale = s21_get_scale(src);

    for (int i = 0; i < scale; i++) {
      s21_div10(&src, false);
    }

    unsigned int biggest = s21_get_sign(src) ? ~0x7fffffff : 0x7fffffff;
    if (((src.bits[1] + src.bits[2]) != 0) || src.bits[0] > biggest) {
      flag = CNV_ERR;
      *dst = 0xffffffff;
    } else {
      *dst = (int)src.bits[0];
      if (s21_get_sign(src)) {
        *dst *= -1;
      }
    }
  }
  return flag;
}