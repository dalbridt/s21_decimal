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
  // -7922816251426433759.3543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
  // -7922816251426433760
  s21_decimal decimal_check = {{0x5EF6EAE0, 0x6DF37F67, 0x0, 0x80000000}};
  s21_decimal result;

  s21_floor(decimal, &result);

  debug_display_decimal("decimal_check", decimal_check);
  debug_display_decimal("result", result);

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