#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "s21_decimal.h"

#define SELECTOR 5

float rand_float(int random, float min, float max) {
  srand(random * time(NULL));
  float value = min + ((float)rand() / RAND_MAX) * (max - min);
  return value;
}

int main() {
  // float a = 90, b = 4.555, result, rem;
  // unsigned_divide(a, b, &result, &rem);
  s21_decimal res;
  // 7.922816251426433759354395034
  s21_decimal decimal1 = {{0x00001231, 0x00000000, 0x00000000, 0x00000000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x00232331, 0x00000000, 0x00000000, 0x00030000}};
  // 11.884224377139650639031592551

  // s21_add(decimal1, decimal2, &res);
  debug_display_decimal("dec1", decimal1);
  debug_display_decimal("dec2", decimal2);
  for (int i = 0; i < 1; i++) {
    s21_div(decimal1, decimal2, &res);
    // s21_big_mantissa_shift_l(&big, 1);
    // big2 = big;
    // s21_big_mantissa_shift_l(&big, 2);
    // debug_display_big_decimal("big", big);
    // debug_display_big_decimal("big2", big2);
    // big3 = s21_add_mantissas_big(&big, &big2);
    debug_display_decimal("big", res);
  }

  // printf("%f/%f=%f\n", a, b, result);

  return 0;
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
//     bit = (dividend & MINUS) >> 31;
//     *remainder = (*remainder << 1) | bit;
//     d = dividend;
//     dividend = dividend << 1;
//     num_bits--;
//   }

//   dividend = d;
//   *remainder = *remainder >> 1;
//   num_bits++;

//   for (i = 0; i < num_bits; i++) {
//     bit = (dividend & MINUS) >> 31;
//     *remainder = (*remainder << 1) | bit;
//     t = *remainder - divisor;
//     q = !((t & MINUS) >> 31);
//     dividend = dividend << 1;
//     *quotient = (*quotient << 1) | q;
//     if (q) {
//       *remainder = t;
//     }
//   }
// }