#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst);
int find_bit(s21_decimal src, int index);
int s21_from_float_to_decimal(float src, s21_decimal *dst);

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
  // printf("ya conchil");
  // ---------------------------------------------------------------------

  // s21_decimal num;
  // num.bits[0] = 0b00000000001000000000000000000000;
  // num.bits[1] = 0b00000000000000000000000000000000;
  // num.bits[2] = 0b00000000000000000000000000000000;
  // num.bits[3] = 0b1000000001111111110000000000000;

  // float res;

  // s21_from_decimal_to_float(num, &res);

  // printf("FLOAT: %f", res);

  // int src = 0b10000000011111111100000000011111;
  // for(int i = 0; i < 32; i++){
  // //printf("get bit check (index %d): %d", index, get_bit(src, index))
  // printf("%d", get_bit(src, i));
  // }

  // --------------- TESTING BITWISE PRINT ------------------
  float f = 0.15625;
  uint32_t fbits = *(uint32_t*)&f;

  printf("bitwise check :\n");
  for(uint32_t mask = 0x80000000; mask; mask >>=1){
    printf("%d", !!(fbits & mask));
  }

  s21_decimal dst;
  printf("\nfunction check :\n");
  s21_from_float_to_decimal(f, &dst);
  // -------------------------------------------------------

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
  // -------------------------------------------------------

  return 0;
}
