#include <limits.h>
#include <string.h>
#include <time.h>

#include "s21_decimal.h"
float rand_float(int random, float min, float max) {
  srand(random * time(NULL));
  float value = min + ((float)rand() / RAND_MAX) * (max - min);
  return value;
}

int main() {
  // int fail = 0;
  // for (int i = 0; i < 1000000; i++) {
  //   float fl = rand_float(i, -F_MAX, F_MAX);
  //   float fl_r = floor(fl);
  //   s21_decimal dec, dec_rnd, dec_res;
  //   s21_from_float_to_decimal(fl, &dec);
  //   s21_from_float_to_decimal(fl_r, &dec_rnd);
  //   s21_floor(dec, &dec_res);

  //   if (s21_is_not_equal(dec_rnd, dec_res)) {
  //     fail++;
  //     printf(" orig float:  %f | build-in round: %f  \n", fl, fl_r);
  //     debug_display_decimal("dec round", dec_res);
  //   }
  // }
  // printf(("\nfails: %d\n"), fail);
  int fail = 0;
  for (int i = 0; i < 100; i++) {
    float f1 = rand_float(i, -F_MAX, F_MAX);
    float f2 = rand_float(i, -F_MAX, F_MAX);
    float res = f1 * f2;
    float conv_res;
    s21_decimal dec1;
    s21_decimal dec2;
    s21_decimal dec_res;
    s21_from_float_to_decimal(f1, &dec1);
    s21_from_float_to_decimal(f2, &dec2);
    s21_mul(dec1, dec2, &dec_res);
    s21_from_decimal_to_float(dec_res, &conv_res);
    if (fabs(conv_res - res) > 0.01) {
      printf(" orig :  %f \n", res);
      debug_display_decimal("", dec_res);
      fail++;
    }
  }
  printf(("\nfails: %d\n"), fail);
  return 0;
}
