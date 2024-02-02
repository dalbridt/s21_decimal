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
  // ------- BIG DECIMAL ---------
  // int fail = 0;
  // for (int i = 0; i < 100; i++) {
  //   float fl = rand_float(i, -F_MAX, F_MAX);
  //   float fl_res;
  //   s21_decimal dec;
  //   s21_big_decimal big_dec = {0};
  //   printf("orig float %f\n", fl);
  //   s21_from_float_to_decimal(fl, &dec);
  //   debug_display_decimal("before", dec);

  //   import_to_big_decimal(dec, &big_dec);
  //   debug_display_big_decimal("big", big_dec);
  //   reset_decimal(&dec);
  //   import_to_small_decimal(big_dec, &dec);
  //   debug_display_decimal("after", dec);
  //   s21_from_decimal_to_float(dec, &fl_res);
  //   if (fabs(fl - fl_res) > 0.001) {
  //     printf("orig : %f | conversion res: %f\n", fl, fl_res);
  //     fail++;
  //   }
  // }
  // printf("big dec conversion fails: %d", fail);

  // ------- OCHHEN BIG DECIMAL ---------
  s21_big_decimal very = {
      .bits[0] = 0b11111111101100011101101011111111101100011101101011111000,
      .bits[1] = 0b00000000000000000000000000000000000000000000000000000000,
      .bits[2] = 0b00000000000000000000000000000000000000000000000000000000,
      .bits[3] = 0b00000000000000000000000000000000000000000000000000000000,
      .bits[4] = 0b00000000000000000000000000000000000000000000000000000000,
      .bits[5] = 0b00000000000000000000000000000000000000000000000000000000,
      .bits[6] = 0b00000000000000000000000000000000000000000000000000000000,
      .scale = 0b00000000000001000000000000000000,
  };
  debug_display_big_decimal("before", very);
  for (int i = 0; i < 10; i++) {
    big_decimal_div10(&very);
    debug_display_big_decimal("", very);
  }
  // s21_decimal dec1;
  // import_to_small_decimal(very, &dec1);
  // debug_display_decimal("after", dec1);

  // ------- MUL ---------
  // int fail = 0;
  // for (int i = 0; i < 10; i++) {
  //   float f1 = rand_float(i, -F_MAX, F_MAX);  // 123456.789;
  //   float f2 = rand_float(i, -F_MAX, F_MAX);  // 986754.321;
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

  return 0;
}
