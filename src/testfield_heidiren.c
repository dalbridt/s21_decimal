#include <stdlib.h>

#include "s21_decimal.h"

int main() {
  float f = 7;

  s21_decimal dst;
  dst.bits[0] = 0b00100000001000000001000000100000;
  dst.bits[1] = 0b00000000000000000000000000000000;
  dst.bits[2] = 0b00000000000000000000000000000000;
  dst.bits[3] = 0b10000000000111010000000000000000;

  system("clear");  //*nix
  printf("\n");
  debug_display_float(&f);
  printf("\n");
  debug_display_decimal(&dst);
  printf("\n");

  return 0;
}
