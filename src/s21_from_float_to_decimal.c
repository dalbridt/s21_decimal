#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int ret = 1;
  if (!isinf(src) && !isnan(src) && dst != NULL) {
    *dst = (s21_decimal){0};
    if (src != 0) {
      uint32_t src_bits =
          *(uint32_t *)&src;  // to get aka int but with the same bits order

      int sign = (src_bits >> 31) & 1;
      src *=sign ? -1:1;
      int exponent = ((src_bits & ~0x80000000) >> 23) - 127;

      if (exponent > -95 && exponent < 95) {
        int scale = 0;
        char num[50];
        sprintf(num, "%f", src);
        char *whole = strtok(num, ".");
        double integr; 
        for (int i = strlen(whole);i < 8; src *= 10, scale++, i++){
          if(modf(src, &integr) == 0){
            break; 
          }
        }
        int sr = (int)src;
        dst->bits[0] = sr & MAX4BITE; 
        set_scale(dst, scale);
        set_sign(dst, sign);
      }
        }
    ret = 0;
  }
  return ret;
}