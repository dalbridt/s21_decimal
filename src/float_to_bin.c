#include <math.h>
#include <stdio.h>
// только выводит на экран, никуда не записывает и целую часть считает во
// всратом обратном порядке
void float_to_binary(long double floatValue) {
  double intgr;
  double fract = modf(floatValue, &intgr);
  int prt1 = (int)intgr;
  // int prt2 = (int)fract;

  printf("Number 1: %f\n", intgr);
  printf("Fractional Part: %f\n", fract);
  // считает перевернуто
  while (prt1 > 0) {
    printf("%d", (prt1 % 2));
    prt1 /= 2;
  }

  printf(".");
  for (int i = 0; i < 32; i++) {
    fract *= 2;
    int bit = fract;
    fract = fract - bit;
    printf("%d", bit);
  }
}

int main() {
  long double floatValue = 784446.456;

  float_to_binary(floatValue);

  return 0;
}

// ---- trying to convert binary float ---------
// - мб конвертировать флот / децимал используя операции с децималом
// (используя этот алгоритм)!!!!
// float f = 15.3; uint32_t f_bits = *(uint32_t*)&f;
//  for (uint32_t mask = 0x80000000; mask; mask >>= 1) {
//     printf("%d", !!(f_bits & mask));
//   }
//   printf("\n");
// float result = 1;
// int i = -1;

// for (uint32_t mask = 0x400000; mask; mask >>= 1) {
//   int bit = !!(f_bits & mask);
//   printf("%d", bit);
//   result += bit * pow(2, i);
//   i--;
// }
// printf("\n");
// printf("mantissa: %f\n", result);
// int exponent = ((f_bits & ~0x80000000) >> 23) - 127;
// float exp = pow(2, exponent);
// float res = result * exp;

// printf("%f", res);

// mantissa i need to get : 7665091