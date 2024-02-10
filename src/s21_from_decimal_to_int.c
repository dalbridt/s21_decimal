#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  cnv_code flag = CNV_ERR;
  if (dst != NULL && s21_decimal_validation(src) == 0) {
    int scale = s21_get_scale(src);

    for (int i = 0; i < scale; i++) {
      s21_div10(&src, false);
    }
    // s21_decimal res;

    // s21_truncate(src, &res);

    if (src.bits[1] != 0 || src.bits[2] != 0 || s21_get_bit(src, 31)) {  //
      flag = CNV_ERR;
      *dst = 0xffffffff;
    } else {
      *dst = (int)src.bits[0];
      if (s21_get_sign(src)) {
        *dst *= -1;
      }
      flag = CNV_OK;
    }
  }

  return flag;
}