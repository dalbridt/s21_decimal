#include <stdlib.h>

#include "s21_decimal.h"

// int main() {
//   float f = 32.02234;

  s21_decimal dst;
  max_decimal(&dst);

  //   system("clear");
  printf("\n");
  debug_display_float(&f);
  printf("\n");
  debug_display_decimal(&dst);

  return 0;
}

// 79228162514264337593543950336.000000
// 792281625142643342906782264096410390086202166153997975552.000000

// SHOULD BE
// 79228162514264337593543950335

// 79228162514264334286419132416.000000