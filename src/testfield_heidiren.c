#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "s21_decimal.h"

#define SELECTOR 4

int main() {
  s21_decimal dec1 = {
      .bits[0] = 0b01010101010101010101010101010101,
      .bits[1] = 0b00000000000000000000000000000000,
      .bits[2] = 0b00000000000000000000000000000000,
      .bits[3] = 0b00000000000000000000000000000000,
  };

  s21_decimal dec3;

#if (SELECTOR == 0)

  float f = 32.02234;

  s21_decimal dst;

  system("clear");
  printf("\n");

  debug_display_decimal("dec1", &dec1);

  debug_display_decimal("dec2", &dec2);

  dec3 = add_decimal_beta(&dec1, &dec2);

  debug_display_decimal("dec3", &dec3);

#elif (SELECTOR == 1)
  for (int i = 0; i < 10; i++) {
    debug_display_decimal("dec1", &dec1);

    decimal_mantissa_shift_l(&dec1, 1);

    debug_display_decimal("dec3", &dec1);
  }

#elif (SELECTOR == 2)

  s21_decimal dec4 = {
      .bits[0] = 0b00010000000000000000000000000000,
      .bits[1] = 0b00111110001001010000001001100001,
      .bits[2] = 0b00100000010011111100111001011110,
      .bits[3] = 0b00000000000000000000000000000000,
  };

  s21_decimal dec5 = {
      .bits[0] = 0b00000000000000000000000000000001,
      .bits[1] = 0b00000000000000000000000000000000,
      .bits[2] = 0b00000000000000000000000000000000,
      .bits[3] = 0b00000000000000000000000000000000,
  };

  unsigned long long b = 1000000000000000000;
  for (int i = 0; i < 30; i++) {
    debug_display_decimal("dec4", dec4);

    decimal_div10(&dec4);
  }

#elif (SELECTOR == 4)

  for (int z = 0; z < 3; z++) {
    float f1 = rand_float(z, -F_MAX, F_MAX);
    float f2 = rand_float(z + 6, -F_MAX, F_MAX);

    s21_decimal dec1 = {0};
    s21_decimal dec2 = {0};
    s21_from_float_to_decimal(f1, &dec1);
    s21_from_float_to_decimal(f2, &dec2);

    // debug_display_decimal("dec1", dec1);
    // debug_display_decimal("dec2", dec2);

    s21_decimal res = {0};
    s21_add(dec1, dec2, &res);
    float flt_res;
    s21_from_decimal_to_float(res, &flt_res);
    printf("%0.3f + %0.3f = %0.3f \nshould be %0.3f\n", f1, f2, flt_res,
           (f1 + f2));
  }

#endif

  return 0;
}