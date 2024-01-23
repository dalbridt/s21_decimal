
#include "s21_decimal.h"

s21_decimal add_decimals_mantissa(s21_decimal* x, s21_decimal* y) {
  s21_decimal result = *x;
  unsigned int carry = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t tmp = (uint64_t)x->bits[i] + y->bits[i] + carry;
    result.bits[i] = (uint32_t)tmp;
    carry = tmp >> 32;
  }
  return result;
}

void decimal_mantissa_shift_l(s21_decimal* dec, int offset) {
  unsigned int* byte;
  size_t size = sizeof(unsigned int);
  size--;
  size_t basic_size = size;

  switchEndian(dec);

  for (int i = 0; i < offset; i++) {
    for (byte = dec->bits; basic_size--; ++byte) {
      unsigned int bit = 0;
      if (basic_size) {
        bit = (byte[1] & (1 << (32 - 1))) ? 1 : 0;
      }
      *byte <<= 1;
      *byte |= bit;
    }
    basic_size = size;
  }

  switchEndian(dec);
}

void switchEndian(s21_decimal* x) {
  unsigned int temp0 = x->bits[0];
  unsigned int temp2 = x->bits[2];
  x->bits[0] = temp2;
  x->bits[2] = temp0;
}

void decimal_x10(s21_decimal* src) {
  s21_decimal dec3 = *src;
  s21_decimal dec2 = *src;

  decimal_mantissa_shift_l(&dec3, 3);
  decimal_mantissa_shift_l(&dec2, 1);

  *src = add_decimals_mantissa(&dec2, &dec3);
}