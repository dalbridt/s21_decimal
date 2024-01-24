#include "s21_decimal.h"
#include <time.h>
#include <limits.h>

float rand_float(int random, float min, float max) {
  srand(random * time(NULL));
  float value = min + ((float)rand() / RAND_MAX) * (max - min);
  return value;
}

int main() {
  system("clear");
  for (int z = 0; z < 10; z++) {
    printf("------ %d ------\n", z);
    float f1 = rand_float(z, -1000, 1000);
    float f2 = rand_float(z+ 6, -1000, 1000);
    s21_decimal dec1 = {0};
    s21_decimal dec2 = {0};
    s21_from_float_to_decimal(f1, &dec1);
    s21_from_float_to_decimal(f2, &dec2);
    s21_decimal res = {0};
    s21_add(dec1, dec2, &res);
    printf("float add: %f+%f = %f\n", f1, f2, (f1 + f2));
    debug_display_decimal("res", res);
    float flt_res;
    s21_from_decimal_to_float(res, &flt_res);
    printf("\nfloat res: %f\n", flt_res);
  }
  return 0;
}
