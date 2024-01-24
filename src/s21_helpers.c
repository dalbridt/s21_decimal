
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

s21_decimal sub_decimals_mantissa(s21_decimal* x, s21_decimal* y) {
  s21_decimal result = *x;
  unsigned int borrow = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t tmp = (uint64_t)x->bits[i] - y->bits[i] - borrow;
    result.bits[i] = (uint32_t)tmp;
    borrow = (tmp >> 32) & 1;  // Extract the borrow for the next iteration
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

void decimal_mantissa_shift_r(s21_decimal* dec, int offset) {
  unsigned int* byte;
  size_t size = sizeof(unsigned int);
  size--;
  size_t basic_size = size;

  switchEndian(dec);

  while (offset--) {
    int carry = 0;
    for (int i = 0; i < 3; ++i) {
      int next = (dec->bits[i] & 1) ? 0x80000000 : 0;
      dec->bits[i] = carry | (dec->bits[i] >> 1);
      carry = next;
    }
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

void decimal_div10(s21_decimal* src) {
  s21_decimal src_copy = *src;
  s21_decimal src_copy2 = *src;

  decimal_mantissa_shift_r(&src_copy, 1);
  decimal_mantissa_shift_r(&src_copy2, 2);
  s21_decimal q = add_decimals_mantissa(&src_copy, &src_copy2);

  for (int i = 4; i < 512; i *= 2) {
    src_copy = q;
    decimal_mantissa_shift_r(&src_copy, i);
    q = add_decimals_mantissa(&q, &src_copy);
  }

  decimal_mantissa_shift_r(&q, 3);

  src_copy2 = q;
  decimal_mantissa_shift_l(&src_copy2, 2);
  src_copy2 = add_decimals_mantissa(&q, &src_copy2);

  decimal_mantissa_shift_l(&src_copy2, 1);

  s21_decimal r = sub_decimals_mantissa(src, &src_copy2);

  q = add_decimals_mantissa(&q, &src_copy);

  if (r.bits[0] >= 0x9) {
    s21_decimal one = {
        .bits[0] = 0b00000000000000000000000000000001,
        .bits[1] = 0b00000000000000000000000000000000,
        .bits[2] = 0b00000000000000000000000000000000,
        .bits[3] = 0b00000000000000000000000000000000,
    };

    q = add_decimals_mantissa(&q, &one);
  }

  *src = q;
}

int s21_mantisa_compare(s21_decimal *value_1, s21_decimal *value_2) {
  int flag = -1;

  for (int i = 2; i >= 0; i--) {
    if (value_1->bits[i] == value_2->bits[i]) {
      continue;
    } else {
      flag = value_1->bits[i] < value_2->bits[i];
      break;
    }
  }
  return flag;
}
