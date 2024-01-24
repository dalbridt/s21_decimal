#include <stdio.h>

#include "s21_decimal.h"

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

void reset_decimal(s21_decimal* src) { *src = (s21_decimal){0}; }

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
  return (src.bits[0] + src.bits[1] + src.bits[2]) == 0;
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

void max_decimal(s21_decimal* dst) {
  dst->bits[0] = 0b11111111111111111111111111111111;
  dst->bits[1] = 0b11111111111111111111111111111111;
  dst->bits[2] = 0b11111111111111111111111111111111;
  dst->bits[3] = 0b00000000000111000000000000000000;
}

void min_decimal(s21_decimal* dst) {
  dst->bits[0] = 0b11111111111111111111111111111111;
  dst->bits[1] = 0b11111111111111111111111111111111;
  dst->bits[2] = 0b11111111111111111111111111111111;
  dst->bits[3] = 0b10000000000111000000000000000000;
}

#if FALSE

u_int32_t div10(u_int32_t dividend) {
  u_int64_t invDivisor = 0x1999999A;
  return (u_int32_t)((invDivisor * dividend) >> 32);
}

unsigned long long divu10(unsigned long long n) {
  unsigned long long q, r;
  q = (n >> 1) + (n >> 2);
  q = q + (q >> 4);
  q = q + (q >> 8);
  q = q + (q >> 16);
  q = q >> 3;
  r = n - (((q << 2) + q) << 1);
  return q + (r > 9);  // return q+((r+6)>>4);
}

#endif

float rand_float(int random, float min, float max) {
  srand(random * time(NULL));
  float value = min + ((float)rand() / RAND_MAX) * (max - min);
  return value;
}