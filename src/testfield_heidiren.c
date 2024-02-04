#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "s21_decimal.h"

void unsigned_divide(unsigned int dividend, unsigned int divisor,
                     unsigned int *quotient, unsigned int *remainder);

void divide_dec(s21_decimal dividend, s21_decimal divisor,
                s21_decimal *quotient, s21_decimal *remainder);

#define SELECTOR 5

float rand_float(int random, float min, float max) {
  srand(random * time(NULL));
  float value = min + ((float)rand() / RAND_MAX) * (max - min);
  return value;
}

int main() {
  float a = 90, b = 4.555, result, rem;

  // unsigned_divide(a, b, &result, &rem);

  s21_decimal dec_a, dec_b, dec_result, dec_rem;

  s21_from_float_to_decimal(a, &dec_a);
  s21_from_float_to_decimal(b, &dec_b);

  divide_dec(dec_a, dec_b, &dec_result, &dec_rem);

  s21_from_decimal_to_float(dec_result, &result);
  s21_from_decimal_to_float(dec_rem, &rem);

  printf("%f/%f=%f, rem %f\n", a, b, result, rem);

  return 0;
}

void divide_dec(s21_decimal dividend, s21_decimal divisor,
                s21_decimal *quotient, s21_decimal *remainder) {
  int num_bits;
  int q, bit;
  int i;

  equalize_scale(&dividend, &divisor);

  s21_decimal d, t;

  reset_decimal(remainder);
  reset_decimal(quotient);

  if (decimal_is_zero(divisor)) return;

  if (s21_is_greater(divisor, dividend)) {
    *remainder = dividend;
    return;
  }

  if (s21_is_equal(divisor, dividend)) {
    decimal_one(quotient);
    return;
  }

  num_bits = 96;

  while (s21_is_less(*remainder, divisor) && num_bits > 0) {
    bit = get_bit(dividend, 95);
    decimal_mantissa_shift_l(remainder, 1);
    if (bit) set_bit(remainder, 0, bit);

    d = dividend;
    decimal_mantissa_shift_l(&dividend, 1);

    num_bits--;
  }

  dividend = d;
  decimal_mantissa_shift_r(remainder, 1);
  num_bits++;

  for (i = 0; i < num_bits; i++) {
    bit = get_bit(dividend, 95);
    decimal_mantissa_shift_l(remainder, 1);
    if (bit) set_bit(remainder, 0, bit);

    t = sub_decimals_mantissa(remainder, &divisor);

    q = !get_bit(t, 95);

    decimal_mantissa_shift_l(&dividend, 1);
    decimal_mantissa_shift_l(quotient, 1);
    if (q) set_bit(quotient, 0, q);

    if (q) {
      *remainder = t;
    }
  }
}

// void unsigned_divide(unsigned int dividend, unsigned int divisor,
//                      unsigned int *quotient, unsigned int *remainder) {
//   unsigned int t, num_bits;
//   unsigned int q, bit, d;
//   int i;

//   *remainder = 0;
//   *quotient = 0;

//   if (divisor == 0) return;

//   if (divisor > dividend) {
//     *remainder = dividend;
//     return;
//   }

//   if (divisor == dividend) {
//     *quotient = 1;
//     return;
//   }

//   num_bits = 32;

//   while (*remainder < divisor) {
//     bit = (dividend & 0x80000000) >> 31;
//     *remainder = (*remainder << 1) | bit;
//     d = dividend;
//     dividend = dividend << 1;
//     num_bits--;
//   }

//   dividend = d;
//   *remainder = *remainder >> 1;
//   num_bits++;

//   for (i = 0; i < num_bits; i++) {
//     bit = (dividend & 0x80000000) >> 31;
//     *remainder = (*remainder << 1) | bit;
//     t = *remainder - divisor;
//     q = !((t & 0x80000000) >> 31);
//     dividend = dividend << 1;
//     *quotient = (*quotient << 1) | q;
//     if (q) {
//       *remainder = t;
//     }
//   }
// }