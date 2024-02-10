#include <check.h>

#include "s21_decimal.h"

#define ITER 50
#define TOL 1e-05

#ifdef TESTS
#include "unit_tests.h"
void hubert_furr_tests(SRunner *runner);

#endif

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
  s21_reset(dec);

  s21_from_float_to_decimal(*fl, dec);

  if (it % 3 != 0) {
    s21_upscale_x10(dec);
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
    s21_upscale_x10(&dec1);
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
    s21_upscale_x10(&dec2);
  }
  if (_i % 5 == 0) {
    s21_upscale_x10(&dec1);
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
    s21_upscale_x10(&dec_1);
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
  s21_big_decimal dec_1_big = {0};
  s21_big_decimal dec_2_big = {0};
  s21_from_float_to_decimal(val1, &dec_1);
  s21_from_float_to_decimal(val2, &dec_2);

  if (_i % 3 == 0) {
    s21_upscale_x10(&dec_1);
  }
  if (_i % 5 == 0) {
    s21_upscale_x10(&dec_2);
  }
  s21_decimal_to_big(dec_1, &dec_1_big);
  s21_decimal_to_big(dec_2, &dec_2_big);
  int res = val1 >= val2;
  ck_assert_int_eq(res, s21_is_greater_or_equal(dec_1, dec_2));
  ck_assert_int_eq(res, s21_is_greater_or_equal_big(dec_1_big, dec_2_big));
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
  s21_reset(&dec1);
  s21_reset(&dec2);
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
    s21_reset(&dec1);
    s21_reset(&dec2);
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
    s21_upscale_x10(&dec_res);
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
    s21_upscale_x10(&dec);
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
    s21_upscale_x10(&dec);
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
    s21_upscale_x10(&dec);
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

START_TEST(t_div_eq) {  // 19. s21_div_equal
  float f1 = rand_float(_i, -F_MAX / 2, F_MAX / 2);
  while (f1 == 0) {
    f1 = rand_float(_i + 10, -F_MAX / 2, F_MAX / 2);
  }
  float f2 = f1;
  float res = 1.0;
  float conv_res;
  s21_decimal dec1, dec2, dec_res;
  s21_from_float_to_decimal(f1, &dec1);
  s21_from_float_to_decimal(f2, &dec2);
  if (_i % 3 == 0) {
    s21_upscale_x10(&dec2);
  }
  if (_i % 5 == 0) {
    s21_upscale_x10(&dec1);
  }
  s21_div(dec1, dec2, &dec_res);
  s21_from_decimal_to_float(dec_res, &conv_res);
  ck_assert_float_eq_tol(res, conv_res, TOL);
}
END_TEST

START_TEST(t_div_zero) {  // 20. s21_div_zero
  float f1 = rand_float(_i, -F_MAX / 2, F_MAX / 2);
  while (f1 == 0) {
    f1 = rand_float(_i + 10, -F_MAX / 2, F_MAX / 2);
  }
  float f2 = 0.0;
  int res = 3;
  s21_decimal dec1, dec2, dec_res;
  s21_from_float_to_decimal(f1, &dec1);
  s21_from_float_to_decimal(f2, &dec2);
  if (_i % 3 == 0) {
    s21_upscale_x10(&dec2);
  }
  if (_i % 5 == 0) {
    s21_upscale_x10(&dec1);
  }
  ck_assert_int_eq(s21_div(dec1, dec2, &dec_res), res);
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

  TCase *div_equal = tcase_create("19. s21_div equal");
  tcase_add_test(div_equal, t_div_eq);
  suite_add_tcase(s, div_equal);

  TCase *div_zero = tcase_create("20. s21_div zero");
  tcase_add_test(div_zero, t_div_zero);
  suite_add_tcase(s, div_zero);
  return s;
}

int main() {
  int failed = 0;
  Suite *s = decimal_suite();
  SRunner *runner = srunner_create(s);

#ifdef TESTS
  hubert_furr_tests(runner);
#endif

  srunner_set_log(runner, "test_report.log");

  srunner_run_all(runner, CK_NORMAL);

  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

#ifdef TESTS

void hubert_furr_tests(SRunner *runner) {
  // srunner_add_suite(runner, add_suite0());
  // srunner_add_suite(runner, add_suite1());

  // #if TESTS == 2
  //   srunner_add_suite(runner, add_suite2());
  //   srunner_add_suite(runner, add_suite3());
  //   srunner_add_suite(runner, add_suite4());
  //   srunner_add_suite(runner, add_suite5());
  //   srunner_add_suite(runner, add_suite6());
  //   srunner_add_suite(runner, add_suite7());
  //   srunner_add_suite(runner, add_suite8());
  //   srunner_add_suite(runner, add_suite9());

  // #endif

  //   srunner_add_suite(runner, sub_suite0());
  //   srunner_add_suite(runner, sub_suite1());

  // #if TESTS == 2
  //   srunner_add_suite(runner, sub_suite2());
  //   srunner_add_suite(runner, sub_suite3());
  //   srunner_add_suite(runner, sub_suite4());
  //   srunner_add_suite(runner, sub_suite5());
  //   srunner_add_suite(runner, sub_suite6());
  //   srunner_add_suite(runner, sub_suite7());
  //   srunner_add_suite(runner, sub_suite8());
  //   srunner_add_suite(runner, sub_suite9());
  // #endif

  //   srunner_add_suite(runner, mul_suite0());
  //   srunner_add_suite(runner, mul_suite1());

  // #if TESTS == 2
  //   srunner_add_suite(runner, mul_suite2());
  //   srunner_add_suite(runner, mul_suite3());
  //   srunner_add_suite(runner, mul_suite4());
  //   srunner_add_suite(runner, mul_suite5());
  //   srunner_add_suite(runner, mul_suite6());
  //   srunner_add_suite(runner, mul_suite7());
  //   srunner_add_suite(runner, mul_suite8());
  //   srunner_add_suite(runner, mul_suite9());
  // #endif

  //   srunner_add_suite(runner, div_suite0());
  //   srunner_add_suite(runner, div_suite1());

  // #if TESTS == 2
  //   srunner_add_suite(runner, div_suite2());
  //   srunner_add_suite(runner, div_suite3());
  //   srunner_add_suite(runner, div_suite4());
  //   srunner_add_suite(runner, div_suite5());
  //   srunner_add_suite(runner, div_suite6());
  //   srunner_add_suite(runner, div_suite7());
  //   srunner_add_suite(runner, div_suite8());
  //   srunner_add_suite(runner, div_suite9());
  //   srunner_add_suite(runner, div_suite10());
  //   srunner_add_suite(runner, div_suite11());
  //   srunner_add_suite(runner, div_suite12());
  //   srunner_add_suite(runner, div_suite13());
  //   srunner_add_suite(runner, div_suite14());
  //   srunner_add_suite(runner, div_suite15());
  //   srunner_add_suite(runner, div_suite16());
  //   srunner_add_suite(runner, div_suite17());
  //   srunner_add_suite(runner, div_suite18());
  // #endif

  //   srunner_add_suite(runner, is_less_suite1());
  //   srunner_add_suite(runner, is_less_suite2());

  // #if TESTS == 2
  //   srunner_add_suite(runner, is_less_suite3());
  //   srunner_add_suite(runner, is_less_suite4());
  //   srunner_add_suite(runner, is_less_suite5());
  //   srunner_add_suite(runner, is_less_suite6());
  //   srunner_add_suite(runner, is_less_suite7());
  //   srunner_add_suite(runner, is_less_suite8());
  //   srunner_add_suite(runner, is_less_suite9());
  //   srunner_add_suite(runner, is_less_suite10());
  //   srunner_add_suite(runner, is_less_suite11());
  //   srunner_add_suite(runner, is_less_suite12());
  //   srunner_add_suite(runner, is_less_suite13());
  //   srunner_add_suite(runner, is_less_suite14());
  //   srunner_add_suite(runner, is_less_suite15());
  //   srunner_add_suite(runner, is_less_suite16());
  // #endif

  //   srunner_add_suite(runner, is_equal_suite1());
  //   srunner_add_suite(runner, is_equal_suite2());

  // #if TESTS == 2
  //   srunner_add_suite(runner, is_equal_suite3());
  //   srunner_add_suite(runner, is_equal_suite4());
  //   srunner_add_suite(runner, is_equal_suite5());
  //   srunner_add_suite(runner, is_equal_suite6());
  //   srunner_add_suite(runner, is_equal_suite7());
  //   srunner_add_suite(runner, is_equal_suite8());
  //   srunner_add_suite(runner, is_equal_suite9());
  //   srunner_add_suite(runner, is_equal_suite10());
  //   srunner_add_suite(runner, is_equal_suite11());
  //   srunner_add_suite(runner, is_equal_suite12());
  //   srunner_add_suite(runner, is_equal_suite13());
  //   srunner_add_suite(runner, is_equal_suite14());
  //   srunner_add_suite(runner, is_equal_suite15());
  //   srunner_add_suite(runner, is_equal_suite16());
  // #endif

  //   srunner_add_suite(runner, is_less_or_equal_suite1());
  //   srunner_add_suite(runner, is_less_or_equal_suite2());
  // #if TESTS == 2
  //   srunner_add_suite(runner, is_less_or_equal_suite3());
  //   srunner_add_suite(runner, is_less_or_equal_suite4());
  //   srunner_add_suite(runner, is_less_or_equal_suite5());
  //   srunner_add_suite(runner, is_less_or_equal_suite6());
  //   srunner_add_suite(runner, is_less_or_equal_suite7());
  //   srunner_add_suite(runner, is_less_or_equal_suite8());
  //   srunner_add_suite(runner, is_less_or_equal_suite9());
  //   srunner_add_suite(runner, is_less_or_equal_suite10());
  //   srunner_add_suite(runner, is_less_or_equal_suite11());
  //   srunner_add_suite(runner, is_less_or_equal_suite12());
  //   srunner_add_suite(runner, is_less_or_equal_suite13());
  //   srunner_add_suite(runner, is_less_or_equal_suite14());
  //   srunner_add_suite(runner, is_less_or_equal_suite15());
  //   srunner_add_suite(runner, is_less_or_equal_suite16());
  // #endif

  //   srunner_add_suite(runner, is_greater_suite1());
  //   srunner_add_suite(runner, is_greater_suite2());

  // #if TESTS == 2
  //   srunner_add_suite(runner, is_greater_suite3());
  //   srunner_add_suite(runner, is_greater_suite4());
  //   srunner_add_suite(runner, is_greater_suite5());
  //   srunner_add_suite(runner, is_greater_suite6());
  //   srunner_add_suite(runner, is_greater_suite7());
  //   srunner_add_suite(runner, is_greater_suite8());
  //   srunner_add_suite(runner, is_greater_suite9());
  //   srunner_add_suite(runner, is_greater_suite10());
  //   srunner_add_suite(runner, is_greater_suite11());
  //   srunner_add_suite(runner, is_greater_suite12());
  //   srunner_add_suite(runner, is_greater_suite13());
  //   srunner_add_suite(runner, is_greater_suite14());
  //   srunner_add_suite(runner, is_greater_suite15());
  //   srunner_add_suite(runner, is_greater_suite16());
  // #endif

  //   srunner_add_suite(runner, is_greater_or_equal_suite1());
  //   srunner_add_suite(runner, is_greater_or_equal_suite2());

  // #if TESTS == 2
  //   srunner_add_suite(runner, is_greater_or_equal_suite3());
  //   srunner_add_suite(runner, is_greater_or_equal_suite4());
  //   srunner_add_suite(runner, is_greater_or_equal_suite5());
  //   srunner_add_suite(runner, is_greater_or_equal_suite6());
  //   srunner_add_suite(runner, is_greater_or_equal_suite7());
  //   srunner_add_suite(runner, is_greater_or_equal_suite8());
  //   srunner_add_suite(runner, is_greater_or_equal_suite9());
  //   srunner_add_suite(runner, is_greater_or_equal_suite10());
  //   srunner_add_suite(runner, is_greater_or_equal_suite11());
  //   srunner_add_suite(runner, is_greater_or_equal_suite12());
  //   srunner_add_suite(runner, is_greater_or_equal_suite13());
  //   srunner_add_suite(runner, is_greater_or_equal_suite14());
  //   srunner_add_suite(runner, is_greater_or_equal_suite15());
  //   srunner_add_suite(runner, is_greater_or_equal_suite16());
  // #endif

  //   srunner_add_suite(runner, is_not_equal_suite1());
  //   srunner_add_suite(runner, is_not_equal_suite2());

  // #if TESTS == 2
  //   srunner_add_suite(runner, is_not_equal_suite3());
  //   srunner_add_suite(runner, is_not_equal_suite4());
  //   srunner_add_suite(runner, is_not_equal_suite5());
  //   srunner_add_suite(runner, is_not_equal_suite6());
  //   srunner_add_suite(runner, is_not_equal_suite7());
  //   srunner_add_suite(runner, is_not_equal_suite8());
  //   srunner_add_suite(runner, is_not_equal_suite9());
  //   srunner_add_suite(runner, is_not_equal_suite10());
  //   srunner_add_suite(runner, is_not_equal_suite11());
  //   srunner_add_suite(runner, is_not_equal_suite12());
  //   srunner_add_suite(runner, is_not_equal_suite13());
  //   srunner_add_suite(runner, is_not_equal_suite14());
  //   srunner_add_suite(runner, is_not_equal_suite15());
  //   srunner_add_suite(runner, is_not_equal_suite16());
  // #endif

  //   srunner_add_suite(runner, from_int_to_decimal_suite());

  //   srunner_add_suite(runner, from_float_to_decimal_suite0());

  // #if TESTS == 2
  //   srunner_add_suite(runner, from_float_to_decimal_suite1());
  //   srunner_add_suite(runner, from_float_to_decimal_suite2());
  //   srunner_add_suite(runner, from_float_to_decimal_suite3());
  //   srunner_add_suite(runner, from_float_to_decimal_suite4());
  //   srunner_add_suite(runner, from_float_to_decimal_suite5());
  //   srunner_add_suite(runner, from_float_to_decimal_suite6());
  //   srunner_add_suite(runner, from_float_to_decimal_suite7());
  // #endif

  srunner_add_suite(runner, from_decimal_to_int_suite0());

#if TESTS == 2
  srunner_add_suite(runner, from_decimal_to_int_suite1());
  srunner_add_suite(runner, from_decimal_to_int_suite2());
  srunner_add_suite(runner, from_decimal_to_int_suite3());
#endif

  //   srunner_add_suite(runner, from_decimal_to_float_suite0());

  // #if TESTS == 2
  //   srunner_add_suite(runner, from_decimal_to_float_suite1());
  //   srunner_add_suite(runner, from_decimal_to_float_suite2());
  //   srunner_add_suite(runner, from_decimal_to_float_suite3());
  //   srunner_add_suite(runner, from_decimal_to_float_suite4());
  //   srunner_add_suite(runner, from_decimal_to_float_suite5());
  //   srunner_add_suite(runner, from_decimal_to_float_suite6());
  //   srunner_add_suite(runner, from_decimal_to_float_suite7());
  //   srunner_add_suite(runner, from_decimal_to_float_suite8());
  // #endif

  //   srunner_add_suite(runner, floor_suite0());

  // #if TESTS == 2
  //   srunner_add_suite(runner, floor_suite1());
  //   srunner_add_suite(runner, floor_suite2());
  //   srunner_add_suite(runner, floor_suite3());
  // #endif

  //   srunner_add_suite(runner, round_suite0());

  // #if TESTS == 2
  //   srunner_add_suite(runner, round_suite1());
  //   srunner_add_suite(runner, round_suite2());
  //   srunner_add_suite(runner, round_suite3());
  // #endif

  //   srunner_add_suite(runner, truncate_suite0());

  // #if TESTS == 2
  //   srunner_add_suite(runner, truncate_suite1());
  //   srunner_add_suite(runner, truncate_suite2());
  //   srunner_add_suite(runner, truncate_suite3());
  // #endif

  //   srunner_add_suite(runner, negate_suite0());

  // #if TESTS == 2
  //   srunner_add_suite(runner, negate_suite1());
  //   srunner_add_suite(runner, negate_suite2());
  //   srunner_add_suite(runner, negate_suite3());
  // #endif

  //   srunner_add_suite(runner, debug0());

  // #if TESTS == 2
  //   srunner_add_suite(runner, debug1());
  //   srunner_add_suite(runner, debug2());
  //   srunner_add_suite(runner, debug3());
  // #endif
}
#endif