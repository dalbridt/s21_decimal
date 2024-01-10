#include <stdio.h>

#include "s21_decimal.h"

#define C_RED "\x1b[31m"
#define C_GREEN "\x1b[32m"
#define C_BLUE "\x1b[34m"
#define C_GREY "\x1b[8m"
#define C_NO "\x1b[0m"

int get_bit(int src, int index) {
  int mask = 1 << index;
  int ret = (src & mask) == 0 ? 0 : 1;

  return ret;
}

/*  index 0 - 31 = bits[0]
    index 32 - 63 = bits[1]
    index 64 - 95 = bits[2]
    index 96 - 127 = bits[3]
*/

void set_bit(s21_decimal* src, int index, int value) {
  int arr_index = index / 32;
  int bit_index = index % 32;
  if (value == 1) {
    src->bits[arr_index] |= (1 << bit_index);
  } else if (value == 0) {
    src->bits[arr_index] &= ~(1 << bit_index);
  }
}

void debug_display_decimal(s21_decimal* src) {
  int* b = &src->bits[0];
  unsigned char byte;
  for (short i = 0; i < 0x80; i++) {
    if (i % 8 == 0) printf(C_NO "[");
    byte = (b[0] >> i) & 1;
    printf(C_BLUE);
    if (i / 0x20 == 3) {
      printf(C_GREY);
      if (i > 0x6F && i <= 0x77) printf(C_NO C_GREEN);
      if (i == 0x7F) printf(C_NO C_RED);
    }

    printf("%u" C_NO, byte);
    if (i % 8 == 7) printf(C_NO "] ");
    if (i % 32 == 31) printf("\n");
  }
}

void debug_display_float(float* src) {
  int* b = &src;
  unsigned char byte;
  for (short i = 0; i < 0x20; i++) {
    if (i % 8 == 0) printf(C_NO "[");
    byte = (b[0] >> i) & 1;
    printf(C_BLUE);
    if (i / 0x20 == 3) {
      printf(C_GREY);
      if (i > 0x6F && i <= 0x77) printf(C_NO C_GREEN);
      if (i == 0x7F) printf(C_NO C_RED);
    }

    printf("%u" C_NO, byte);
    if (i % 8 == 7) printf(C_NO "] ");
    if (i % 32 == 31) printf("\n");
  }
}

void reset_decimal(s21_decimal* src) { *src = (s21_decimal){0}; }