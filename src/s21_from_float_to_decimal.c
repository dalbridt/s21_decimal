#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int ret = 1;
  if (!isinf(src) && !isnan(src) && dst != NULL) {
    *dst = (s21_decimal){0};
    if (src != 0) {
      uint32_t src_bits =
          *(uint32_t *)&src;  // to get aka int but with the same bits order

      int sign = (src_bits >> 31) & 1;
      int exponent =
          ((src_bits & ~0x80000000) >> 23) - 127;  // 0х -hex, left bit is set

      if (exponent > -95 && exponent < 95) {
        int scale = 0;
        printf("before any manipulations : %f\n", src);
        for (; !(int)src; src *= 10, scale++) {
        }  // 0.0023 => 2.3 - if exp < -95
        printf("after loop 1: %f || %d\n", src, scale);

        // loop that makes 8 numbers before point (keeping track of scale) -
        // FIXME int k = scale + 7; for (scale; scale < k; src *= 10, scale++) {
        // }
        // printf("after loop 2 : %f || %d\n", src, scale);

        // get exponent after normalization
        int exponent = ((src_bits & ~0x80000000) >> 23) - 127;
        set_bit(dst, exponent, 1);  // тут по идее мы должны были установить 22
                                    // бит, но экспонента может быть  минусовая
        printf("hoba! %d\n", exponent);

        // the number we get cast to int and put into decimal
        int temp = (int)src;
        for (int i = 0; i < 32; i++) {
          int val = !!(temp & (0x80000000 >> i));
          set_bit(dst, i, val);
        }
        printf("\n");
        debug_display_float(&src);
        printf("\n");
        debug_display_decimal("", *dst);

        // uint32_t mask = 0x400000; // - mask to set 22nd bit
        // what to do with scale ?
        // set bit - (dst, ?)to set 1 that is default in float between exp bits
        // and mantissa;
      }
    }
    ret = 0;
  }
  return ret;
}