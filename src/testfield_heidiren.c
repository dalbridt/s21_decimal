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
  // -1.0
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x80010000}};
  // -1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x80010000}};
  // 0.0000000000000000000000000007
  s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x1C0000}};
  s21_decimal result;
  s21_div(decimal1, decimal2, &result);

  debug_display_decimal("decimal1", decimal1);
  debug_display_decimal("decimal2", decimal2);

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