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
  // int fail = 0;
  // float range = 1301230.03123;
  // int i = 0;
  // for (; i < 1000; i++) {
  //   float f1 = rand_float(i + 5, -range, range);
  //   float f2 = rand_float(i, -range, range);
  //   float res = f1 / f2;
  //   float conv_res;
  //   s21_decimal dec1, dec2, dec_res;
  //   s21_from_float_to_decimal(f1, &dec1);
  //   s21_from_float_to_decimal(f2, &dec2);
  //   s21_div(dec1, dec2, &dec_res);
  //   s21_from_decimal_to_float(dec_res, &conv_res);
  //   // if (i % 1000 == 0) {
  //   //   printf("iter # %d\n", i);
  //   // }
  //   if (fabs(conv_res - res) > 0.01) {
  //     printf("%0.3f/%0.3f=%0.8f =? %0.8f || delta: %0.8f\n", f1, f2, res,
  //            conv_res, fabs(conv_res - res));
  //     fail++;
  //   }
  // }
  // printf(("\ntotal amount of tests: %d \nfails: %d\n"), i, fail);

  // s21_decimal dec1 = {{0x80000000, 0x0, 0x0, 0x80000000}};
  // s21_decimal dec2 = {{0x0, 0x32, 0x0, 0x80020000}}; 
  // s21_decimal dec3 = {{0xFFFFFFFF, 0x0, 0x0, 0x0}}; 
  // debug_display_decimal("1", dec1);
  // debug_display_decimal("2", dec2);
  // debug_display_decimal("3", dec3);
  // int x; 
  // int ctrl = 0x80000000; 
  // printf("convert code: %d || number: %d\n", s21_from_decimal_to_int(decimal, &x), x); 
  // printf("ctrl: %d", ctrl);
  
 //  s21_decimal decimal = {{0x0, 0x32, 0x0, 0x80020000}}; 
  
  // debug_display_decimal("2", decimal);
  // s21_div10(&decimal, 0);  
  // debug_display_decimal("1", decimal);
  // s21_div10(&decimal, 0); 
  // s21_set_scale(&decimal, 0); 
  // debug_display_decimal("", decimal);
  int max = 0x7fffffff; 
  int min = ~0x7fffffff; 
  printf("max: %d | min %d", max, min); 
  return 0;
}
