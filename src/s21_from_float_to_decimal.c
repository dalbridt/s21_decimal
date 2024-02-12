#include <stdint.h>

#include "s21_decimal.h"

typedef union {
  int u_int;
  float u_float;
} ftd_union;

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int ret = 1;
  s21_reset(dst);

  if (isinf(src) == 0 && isnan(src) == 0) {
    if (src != 0) {
      int exponent;
      frexp(src, &exponent);
      double temp = fabs(src);
      int scale = 0;
      double pow_2_21 = pow(2, 21);
      while (scale < 28 && temp < pow_2_21) {
        temp *= 10;
        scale++;
      }

      if ((exponent > -94 && exponent < 96)) {
        int sign = signbit(src);
        ftd_union convertor = {0};
        temp = round(temp);
        while (fmod(temp, 10) == 0 && scale > 0) {
          scale--;
          temp /= 10;
        }

        convertor.u_float = temp;
        exponent = ((*(int *)&convertor.u_float & ~MINUS) >> 0x17) - 0x7f;
        dst->bits[exponent / 0x20] |= 1 << exponent % 0x20;

        for (int exp = exponent - 1, j = 22; j >= 0; exp--, j--) {
          if ((convertor.u_int & (1 << j)) != 0) {
            dst->bits[exp / 0x20] |= 1 << exp % 0x20;
          }
        }
        s21_set_scale(dst, scale);
        s21_set_sign(dst, sign);
      }
    }
    ret = 0;
  }
  return ret;
}