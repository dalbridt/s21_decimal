#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int ret = 1;
  *dst = (s21_decimal){0};
  // if (!isinf(src) && !isnan(src)) if !(src == 0) - add check

  uint32_t src_bits = *(uint32_t *)&src;

  int sign = (src_bits >> 31) & 1;
  int exponent = ((src_bits & ~0x80000000) >> 23) -127;  // 0х - assume as 16 and only left bit is set
  int raw_mantissa = src_bits & 0x7FFFFF;

  double norm_mantissa = 1.0 + raw_mantissa / pow(2, 23);  // normalize mantissa
    printf("\nexponent %d : \n", exponent);
  for (uint32_t mask = 0x80000000; mask; mask >>= 1) {
    printf("%d", !!(exponent & mask));
  }
  printf("\nmantissa %d : \n", raw_mantissa);
   for (uint32_t mask = 0x80000000; mask; mask >>= 1) {
    printf("%d", !!(raw_mantissa & mask));
  }

  return ret;
}