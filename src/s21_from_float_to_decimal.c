#include <stdint.h>

#include "s21_decimal.h"

typedef union {
  int u_int;
  float u_float;
} ftd_union;

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int ret = 1;
  reset_decimal(dst);

  if (!isinf(src) && !isnan(src)) {
    if (src != 0) {
      int exponent, sign = signbit(src);
      frexp(src, &exponent);
      double temp = fabs(src);
      int scale = 0;
      double pow_2_21 = pow(2, 21);
      while (scale < 28 && temp < pow_2_21) {
        temp *= 10;
        scale++;
      }

      if ((exponent > -94 && exponent < 96)) {
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
        dst->bits[3] = (sign << 0x1f) | (scale << 0x10);
      }
    }
    ret = 0;
  }
  return ret;
}

// TODO: SPISZHENO

/*

typedef union {
  int u_int;
  float u_float;
} ftd_union;

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int flag = 1;
  reset_decimal(dst);

  if (!isinf(src) && !isnan(src)) {
    flag = 0;
    if (src != 0) {
      int exponent, sign = signbit(src);
      frexp(src, &exponent);

      if (exponent > -94 && exponent < 96) {
        double temp = fabs(src);
        int scale = 0;

        double pow_2_21 = pow(2, 21);
        while (scale < 28 && temp < pow_2_21) {
          temp *= 10;
          scale++;
        }

        ftd_union convertor = {0};

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
        dst->bits[3] = (sign << 0x1f) | (scale << 0x10);

      } else {
        flag = 1;
      }
    }
  }
  return flag;
}
*/