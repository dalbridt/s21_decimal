#include "s21_decimal.h"

// void s21_decreace_scale_big_decimal(s21_big_decimal *dst, int n) {
//   int scale = get_scale_big_decimal(*dst);
//   for(int i = 0; i < n; i++){
//     scale--;
//   }
//   set_scale_big_decimal(dst, scale);
// }

float rand_float(int random, float min, float max) {
  srand(random * time(NULL));
  float value = min + ((float)rand() / RAND_MAX) * (max - min);
  return value;
}

int randomize_int(int random) {
  srand(random * time(NULL));
  int value = rand();
  if (random % 2 == 0) {
    value = -value;
  }
  return value;
}

void randomize_decimal(s21_decimal *dec, float *fl, int it) {
  *fl = rand_float(it, -F_MAX, F_MAX);  // FLT_MIN / 2, FLT_MAX / 2
  reset_decimal(dec);

  s21_from_float_to_decimal(*fl, dec);

  if (it % 3 != 0) {
    upscale_decimal_x10(dec);
  }
}

int main() {  //
  s21_decimal a = {0}, b = {0}, result = {0};
  // s21_big_decimal b = {0};

  //     b.bits[0] =
  //     0b1111111111111111111111111111111111111111111111111111111111111111;
  //     b.bits[1] =
  //     0b1111111111111111111111111111111111111111111111111111111111111111;
  //     b.bits[2] =
  //     0b1111111111111111111111111111111111111111111111111111111111111111;
  //     b.bits[3] =
  //     0b1111111111111111111111111111111111111111111111111111111111111111;
  //     b.bits[4] =
  //     0b1111111111111111111111111111111111111111111111111111111111111111;
  //     b.bits[5] =
  //     0b1111111111111111111111111111111111111111111111111111111111111111;
  //     b.bits[6] =
  //     0b1111111111111111111111111111111111111111111111111111111111111111;
  //     b.scale = 0b10000000000111000000000000000000;
  // int i_1 = randomize_int(1);
  int i_2 = randomize_int(1);
  // float f_1 = rand_float(i_1, -0xffffffff, 0xffffffff);
  float f_2 = rand_float(i_2, -1000, 1000);
  printf("%f\n", f_2);
  // randomize_decimal(&a, &f_1, i_1);
  // randomize_decimal(&b, &f_2, i_2);
  s21_from_float_to_decimal(f_2, &b);
  // set_scale(&a, 0);
  // set_scale(&b, 0);

  // a.bits[0] = 0b00000000000000000000000010000010;
  // a.bits[1] = 0b00000000000000000000000000000000;
  // a.bits[2] = 0b00000000000010000000000000000000;
  // a.bits[3] = 0b00000000000000000000000000000000;

  // b.bits[0] = 0b00000000000000000010000000000011;
  // b.bits[1] = 0b00000000000000000000000000000000;
  // b.bits[2] = 0b00000000000000000000000000000000;
  // b.bits[3] = 0b00000000000000000000000000000000;
  // debug_display_big_decimal("before", b);
  // s21_decreace_scale_big_decimal(&b, 10);
  // debug_display_big_decimal("after", b);

  debug_display_decimal("B", b);
  printf("%d", get_sign(b));

  return 0;
}