#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "s21_decimal.h"

#define SELECTOR 5

float rand_float(int random, float min, float max) {
  srand(random * time(NULL));
  float value = min + ((float)rand() / RAND_MAX) * (max - min);
  return value;
}

int main() {
  for (int i = 0; i < 10; i++) {
    float fl = rand_float(i, -F_MAX, F_MAX) / 30340 + 0.123123;
    s21_decimal dec;
    s21_from_float_to_decimal(fl, &dec);
    debug_display_decimal("do", dec);
    upscale_x10(&dec);
    debug_display_decimal("re", dec);
  }

  return 0;
}