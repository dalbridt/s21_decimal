#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int ret = 1;
  *dst = (s21_decimal){0};

  //if (!isinf(src) && !isnan(src))
    // if(src == 0) - что тогда ? 
    int sign = src > 0 ? 0 : 1;
    // int sign = *(int *)&src >> 31; // побитовый способ извлечения знака, может быть нужно для +0 и -0
    int exponent = ((*(int *)&src & ~0x80000000) >> 23) - 127;
  

  return ret;
}