#include <limits.h>
#include <string.h>
#include <time.h>

#include "s21_decimal.h"

int main() {
  // ---- TESTING FLOAT CONVERSION ------
  // system("clear");
  // for (int z = 0; z < 10; z++) {
  //   printf("------ %d ------\n", z);
  //   float f1 = rand_float(z, -1000, 1000);
  //   float f2 = rand_float(z + 6, -1000, 1000);
  //   // float f2 = -660.448;
  //   // float f1 = 358.114;
  //   s21_decimal dec1 = {0};
  //   s21_decimal dec2 = {0};
  //   s21_from_float_to_decimal(f1, &dec1);
  //   s21_from_float_to_decimal(f2, &dec2);

  //   // debug_display_decimal("dec1", dec1);
  //   // debug_display_decimal("dec2", dec2);

  //   s21_decimal res = {0};
  //   s21_add(dec1, dec2, &res);
  //   printf("float add: %0.3f + %0.3f = %f\n", f1, f2, (f1 + f2));
  //   // debug_display_decimal("res", res);
  //   float flt_res;
  //   s21_from_decimal_to_float(res, &flt_res);
  //   printf("\nfloat res: %f\n", flt_res);
  //   printf("diff: %0.3f\n", flt_res - (f1 + f2));
  // }
  // ------------------------------------------
  // ------- TESTING INT CONVERSION --------

  // srand((unsigned)time(NULL));

  // for (int i = 0; i < 10; i++) {
  //   int val, val_res;
  //   s21_decimal dec_res = {0};
  //   val = rand();  //% (10000000 - (-10000000) + 1)) + (-10000000);
  //   if (i % 2 == 0) {
  //     val *= -1;
  //   }

  //   s21_from_int_to_decimal(val, &dec_res);
  //   char name[50];
  //   sprintf(name, "%d", val);
  //   // debug_display_decimal(name, dec_res);
  //   s21_from_decimal_to_int(dec_res, &val_res);
  //   printf("assertion: %d | orig: %d  |  after: %d \n", (val - val_res), val,
  //          val_res);
  // }

  // ------------------------------------------
  // ------- TESTING IS GREATER FUNC --------

  // float val1 = 23.15;
  // float val2 = 4.5678;
  // s21_decimal dec_1 = {0};
  // s21_decimal dec_2 = {0};
  // s21_from_float_to_decimal(val1, &dec_1);
  // s21_from_float_to_decimal(val2, &dec_2);
  // debug_display_decimal("dec1",dec_1);
  // debug_display_decimal("dec2",dec_2);
  // printf("%d |val1: %6f |val2: %6f\n", s21_is_greater(dec_1, dec_2), val1,
  // val2);

  // for (int i = 0; i < 5; i++) {
  //   float val1 = i * ((float)rand() / RAND_MAX);
  //   float val2 = i * ((float)rand() / RAND_MAX);
  //   s21_decimal dec_1 = {0};
  //   s21_decimal dec_2 = {0};
  //   s21_from_float_to_decimal(val1, &dec_1);
  //   s21_from_float_to_decimal(val2, &dec_2);
  //   printf("%d |val1: %6f |val2: %6f\n", s21_is_greater(dec_1, dec_2), val1,
  //   val2);
  // }

  // for (int i = 0; i < 5; i++) {
  //   int val, val2;
  //   s21_decimal dec_1 = {0};
  //   s21_decimal dec_2 = {0};
  //   val = (rand() % (100 - (-100) + 1)) + (-100);
  //   val2 = (rand() % (100 - (-100) + 1)) + (-100);
  //   // if (i % 2 == 0) {
  //   //   val *= -1;
  //   // }
  //   s21_from_int_to_decimal(val, &dec_1);
  //   s21_from_int_to_decimal(val2, &dec_2);
  //   printf("%d |val1: %5d |val2: %5d\n", s21_is_greater(dec_1, dec_2), val,
  //   val2);
  // }

  // ------------------------------------------
  // ------- TESTING IS not equal FUNC --------
  float val1 = 512;
  float val2 = 512;
  s21_decimal dec_1 = {0};
  s21_decimal dec_2 = {0};
  s21_from_float_to_decimal(val1, &dec_1);
  s21_from_float_to_decimal(val2, &dec_2);
  //debug_display_decimal("dec1", dec_1);
  //debug_display_decimal("dec2", dec_2);
  printf("%d |val1: %6f |val2: %6f\n", s21_is_not_equal(dec_1, dec_2), val1,
         val2);
  return 0;
}
