#include <stdio.h>

#include "s21_decimal.h"

int main() {
  // testing convertr from and to int
  for (int i = -2147483647; i < 2147483647; i++) {
    s21_decimal num;
    int check = 0;
    s21_from_int_to_decimal(i, &num);
    s21_from_decimal_to_int(num, &check);
    if (check != i) {
      printf("number %d is not processed correctly", i);
    }
  }
  printf("ya conchil");
  return 0;
}