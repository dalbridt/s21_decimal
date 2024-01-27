#include <limits.h>
#include <string.h>
#include <time.h>

#include "s21_decimal.h"

int main() {
  int fail = 0;
  for (int i = 0; i < 100; i++) {
    float fl = rand_float(i, -F_MAX, F_MAX);
    s21_decimal dec, dec_res, dec_int;
    s21_from_float_to_decimal(fl, &dec);
    double res;
    modf(fl, &res);
    s21_from_int_to_decimal((int)res, &dec_int);
    // hui
    s21_truncate(dec, &dec_res);
    if (s21_is_not_equal(dec_int, dec_res)) {
      fail++;
      printf("%d | float: %0.3f | double :%0.3f \n", i, fl, res);
      debug_display_decimal("posle", dec_res);
    }
  }
  printf(("\nfails: %d\n"), fail);
  return 0;
}
