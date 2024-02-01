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
  int fail = 0;
  for (int i = 0; i < 10; i++) {
    float fl = rand_float(i, -F_MAX, F_MAX);
    float fl_res;
    s21_decimal dec;
    s21_big_decimal big_dec;
    s21_from_float_to_decimal(fl, &dec);
    // debug_display_decimal("before", dec);
    import_to_big_decimal(dec, &big_dec);
    reset_decimal(&dec);
    import_to_small_decimal(big_dec, &dec);
    s21_from_decimal_to_float(dec, &fl_res);
    // debug_display_decimal("after", dec);
    if (fabs(fl - fl_res) > 0.00001) {
      printf("orig : %f | conversion res: %f\n", fl, fl_res);
      fail++;
    }
  }
  printf("big dec conversion fails: %d", fail);

  // int fail = 0;
  // for (int i = 0; i < 10; i++) {
  //   float f1 = rand_float(i, -F_MAX, F_MAX);
  //   float f2 = rand_float(i, -F_MAX, F_MAX);
  //   float res = f1 * f2;
  //   float conv_res;
  //   s21_decimal dec1;
  //   s21_decimal dec2;
  //   s21_decimal dec_res;
  //   s21_from_float_to_decimal(f1, &dec1);
  //   s21_from_float_to_decimal(f2, &dec2);
  //   s21_mul(dec1, dec2, &dec_res);
  //   s21_from_decimal_to_float(dec_res, &conv_res);
  //   if (fabs(conv_res - res) > 0.01) {
  //     printf(" orig :  %f \n", res);
  //     debug_display_decimal("", dec_res);
  //     fail++;
  //   }
  // }
  // printf(("\nfails: %d\n"), fail);
  // return 0;
}
