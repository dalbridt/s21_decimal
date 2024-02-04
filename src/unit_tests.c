#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "s21_decimal.h"

#define ITER 200
#define TOL 1e-06

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
    upscale_x10(dec);
  }
}

START_TEST(t_add) {  // 01. s21_add
  float f1 = rand_float(_i, FLT_MIN, FLT_MAX);
  float f2 = rand_float(_i + 6, FLT_MIN, FLT_MAX);
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_from_float_to_decimal(f1, &dec1);
  s21_from_float_to_decimal(f2, &dec2);
  // ck_assert
  float flt_res;
  s21_decimal dec_res;

  randomize_decimal(&dec1, &f1, _i);
  randomize_decimal(&dec2, &f2, _i + 5);

  s21_add(dec1, dec2, &dec_res);

  s21_from_decimal_to_float(dec_res, &flt_res);

  ck_assert_float_eq_tol(flt_res, f1 + f2, TOL);
}
END_TEST

START_TEST(t_sub) {  // 02. s21_sub
  float f1, f2, flt_res;
  s21_decimal dec1, dec2, dec_res;

  randomize_decimal(&dec1, &f1, _i);
  randomize_decimal(&dec2, &f2, _i + 5);

  s21_sub(dec1, dec2, &dec_res);

  s21_from_decimal_to_float(dec_res, &flt_res);

  ck_assert_float_eq_tol(flt_res, f1 - f2, TOL);
}
END_TEST

START_TEST(t_mul) {  // 03. s21_mul
  float f1 = rand_float(_i, -F_MAX / 2, F_MAX / 2);
  float f2 = rand_float(_i + 10, -F_MAX / 2, F_MAX / 2);
  float res = f1 * f2;
  float conv_res;
  s21_decimal dec1, dec2, dec_res;
  s21_from_float_to_decimal(f1, &dec1);
  s21_from_float_to_decimal(f2, &dec2);
  if (_i % 5 == 0) {
    upscale_x10(&dec1);
  }
  s21_mul(dec1, dec2, &dec_res);
  s21_from_decimal_to_float(dec_res, &conv_res);
  ck_assert_float_eq_tol(res, conv_res, TOL);
}
END_TEST

START_TEST(t_div) {  // 04. s21_div
  float f1 = rand_float(_i, -F_MAX / 2, F_MAX / 2);
  float f2 = 0;
  while (f2 == 0) {
    f2 = rand_float(_i + 10, -F_MAX / 2, F_MAX / 2);
  }
  float res = f1 / f2;
  float conv_res;
  s21_decimal dec1, dec2, dec_res;
  s21_from_float_to_decimal(f1, &dec1);
  s21_from_float_to_decimal(f2, &dec2);
  if (_i % 3 == 0) {
    upscale_x10(&dec2);
  }
  if (_i % 5 == 0) {
    upscale_x10(&dec1);
  }
  s21_div(dec1, dec2, &dec_res);
  s21_from_decimal_to_float(dec_res, &conv_res);
  ck_assert_float_eq_tol(res, conv_res, TOL);
}
END_TEST

START_TEST(t_is_less) {  // 05. s21_is_less
  float val1 = rand_float(_i, -F_MAX, F_MAX);
  float val2 = rand_float(_i + 5, -F_MAX, F_MAX);
  if (_i % 3 == 0) {
    val1 *= -1;
  }
  if (_i % 5 == 0) {
    val2 = round(val2);
  }
  s21_decimal dec_1 = {0};
  s21_decimal dec_2 = {0};
  s21_from_float_to_decimal(val1, &dec_1);
  s21_from_float_to_decimal(val2, &dec_2);
  int res = val1 < val2;
  ck_assert_int_eq(res, s21_is_less(dec_1, dec_2));
}
END_TEST

START_TEST(t_is_less_or_equal) {  // 06. s21_is_less_or_equal
  float val1 = rand_float(_i, -F_MAX, F_MAX);
  float val2 = rand_float(_i + 5, -F_MAX, F_MAX);
  if (_i % 3 == 0) {
    val1 *= -1;
  }
  if (_i % 5 == 0) {
    val2 = round(val2);
  }
  if (_i % 7 == 0) {
    val2 = val1;
  }
  s21_decimal dec_1 = {0};
  s21_decimal dec_2 = {0};
  s21_from_float_to_decimal(val1, &dec_1);
  s21_from_float_to_decimal(val2, &dec_2);
  int res = val1 <= val2;
  ck_assert_int_eq(res, s21_is_less_or_equal(dec_1, dec_2));
}
END_TEST

START_TEST(t_is_greater) {  // 07. s21_is_greater
  float val1 = rand_float(_i, -F_MAX, F_MAX);
  float val2 = rand_float(_i + 5, -F_MAX, F_MAX);
  if (_i % 3 == 0) {
    val1 *= -1;
  }
  if (_i % 5 == 0) {
    val2 = round(val2);
  }

  s21_decimal dec_1 = {0};
  s21_decimal dec_2 = {0};
  s21_from_float_to_decimal(val1, &dec_1);
  if (_i % 9 != 0) {
    upscale_x10(&dec_1);
  }
  s21_from_float_to_decimal(val2, &dec_2);
  int res = val1 > val2;
  ck_assert_int_eq(res, s21_is_greater(dec_1, dec_2));
}
END_TEST

START_TEST(t_is_greater_or_equal) {  // 08. s21_is_greater_or_equal
  float val1 = rand_float(_i, -F_MAX, F_MAX);
  float val2 = rand_float(_i + 5, -F_MAX, F_MAX);
  if (_i % 3 == 0) {
    val1 *= -1;
  }
  if (_i % 5 == 0) {
    val2 = round(val2);
  }
  if (_i % 7 == 0) {
    val2 = val1;
  }
  s21_decimal dec_1 = {0};
  s21_decimal dec_2 = {0};
  s21_from_float_to_decimal(val1, &dec_1);
  s21_from_float_to_decimal(val2, &dec_2);

  if (_i % 3 == 0) {
    upscale_x10(&dec_1);
  }
  if (_i % 5 == 0) {
    upscale_x10(&dec_2);
  }
  int res = val1 >= val2;
  ck_assert_int_eq(res, s21_is_greater_or_equal(dec_1, dec_2));
}
END_TEST

START_TEST(t_is_equal) {  // 09. s21_is_equal
  int v_int = randomize_int(_i);
  s21_decimal dec1, dec2;
  if (_i % 2 == 0) {
    s21_from_int_to_decimal(v_int, &dec1);
    s21_from_int_to_decimal(v_int, &dec2);
    int res = s21_is_equal(dec1, dec2);
    ck_assert_int_eq(res, 1);
  } else {
    s21_from_int_to_decimal(v_int, &dec1);
    s21_from_int_to_decimal((v_int + _i), &dec2);
    int res = s21_is_equal(dec1, dec2);
    ck_assert_int_eq(res, 0);
  }
  reset_decimal(&dec1);
  reset_decimal(&dec2);
  int res = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
  // // is it too much for one test and should be two?
  float f_val = rand_float(_i, -F_MAX, F_MAX);
  if (_i % 2 == 0) {
    s21_from_float_to_decimal(f_val, &dec1);
    s21_from_float_to_decimal(f_val, &dec2);
    int res = s21_is_equal(dec1, dec2);
    ck_assert_int_eq(res, 1);
  } else {
    float not_eq = f_val + 100;
    // printf("#%d |f_val: %f | 2nd: %f \n", _i, f_val, not_eq);
    s21_from_float_to_decimal(f_val, &dec1);
    s21_from_float_to_decimal(not_eq, &dec2);
    int res = s21_is_equal(dec1, dec2);
    ck_assert_int_eq(res, 0);
  }
}
END_TEST

START_TEST(t_is_not_equal) {  // 10. s21_is_not_equal
  s21_decimal dec1, dec2;
  float f1, f2;
  randomize_decimal(&dec1, &f1, _i);
  if (_i % 5 == 0) {
    dec2 = dec1;
    f2 = f1;
  } else if (_i % 10 == 0) {
    dec2 = dec1;
    f2 = -f1;
    s21_from_float_to_decimal(f2, &dec2);
  } else if (_i % 50 == 0) {
    reset_decimal(&dec1);
    reset_decimal(&dec2);
    f1 = 0;
    f2 = 0;
  } else {
    randomize_decimal(&dec2, &f2, _i + 5);
  }
  ck_assert_int_eq(s21_is_not_equal(dec1, dec2), (f1 != f2));
}
END_TEST

START_TEST(t_from_int_to_decimal) {  // 11. s21_from_int_to_decimal
  int val, val_res;
  s21_decimal dec_res;
  val = randomize_int(_i);
  s21_from_int_to_decimal(val, &dec_res);
  s21_from_decimal_to_int(dec_res, &val_res);
  ck_assert_int_eq(val, val_res);
}
END_TEST

START_TEST(t_from_float_to_decimal) {  // 12. s21_from_float_to_decimal
  float f1, flt_res;
  s21_decimal dec_res;

  f1 = rand_float(_i, -F_MAX, F_MAX);

  s21_from_float_to_decimal(f1, &dec_res);

  s21_from_decimal_to_float(dec_res, &flt_res);

  ck_assert_float_eq_tol(flt_res, f1, TOL);
}
END_TEST

START_TEST(t_from_decimal_to_int) {  // 13. s21_from_decimal_to_int
  int i1;
  s21_decimal dec_res;
  float f1 = rand_float(_i, -F_MAX, F_MAX);

  s21_from_int_to_decimal((int)f1, &dec_res);

  if (_i % 3 != 0) {
    upscale_x10(&dec_res);
  }

  s21_from_decimal_to_int(dec_res, &i1);

  ck_assert_int_eq((int)f1, i1);
}
END_TEST

START_TEST(t_from_decimal_to_float) {  // 14. s21_from_decimal_to_float
  float f1, flt_res;
  s21_decimal dec_res;

  f1 = rand_float(_i, -F_MAX, F_MAX);

  s21_from_float_to_decimal(f1, &dec_res);

  s21_from_decimal_to_float(dec_res, &flt_res);

  ck_assert_float_eq_tol(flt_res, f1, TOL);
}
END_TEST

START_TEST(t_floor) {  // 15. s21_floor
  float fl = rand_float(_i, -F_MAX, F_MAX);
  s21_decimal dec, dec_res;
  s21_from_float_to_decimal(fl, &dec);
  if (_i % 3 == 0) {
    upscale_x10(&dec);
  }
  fl = floor(fl);
  s21_floor(dec, &dec_res);

  s21_from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(s21_is_equal(dec_res, dec), 1);
}
END_TEST

START_TEST(t_round) {  // 16. s21_round
  float fl = rand_float(_i, -F_MAX, F_MAX);
  s21_decimal dec, dec_res;
  s21_from_float_to_decimal(fl, &dec);
  fl = round(fl);
  if (_i % 3 != 0) {
    upscale_x10(&dec);
  }
  s21_round(dec, &dec_res);

  s21_from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(s21_is_equal(dec_res, dec), 1);
}
END_TEST

START_TEST(t_truncate) {  // 17. s21_truncate
  float fl = rand_float(_i, -F_MAX, F_MAX);
  s21_decimal dec, dec_res, dec_int;
  s21_from_float_to_decimal(fl, &dec);
  double res;
  modf(fl, &res);
  s21_from_int_to_decimal((int)res, &dec_int);
  if (_i % 3 != 0) {
    upscale_x10(&dec);
  }
  s21_truncate(dec, &dec_res);
  ck_assert_int_eq(s21_is_equal(dec_int, dec_res), 1);
}
END_TEST

START_TEST(t_negate) {  // 18. s21_negate
  float f1, flt_res;
  s21_decimal dec1, dec_res;

  randomize_decimal(&dec1, &f1, _i);

  s21_negate(dec1, &dec_res);

  s21_from_decimal_to_float(dec_res, &flt_res);

  ck_assert_float_eq_tol(flt_res, -f1, TOL);
}
END_TEST

Suite *decimal_suite() {
  Suite *s = suite_create("s21_decimal_tests");

  TCase *add = tcase_create("01. s21_add");
  tcase_add_loop_test(add, t_add, 0, ITER);
  suite_add_tcase(s, add);

  TCase *sub = tcase_create("02. s21_sub");
  tcase_add_loop_test(sub, t_sub, 0, ITER);
  suite_add_tcase(s, sub);

  TCase *mul = tcase_create("03. s21_mul");
  tcase_add_loop_test(mul, t_mul, 0, ITER);
  suite_add_tcase(s, mul);

  TCase *div = tcase_create("04. s21_div");
  tcase_add_loop_test(div, t_div, 0, ITER);
  suite_add_tcase(s, div);

  TCase *is_less = tcase_create("05. s21_is_less");
  tcase_add_loop_test(is_less, t_is_less, 0, ITER);
  suite_add_tcase(s, is_less);

  TCase *is_less_or_equal = tcase_create("06. s21_is_less_or_equal");
  tcase_add_loop_test(is_less_or_equal, t_is_less_or_equal, 0, ITER);
  suite_add_tcase(s, is_less_or_equal);

  TCase *is_greater = tcase_create("07. s21_is_greater");
  tcase_add_loop_test(is_greater, t_is_greater, 0, ITER);
  suite_add_tcase(s, is_greater);

  TCase *is_greater_or_equal = tcase_create("08. s21_is_greater_or_equal");
  tcase_add_loop_test(is_greater_or_equal, t_is_greater_or_equal, 0, ITER);
  suite_add_tcase(s, is_greater_or_equal);

  TCase *is_equal = tcase_create("09. s21_is_equal");
  tcase_add_loop_test(is_equal, t_is_equal, 0, ITER);
  suite_add_tcase(s, is_equal);

  TCase *is_not_equal = tcase_create("10. s21_is_not_equal");
  tcase_add_loop_test(is_not_equal, t_is_not_equal, 0, ITER);
  suite_add_tcase(s, is_not_equal);

  TCase *from_int_to_decimal = tcase_create("11. s21_from_int_to_decimal");
  tcase_add_loop_test(from_int_to_decimal, t_from_int_to_decimal, 0, ITER);
  suite_add_tcase(s, from_int_to_decimal);

  TCase *from_float_to_decimal = tcase_create("12. s21_from_float_to_decimal");
  tcase_add_loop_test(from_float_to_decimal, t_from_float_to_decimal, 0, ITER);
  suite_add_tcase(s, from_float_to_decimal);

  TCase *from_decimal_to_int = tcase_create("13. s21_from_decimal_to_int");
  tcase_add_loop_test(from_decimal_to_int, t_from_decimal_to_int, 0, ITER);
  suite_add_tcase(s, from_decimal_to_int);

  TCase *from_decimal_to_float = tcase_create("14. s21_from_decimal_to_float");
  tcase_add_loop_test(from_decimal_to_float, t_from_decimal_to_float, 0, ITER);
  suite_add_tcase(s, from_decimal_to_float);

  TCase *floor = tcase_create("15. s21_floor");
  tcase_add_loop_test(floor, t_floor, 0, ITER);
  suite_add_tcase(s, floor);

  TCase *round = tcase_create("16. s21_round");
  tcase_add_loop_test(round, t_round, 0, ITER);
  suite_add_tcase(s, round);

  TCase *truncate = tcase_create("17. s21_truncate");
  tcase_add_loop_test(truncate, t_truncate, 0, ITER);
  suite_add_tcase(s, truncate);

  TCase *negate = tcase_create("18. s21_negate");
  tcase_add_loop_test(negate, t_negate, 0, ITER);
  suite_add_tcase(s, negate);

  return s;
}

int main() {
  int failed = 0;
  Suite *s = decimal_suite();
  SRunner *runner = srunner_create(s);
  srunner_set_log(runner, "test_report.log");

  srunner_run_all(runner, CK_NORMAL);

  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}