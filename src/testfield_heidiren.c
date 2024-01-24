#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "s21_decimal.h"

#define SELECTOR 4

#define F_MAX 150003232340.253123L

//            79,228,162,514,264,337,593,543,950,335

int divideBy10(int num) {
  // Right shift the bits by 1 (equivalent to dividing by 2)
  int result = num >> 1;

  // Right shift the bits by 3 more positions (equivalent to dividing by 8)
  result >>= 3;

  // Add the two results to get the final division by 10
  result += result >> 1;
  result += result >> 4;
  result += result >> 4;

  return result;
}

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

  system("clear");
  for (int z = 0; z < 10; z++) {
    printf("------ %d ------\n", z);
    float f1 = rand_float(z, -F_MAX, F_MAX);
    float f2 = rand_float(z + 6, -F_MAX, F_MAX);
    // float f2 = -660.448;
    // float f1 = 358.114;
    s21_decimal dec1 = {0};
    s21_decimal dec2 = {0};
    s21_from_float_to_decimal(f1, &dec1);
    s21_from_float_to_decimal(f2, &dec2);

    // debug_display_decimal("dec1", dec1);
    // debug_display_decimal("dec2", dec2);

    s21_decimal res = {0};
    s21_add(dec1, dec2, &res);
    printf("float add: %0.3f + %0.3f = %f\n", f1, f2, (f1 + f2));
    // debug_display_decimal("res", res);
    float flt_res;
    s21_from_decimal_to_float(res, &flt_res);
    printf("\nfloat res: %f\n", flt_res);
    printf("diff: %0.3f\n", flt_res - (f1 + f2));
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

// unsigned long long divu10(unsigned long long n) {
//   unsigned long long q, r;
//   q = (n >> 1) + (n >> 2);
//   q = q + (q >> 4);
//   q = q + (q >> 8);
//   q = q + (q >> 16);
//   q = q + (q >> 32);
//   q = q >> 3;
//   r = n - (((q << 2) + q) << 1);
//   return q + (r > 9);  // return q+((r+6)>>4);
// }

#if FALSE

// u_int32_t div10(u_int32_t dividend) {
//   u_int64_t invDivisor = 0x1999999A;
//   return (u_int32_t)((invDivisor * dividend) >> 32);
// }

#endif
