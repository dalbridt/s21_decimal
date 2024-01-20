#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  double temp = (double)*dst;

  for (int i = 0; i < 96; i++) {
    temp += get_bit(src, i) * pow(2, i);
  }
  int scale = 0x0000FF00 & src.bits[3] >> 16;
  temp = temp * pow(10, -scale);
   *dst = temp; 
  if(get_bit(src, 127)){
    *dst *= -1;
  }
  return 0;
}