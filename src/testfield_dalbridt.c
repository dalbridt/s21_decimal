#include <limits.h>
#include <time.h>

#include "s21_decimal.h"

int main() {
  system("clear");
  for (int z = 0; z < 10; z++) {
    printf("------ %d ------\n", z);
    float f1 = rand_float(z, -1000, 1000);
    float f2 = rand_float(z + 6, -1000, 1000);
    // float f2 = -660.448;
    // float f1 = 358.114;
    s21_decimal dec1 = {0};
    s21_decimal dec2 = {0};
    s21_from_float_to_decimal(f1, &dec1);
    s21_from_float_to_decimal(f2, &dec2);

    // debug_display_decimal("dec1", dec1);
    // debug_display_decimal("dec2", dec2);

    s21_decimal res = {0};
    s21_add(dec1, dec2, &res);
    printf("float add: %0.3f + %0.3f = %f\n", f1, f2, (f1 + f2));
    // debug_display_decimal("res", res);
    float flt_res;
    s21_from_decimal_to_float(res, &flt_res);
    printf("\nfloat res: %f\n", flt_res);
    printf("diff: %0.3f\n", flt_res - (f1 + f2));
  }

  return 0;
}
