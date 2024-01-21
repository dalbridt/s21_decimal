#include <stdio.h>

#include "s21_decimal.h"

#define C_RED "\x1b[31m"
#define C_GREEN "\x1b[32m"
#define C_BLUE "\x1b[34m"
#define C_GREY "\x1b[8m"
#define C_NO "\x1b[0m"

int get_bit(s21_decimal src, int index) {
  int mask = 1u << (index % 32);
  return (src.bits[index / 32] & mask) != 0;
}

/*  index 0 - 31 = bits[0]
    index 32 - 63 = bits[1]
    index 64 - 95 = bits[2]
    index 96 - 127 = bits[3]
*/

void set_bit(s21_decimal* src, int index, int value) {
  int arr_index = index / 32;
  int bit_index = index % 32;
  if (value == 1) {
    src->bits[arr_index] |= (1u << bit_index);
  } else if (value == 0) {
    src->bits[arr_index] &= ~(1u << bit_index);
  }
}

void debug_display_decimal(s21_decimal* src) {
  int* b = &src->bits[0];
  unsigned char byte;

  int sign = get_sign(*src);
  // int exp;
  // float mantissa = frexpf(*src, &exp);

  // float real_float = (sign ? -1 : 1) * mantissa * pow(2.0, exp);

  printf("decimal: is ");
  printf("%s%d%s", C_RED, sign ? -1 : 1, C_NO);
  // printf(" * %s%f%s", C_BLUE, mantissa, C_NO);
  // printf(" * 2^%s%d%s\n", C_GREEN, exp, C_NO);
  printf("\n");

  for (short i = 0; i < 0x80; i++) {
    if (i % 8 == 0) printf(C_NO "[");
    byte = (b[i / 0x20] >> i) & 1;
    printf(C_BLUE);
    if (i / 0x20 == 3) {
      printf(C_GREY);
      if (i > 0x6F && i <= 0x77) printf(C_NO C_GREEN);
      if (i == 0x7F) printf(C_NO C_RED);
    }

    printf("%u" C_NO, byte);
    if (i % 8 == 7) printf(C_NO "] ");
    if (i % 32 == 31) printf("\n");
  }
}

void debug_display_float(float* src) {
  unsigned int* b = (unsigned int*)src;
  unsigned char byte;

  int sign = signbit(*src);
  int exp;
  float mantissa = frexpf(*src, &exp);

  float real_float = (sign ? -1 : 1) * mantissa * pow(2.0, exp);

  printf("float: %f is ", *src);
  printf("%s%d%s", C_RED, sign ? -1 : 1, C_NO);
  printf(" * %s%f%s", C_BLUE, mantissa, C_NO);
  printf(" * 2^%s%d%s", C_GREEN, exp, C_NO);
  printf("\n");

  for (short i = 0; i < 0x20; i++) {
    if (i % 8 == 0) printf(C_NO "[");
    byte = (b[0] >> i) & 1;
    printf(C_BLUE);
    if (i > 0x16 && i < 0x1F) printf(C_NO C_GREEN);
    if (i == 0x1F) printf(C_NO C_RED);

    printf("%u" C_NO, byte);
    if (i % 8 == 7) printf(C_NO "] ");
    if (i % 32 == 31) printf("\n");
  }
}

void reset_decimal(s21_decimal* src) { *src = (s21_decimal){0}; }

int get_sign(s21_decimal num) { return (num.bits[3] & MINUS) != 0; }

void set_sign(s21_decimal* num, int sign_value) {
  int mask = MINUS;
  if (sign_value == 0)
    num->bits[3] &= ~mask;
  else
    num->bits[3] |= mask;
}

int get_scale(s21_decimal num) { return ((SCALE & num.bits[3]) >> 16); }

void set_scale(s21_decimal* num, int scale_value) {
  reset_decimal(num);
  scale_value <<= 16;
  num->bits[3] = num->bits[3] | scale_value;
  if (get_sign(*num)) set_sign(num, 1);
}

void import_to_big_decimal(s21_decimal src, s21_big_decimal* dst) {
  dst->bits[0] = src.bits[0] & MAX4BITE;
  dst->bits[1] = src.bits[1] & MAX4BITE;
  dst->bits[2] = src.bits[2] & MAX4BITE;
}

void import_to_small_decimal(s21_big_decimal src, s21_decimal* dst) {
  dst->bits[0] = src.bits[0] & MAX4BITE;
  dst->bits[1] = src.bits[1] & MAX4BITE;
  dst->bits[2] = src.bits[2] & MAX4BITE;
}

void reset_big_decimal(s21_big_decimal* src) { *src = (s21_big_decimal){0}; }

int decimal_is_zero(s21_decimal src) {
  return src.bits[0] + src.bits[1] + src.bits[2];
}

// int big_decimal_is_zero(s21_big_decimal src) {
//   return src.bits[0] + src.bits[1] + src.bits[2] + src.bits[3] + src.bits[4]
//   +
//          src.bits[5] + src.bits[6] + src.bits[7];
// }

int get_bit_big_decimal(s21_big_decimal src, int index) {
  int mask = 1u << (index % 32);
  return (src.bits[index / 32] & mask) != 0;
}

void set_bit_big_decimal(s21_big_decimal* dst, int index, int bit) {
  int mask = 1u << (index % 32);
  if (bit == 0)
    dst->bits[index / 32] = dst->bits[index / 32] & ~mask;
  else
    dst->bits[index / 32] = dst->bits[index / 32] | mask;
}