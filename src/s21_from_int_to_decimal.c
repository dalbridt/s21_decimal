#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  cnv_code flag = CNV_ERR;
  if (dst != NULL) {
    flag = CNV_OK;
    s21_reset(dst);
    s21_set_sign(dst, signbit((float)src));
    if (signbit((float)src)) {
      src *= -1;
    }
    dst->bits[0] = src | BLANK;
  }
  return flag;
}