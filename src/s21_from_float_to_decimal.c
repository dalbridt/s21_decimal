#include <stdint.h>

#include "s21_decimal.h"

typedef union {
  int uin_t;
  float floa_t;
} s21_float_bits;

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int ret = 1;
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;

  if (!isinf(src) && !isnan(src)) {
    if (src != 0) {
      int sign = *(int *)&src >> 31;
      int exponent = ((*(int *)&src & ~0x80000000) >> 23) - 127;
      double temp = (double)fabs(src);
      int off = 0;

      while (off < 28 && (int)temp / (int)pow(2, 21) == 0) {
        temp *= 10;
        off++;
      }

      temp = round(temp);

      if (off <= 28 && (exponent > -94 && exponent < 96)) {
        s21_float_bits mantissa = {0};
        temp = (float)temp;

        while (fmod(temp, 10) == 0 && off > 0) {
          off--;
          temp /= 10;
        }

        mantissa.floa_t = temp;
        exponent = ((*(int *)&mantissa.floa_t & ~0x80000000) >> 23) - 127;
        dst->bits[exponent / 32] |= 1 << exponent % 32;

        for (int i = exponent - 1, j = 22; j >= 0; i--, j--)
          if ((mantissa.uin_t & (1 << j)) != 0)
            dst->bits[i / 32] |= 1 << i % 32;

        dst->bits[3] = (sign << 31) | (off << 16);
      }
    }
    ret = 0;
  }
  return ret;
}

// TODO: SPISZHENO