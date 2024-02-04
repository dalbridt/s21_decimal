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
  // ------- MUL ---------
  // int fail = 0;
  // for (int i = 0; i < 100000; i++) {
  //   float f1 = rand_float(i, -F_MAX / 2, F_MAX / 2);
  //   float f2 = rand_float(i, -F_MAX / 2, F_MAX / 2);
  //   float res = f1 * f2;
  //   float conv_res;
  //   s21_decimal dec1, dec2, dec_res;
  //   s21_from_float_to_decimal(f1, &dec1);
  //   s21_from_float_to_decimal(f2, &dec2);
  //   s21_mul(dec1, dec2, &dec_res);
  //   s21_from_decimal_to_float(dec_res, &conv_res);
  //   if (i % 1000 == 0) {
  //     printf("iter # %d\n", i);
  //   }
  //   if (fabs(conv_res - res) > 0.01) {
  //     printf(" f1: %f | f2: %f orig :  %f \n", f1, f2, res);
  //     fail++;
  //   }
  // }
  // printf(("\nfails: %d\n"), fail);

  // --------- DIV ------------
  int fail = 0;
  int i = 0;
  for (; i < 100; i++) {
    float f1 = rand_float(i + 5, -F_MAX / 200000, F_MAX / 200000);
    float f2 = rand_float(i, -F_MAX / 200000, F_MAX / 200000);
    float res = f1 / f2;
    float conv_res;
    s21_decimal dec1, dec2, dec_res;
    s21_from_float_to_decimal(f1, &dec1);
    s21_from_float_to_decimal(f2, &dec2);
    s21_div(dec1, dec2, &dec_res);
    s21_from_decimal_to_float(dec_res, &conv_res);
    // if (i % 1000 == 0) {
    //   printf("iter # %d\n", i);
    // }
    if (fabs(conv_res - res) > 0.01) {
      printf(
          " f1: %6.6f | f2: %6.6f orig :  %6.6f  || conv_res: %6.6f || delta: "
          "%6.6f\n",
          f1, f2, res, conv_res, fabs(conv_res / 10 - res));
      fail++;
    }
  }
  printf(("\ntotal amount of tests: %d \nfails: %d\n"), i, fail);

  return 0;
}
