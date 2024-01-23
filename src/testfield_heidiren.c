#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "s21_decimal.h"

#define SELECTOR 2

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
  // max_decimal(&dst);
  system("clear");
  printf("\n");
  // debug_display_float(&f);
  // printf("\n");

  // s21_decimal dec1, dec2;

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
      .bits[0] = 0b00000000000000000000000000000001,
      .bits[1] = 0b00000000000000000000000000000000,
      .bits[2] = 0b00000000000000000000000000000000,
      .bits[3] = 0b00000000000000000000000000000000,
  };
  for (int i = 0; i < 28; i++) {
    debug_display_decimal("dec4", &dec4);

    decimal_x10(&dec4);
  }

#endif

  // printf("divided int %u", div10(abc));

  // equalize_scale(&dec1, 1);
  // equalize_scale(&dec2, 1);
  // printf("\n");

  // debug_display_decimal("dec3", &dec3);

  // printf("are dec1 and dec2 equal? - %s\n",
  //        (s21_is_equal(dec1, dec2) == 1) ? "yes" : "no");

  return 0;
}
