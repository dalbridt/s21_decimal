#include <math.h>
#include <stdio.h>
// только выводит на экран, никуда не записывает и целую часть считает во всратом обратном порядке 
void float_to_binary(long double floatValue) {
  double intgr;
  double fract = modf(floatValue, &intgr);
  int prt1 = (int)intgr;
  int prt2 = (int)fract;

  printf("Number 1: %f\n", intgr);
  printf("Fractional Part: %f\n", fract);

  while (prt1 > 0) {
    printf("%d", (prt1 % 2));
    prt1 /= 2;
  }
   
   printf(".");
   // считает перевернуто 
   for(int i = 0; i < 32; i++) {
        fract *=2;
        int bit = fract;
        fract = fract - bit;   
        printf("%d",bit);
   }
}

int main() {
  long double floatValue = 784446.456;

  float_to_binary(floatValue);

  return 0;
}