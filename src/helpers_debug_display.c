#include "s21_decimal.h"

#define C_RED "\x1b[31m"
#define C_GREEN "\x1b[32m"
#define C_BLUE "\x1b[34m"
#define C_INVIS "\x1b[8m"
#define C_NO "\x1b[0m"
#define C_GREY "\x1b[2m"

void debug_display_decimal(char* name, s21_decimal src) {
  unsigned int* b = &src.bits[0];
  unsigned int byte;

  int sign = s21_get_sign(src);
  int exp = s21_get_scale(src);

  long double mantissa = s21_get_mantissa(&src);
  long double mantissa_copy = mantissa;
  int exp_copy = exp;

  while (exp_copy > 0) {
    mantissa_copy /= 10;
    exp_copy--;
  }

  printf("decimal %s: is ", name);
  printf("%s%d%s", C_RED, sign ? -1 : 1, C_NO);
  printf(" * %s%Lf%s", C_BLUE, mantissa, C_NO);
  printf(" / 10^%s%d%s", C_GREEN, exp, C_NO);
  printf(" =~ %Lf", mantissa_copy * (sign ? -1 : 1));
  printf("\n");

  for (short i = 0x80 - 1; i >= 0; i--) {
    if (i % 8 == 7) printf(C_NO "[");
    byte = (b[i / 0x20] >> i) & 1;
    printf(C_BLUE);
    if (i / 0x20 == 3) {
      printf(C_GREY);  // C_INVIS

      if (i > 0x74 && i <= 0x77) printf(C_GREY);
      if (i > 0x6F && i <= 0x74) printf(C_NO C_GREEN);
      if (i == 0x7F) printf(C_NO C_RED);
    }

    printf("%u" C_NO, byte);
    if (i % 8 == 0) printf(C_NO "] ");
    if (i % 32 == 0) printf("\n");
  }
  printf("\n");
}

void debug_display_big_decimal(char* name, s21_big_decimal src) {
  uint64_t* b = &src.bits[0];
  unsigned int byte;

  int sign = s21_get_sign_big(src);
  int exp = s21_get_scale_big(src);

  long double mantissa = s21_get_mantissa_big(&src);
  long double mantissa_copy = mantissa;
  int exp_copy = exp;

  while (exp_copy > 0) {
    mantissa_copy /= 10;
    exp_copy--;
  }

  printf("big decimal %s: is ", name);
  printf("%s%d%s", C_RED, sign ? -1 : 1, C_NO);
  printf(" * %s%Lf%s", C_BLUE, mantissa, C_NO);
  printf(" / 10^%s%d%s", C_GREEN, exp, C_NO);
  printf(" =~ %Lf", mantissa_copy * (sign ? -1 : 1));
  printf("\n");

  for (short i = 0x1E0 - 1; i >= 0; i--) {
    if (i % 8 == 7) printf(C_NO "[");
    if (i >= 0x1E0 && i <= 0x19F) {
      byte = (b[i / 0x20] >> i) & 1;
    } else {
      byte = (b[i / 0x40] >> i) & 1;
    }
    printf(C_BLUE);
    if (i / 0x40 == 7) {
      printf(C_GREY);  // C_INVIS

      if (i > 0x1D5 && i <= 0x1D8) printf(C_GREY);
      if (i > 0x1CF && i < 0x1D5) printf(C_NO C_GREEN);
      if (i == 0x1DF) printf(C_NO C_RED);
    }

    printf("%u" C_NO, byte);
    if (i % 8 == 0) printf(C_NO "] ");
    if (i % 64 == 0) printf("\n");
  }
  printf("\n");
}

void debug_display_float(float* src) {
  unsigned int* b = (unsigned int*)src;
  unsigned char byte;

  int sign = signbit(*src) == 0 ? 1 : -1;
  int exp;
  float mantissa = frexpf(*src, &exp);

  float real_float = mantissa * pow(2.0, exp);

  printf("float: %f is ", *src);
  printf("%s%d%s", C_RED, sign, C_NO);
  printf(" * %s%f%s", C_BLUE, sign * mantissa, C_NO);
  printf(" * 2^%s(%d-127 = %d)%s", C_GREEN, exp + 0b01111111, exp, C_NO);
  printf(" = %f", real_float);
  printf("\n");

  for (short i = 0x20 - 1; i >= 0; i--) {
    if (i % 8 == 7) printf(C_NO "[");
    byte = (b[0] >> i) & 1;
    printf(C_BLUE);
    if (i > 0x16 && i < 0x1F) printf(C_NO C_GREEN);
    if (i == 0x1F) printf(C_NO C_RED);

    printf("%u" C_NO, byte);
    if (i % 8 == 0) printf(C_NO "] ");
  }
  printf("\n");
}

void debug_display_int(int src) {
  //   unsigned int* b = (unsigned int*)src;
  unsigned char byte;

  int sign = signbit((float)src) == 0 ? 1 : -1;
  int exp;

  printf("int: %d is ", src);
  printf("%s%d%s", C_RED, sign, C_NO);
  printf(" * %s%d%s", C_BLUE, sign * src, C_NO);
  printf(" = %d", src);
  printf("\n");

  for (short i = 0x20 - 1; i >= 0; i--) {
    if (i % 8 == 7) printf(C_NO "[");
    byte = (src >> i) & 1;
    printf(C_BLUE);
    // if (i > 0x16 && i < 0x1F) printf(C_NO C_GREEN);
    if (i == 0x1F) printf(C_NO C_RED);

    printf("%u" C_NO, byte);
    if (i % 8 == 0) printf(C_NO "] ");
  }
  printf("\n");
}