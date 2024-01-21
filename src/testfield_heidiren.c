#include <stdlib.h>

#include "s21_decimal.h"

int main() {
  float f = 32.02234;

  s21_decimal dst;
  max_decimal(&dst);

  system("clear");
  printf("\n");
  debug_display_float(&f);
  printf("\n");
  debug_display_decimal(&dst);

  return 0;
}