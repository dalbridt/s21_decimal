#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int ret = 1;
  if (!isinf(src) && !isnan(src) && dst != NULL) {
    *dst = (s21_decimal){0};
    if (src != 0) {
      uint32_t src_bits = *(uint32_t *)&src;

      int sign = (src_bits >> 31) & 1;  // use bit
      int exponent =((src_bits & ~0x80000000) >> 23) - 127;  // 0х -hex, left bit is set

      if (exponent > -95 && exponent < 95) {
        int scale = 0;
        // for (; !(int)src; src *= 10, scale++){  /// 0.0023 = 2.3 / scale
      }
    }
    ret = 0;
  }
  return ret;
}