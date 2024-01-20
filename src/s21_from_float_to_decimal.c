#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int ret = 1;
  if (!isinf(src) && !isnan(src) && dst != NULL) {
    *dst = (s21_decimal){0};
    if (src != 0) {
      uint32_t src_bits = *(uint32_t *)&src;

      int sign = (src_bits >> 31) & 1;
      int exponent =
          ((src_bits & ~0x80000000) >> 23) - 127;  // 0х -hex, left bit is set

      if (exponent > -95 && exponent < 95) {
        int scale = 0;
        // for (; !(int)src; src *= 10, scale++){} /0.0023 => 2.3 - if exp < -95
        // loop that makes 8 numbers before point (keeping track of scale) 
        // the number we get cast to int and put into decimal
        // get exponent
        // uns int mask = 0x400000;
        // set bit - (dst, ?)to set 1 that is default in float between exp bits and mantissa;
    
      }
    }
    ret = 0;
  }
  return ret;
}