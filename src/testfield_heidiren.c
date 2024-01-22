#include <stdlib.h>
#include <time.h>

#include "s21_decimal.h"

// s21_decimal add_decimal_beta(s21_decimal* x, s21_decimal* y);

// int main() {
//   float f = 32.02234;

//   s21_decimal dst;
//   // max_decimal(&dst);
//   system("clear");
//   printf("\n");
//   // debug_display_float(&f);
//   // printf("\n");

//   // s21_decimal dec1, dec2;

//   s21_decimal dec1 = {
//       .bits[0] = 0b00000000000000000000000011001000,
//       .bits[1] = 0b00000000000000000000000000000000,
//       .bits[2] = 0b00000000000000000000000000000000,
//       .bits[3] = 0b00000000000000000000000000000000,
//   };

//   s21_decimal dec2 = {
//       .bits[0] = 0b00000000000000000000000000010100,
//       .bits[1] = 0b00000000000000000000000000000000,
//       .bits[2] = 0b00000000000000000000000000000000,
//       .bits[3] = 0b00000000000000000000000000000000,
//   };

//   uint32_t abc = 1000000000u;

//   printf("divided int %u", div10(abc));

//   // equalize_scale(&dec1, 1);
//   // equalize_scale(&dec2, 1);
//   // printf("\n");
//   // s21_decimal dec3 = add_decimal_beta(&dec1, &dec2);

// debug_display_decimal("dec1", &dec1);

//   // debug_display_decimal("dec2", &dec2);

//   // debug_display_decimal("dec3", &dec3);

//   // printf("are dec1 and dec2 equal? - %s\n",
//   //        (s21_is_equal(dec1, dec2) == 1) ? "yes" : "no");

//   return 0;
// }

#include <limits.h>
#include <stdio.h>

// void show(const void* object, size_t size) {
//   const unsigned char* byte;
//   int i = 0;
//   byte = object;
//   // for (byte = object; size--; ++byte) {
//   unsigned int mask;

//   for (mask = 1 << (96 - 1); mask; mask >>= 1) {
//     putchar(mask & *byte ? '1' : '0');

//     // if (i % 8 == 7) putchar(' ');
//   }
//   i++;

//   putchar(' ');
//   if (i % 4 == 0) putchar('\n');
//   // }
//   putchar('\n');
// }

void shiftl(void* object, size_t size) {
  unsigned int* byte;
  for (byte = object; size--; ++byte) {
    unsigned int bit = 0;
    // if (size) {
    //   bit = byte[1] & ((CHAR_BIT - 1) >> 1) ? 1 : 0;
    // }
    *byte <<= 1;
    *byte |= bit;
  }
}

int main() {
  /* 11110000 11001100 10101010 11110000 */
  s21_decimal dec1 = {
      .bits[0] =  // 0b00000000000000000000000000000001,
      0b00000000000000000000000000000001,
      .bits[1] = 0b00000000000000000000000000000000,
      .bits[2] = 0b00000000000000000000000000000000,
      .bits[3] = 0b00000000000000000000000000000000,
  };
  // s21_decimal dec2 = {0}, dec3 = {0};
  // int msec = 0, trigger = 10; /* 10ms */
  clock_t before = clock();
  int i;

  for (i = 0; i < 64; i++) {
    //
    // dec2 = dec1;
    // int iterations = 0;
    // for (iterations = 0; iterations < 3; iterations++) {
    shiftl(dec1.bits, sizeof(dec1));
    // }
    // shiftl(dec2.bits, sizeof(unsigned int) * 4);
    // dec3 = add_decimal_beta(&dec1, &dec2);
    debug_display_decimal("dec1", &dec1);
    // dec1 = dec3;
  }
  // show(dec1.bits, sizeof(unsigned int) * 4);
  // debug_display_decimal("dec1", &dec1);

  // show(dec1.bits, sizeof(unsigned int) * 4);

  // clock_t difference = clock() - before;
  // msec = difference * 1000 / CLOCKS_PER_SEC;
  // printf("Time taken %d seconds %d milliseconds (%d iterations)\n", msec /
  // 1000,
  //        msec % 1000, i);

  return 0;
}

// #include <stdint.h>
// #include <stdio.h>

// typedef struct uint96_t {
//   uint32_t value[3];
// } uint96_t;

s21_decimal add_decimal_beta(s21_decimal* x, s21_decimal* y) {
  s21_decimal result = {0};
  unsigned int carry = 0;
  short i = 3;  // sizeof(x.bits) / sizeof(x.bits[0]);
  while (i--) {
    uint64_t tmp = (uint64_t)x->bits[i] + y->bits[i] + carry;
    result.bits[i] = (uint32_t)tmp;
    carry = tmp >> 32;
  }
  return result;
}

// s21_decimal decimal_x10(s21_decimal* src) {
//   //
// }

// typedef struct uint96_t {
//   uint32_t value[3];
// } uint96_t;

// uint96_t add_uint96(uint96_t x, uint96_t y) {
//   uint96_t result = {0};
//   unsigned int carry = 0;
//   short i = sizeof(x.value) / sizeof(x.value[0]);
//   while (i--) {
//     uint64_t tmp = (uint64_t)x.value[i] + y.value[i] + carry;
//     result.value[i] = (uint32_t)tmp;
//     carry = tmp >> 32;
//   }
//   return result;
// }

// void print_uint96(char *str, uint96_t x) {
//   printf("%s = %08x%08x%08x\r\n", str, x.value[0], x.value[1],
//   x.value[2]);
// }

// int main(void) {
//   uint96_t x = {0x0fffffff, 0xfffffffe, 0xffffffff};
//   uint96_t y = {0x00000000, 0x00000000, 0x00000001};
//   uint96_t r = add_uint96(x, y);
//   print_uint96("x", x);
//   print_uint96("y", y);
//   print_uint96("result", r);
//   return 0;
// }