#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0; 
  int exp_1 = (value_1.bits[3] & ~0x1FF0000);

  // normalize to get same exponent 

  int ctrl = 0; 
  int mask = 1; 

  for(int arr_idx = 2; arr_idx >= 0; arr_idx--){
    for(int bit_idx = 31; bit_idx >= 0; bit_idx--){
      // add bits by applying mask 
    }
  }

  return flag;
}