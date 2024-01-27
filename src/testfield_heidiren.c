#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "s21_decimal.h"

#define SELECTOR 5

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

    // b = divu10(b);
    // printf("%llu\n", b);

    // decimal_div10(&dec4);

    // decimal_x10(&dec4);
    // dec4 = add_decimals_mantissa(&dec4, &dec5);
  }
  // decimal_mantissa_shift_l(&dec4, 1);
  // debug_display_decimal("dec4", dec4);

  // int number = 5000;
  // int result = divideBy10(number);

  // printf("%d divided by 10 is %d\n", number, result);

  return 0;
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

unsigned long long divu10(unsigned long long n) {
  unsigned long long q, r;
  q = (n >> 1) + (n >> 2);
  q = q + (q >> 4);
  q = q + (q >> 8);
  q = q + (q >> 16);
  q = q + (q >> 32);
  q = q >> 3;
  r = n - (((q << 2) + q) << 1);
  return q + (r > 9);  // return q+((r+6)>>4);
}

#if FALSE

u_int32_t div10(u_int32_t dividend) {
  u_int64_t invDivisor = 0x1999999A;
  return (u_int32_t)((invDivisor * dividend) >> 32);
}

#endif

return 0;
}