#include "s21_decimal.h"

int main() {
  // ---------testing convertr from and to int ----------------
  // for (int i = -2147483647; i < 2147483647; i++) {
  //   s21_decimal num;
  //   int check = 0;
  //   s21_from_int_to_decimal(i, &num);
  //   s21_from_decimal_to_int(num, &check);
  //   if (check != i) {
  //     printf("number %d is not processed correctly", i);
  //   }
  // }
  // ---------- Working on ADD ALGO  --------------

  // s21_decimal num1;
  // num1.bits[0] = 0b00000001010000000000000000000000;
  // num1.bits[1] = 0b00000000000000000000000000000000;
  // num1.bits[2] = 0b00000000000000000000000000000000;
  // num1.bits[3] = 0b00000000000010110000000000000000;

  // debug_display_decimal("", num1);

  // printf("\n ------ \n ");

  // s21_decimal num2;
  // num2.bits[0] = 0b00000000001000000000000000000000;
  // num2.bits[1] = 0b00000000000000000000000000000000;
  // num2.bits[2] = 0b00000000000000000000000000000000;
  // num2.bits[3] = 0b00000000000010100000000000000000;

  // equalize_scale(&num1, 10);

  // float res;

  // s21_from_decimal_to_float(num, &res);

  // printf("FLOAT: %f", res);

  // int src = 0b10000000011111111100000000011111;
  // for(int i = 0; i < 32; i++){
  // //printf("get bit check (index %d): %d", index, get_bit(src, index))
  // printf("%d", get_bit(src, i));
  // }

  // --------------- TESTING BITWISE PRINT ------------------
  // float f = 1;

  // // printf("\nfloat\n");

  // // debug_display_float(&f);

  // s21_decimal dst;
  // // reset_decimal(&dst);
  // // printf("\ndecimal\n");
  // // // s21_from_float_to_decimal(f, &dst);
  // dst.bits[0] = 0b00100000001000000001000000100000;
  // dst.bits[1] = 0b00000000000000000000000000000000;
  // dst.bits[2] = 0b00000000000000000000000000000000;
  // dst.bits[3] = 0b10000000000111010000000000000000;

  // debug_display_decimal(&dst);
  // printf("\n");

  // //   for (uint32_t mask = 0x80000000; mask; mask >>= 1) {
  // //     printf("%d", !!(num.bits[3] & mask));
  // //   }
  // //   printf("\n");

  // --------------- TESTING fukin Dec to float conversion ------------------

  // s21_from_decimal_to_float(dst, &f);
  // printf("converted: \n");
  // debug_display_float(&f);
  // printf("\n%f\n", f);

  // ---------- TESTING FROM FLOAT TO DECIMAL CONVERSION ------------------

  float f = 1.605;

  s21_decimal dst = (s21_decimal){0};

  s21_from_float_to_decimal(f, &dst);
  printf("_______________\n\n");
  debug_display_decimal("i", dst); 


  // --------------- TESTING SET BIT  ---------------------
  // s21_decimal num = (s21_decimal){0};
  // for (int i = 0; i < 128; i++) {
  //   set_bit(&num, i, 1);
  // }
  // printf("\nsetbit check :\n");
  // for (int i = 0; i < 4; i++) {
  //   for (uint32_t mask = 0x80000000; mask; mask >>= 1) {
  //     printf("%d", !!(num.bits[i] & mask));
  //   }
  //   printf("\n");
  // }
  // for(int i = 112; i < 120; i++){
  //   set_bit(&num, i, 0);
  // }
  // printf("\nsetbit check - 2 :\n");
  // for (int i = 0; i < 4; i++) {
  //   for (uint32_t mask = 0x80000000; mask; mask >>= 1) {
  //     printf("%d", !!(num.bits[i] & mask));
  //   }
  //   printf("\n");
  // }
  // ---- trying to convert binary float ---------
  // - мб конвертировать флот / децимал используя операции с децималом
  // (используя этот алгоритм)!!!!
  // float f = 15.3; uint32_t f_bits = *(uint32_t*)&f;
  //  for (uint32_t mask = 0x80000000; mask; mask >>= 1) {
  //     printf("%d", !!(f_bits & mask));
  //   }
  //   printf("\n");
  // float result = 1;
  // int i = -1;

  // for (uint32_t mask = 0x400000; mask; mask >>= 1) {
  //   int bit = !!(f_bits & mask);
  //   printf("%d", bit);
  //   result += bit * pow(2, i);
  //   i--;
  // }
  // printf("\n");
  // printf("mantissa: %f\n", result);
  // int exponent = ((f_bits & ~0x80000000) >> 23) - 127;
  // float exp = pow(2, exponent);
  // float res = result * exp;

  // printf("%f", res);

  // mantissa i need to get : 7665091
  return 0;
}
