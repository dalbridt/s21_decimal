#include <limits.h>
#include <string.h>
#include <time.h>

#include "s21_decimal.h"

int main() {
  int fail = 0;
  for (int i = 0; i < 1000000; i++) {
    float fl = rand_float(i, -F_MAX, F_MAX);
    float fl_r = floor(fl);
    s21_decimal dec, dec_rnd, dec_res;
    s21_from_float_to_decimal(fl, &dec);
    s21_from_float_to_decimal(fl_r, &dec_rnd);
    s21_floor(dec, &dec_res);

    if (s21_is_not_equal(dec_rnd, dec_res)) {
      fail++;
      printf(" orig float:  %f | build-in round: %f  \n", fl, fl_r);
      debug_display_decimal("dec round", dec_res);
    }
  }
  printf(("\nfails: %d\n"), fail);
  return 0;
}
