#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "s21_decimal.h"
#define ITER 5
#define TOL 1e-06

float rand_double(int random, float min, float max);

float rand_double(int random, float min, float max) {
  srand(random * time(NULL));
  float value = min + ((float)rand() / RAND_MAX) * (max - min);
  return value;
}

START_TEST(t_add) {  // 01. s21_add
  //
}
END_TEST

START_TEST(t_sub) {  // 02. s21_sub
  //
}
END_TEST

START_TEST(t_mul) {  // 03. s21_mul
  //
}
END_TEST

START_TEST(t_div) {  // 04. s21_div
  //
}
END_TEST

START_TEST(t_is_less) {  // 05. s21_is_less
  //
}
END_TEST

START_TEST(t_is_less_or_equal) {  // 06. s21_is_less_or_equal
  //
}
END_TEST

START_TEST(t_is_greater) {  // 07. s21_is_greater
  //
}
END_TEST

START_TEST(t_is_greater_or_equal) {  // 08. s21_is_greater_or_equal
  //
}
END_TEST

START_TEST(t_is_equal) {  // 09. s21_is_equal
  //
}
END_TEST

START_TEST(t_is_not_equal) {  // 10. s21_is_not_equal
  //
}
END_TEST

START_TEST(t_from_int_to_decimal) {  // 11. s21_from_int_to_decimal
  //
}
END_TEST

START_TEST(t_from_float_to_decimal) {  // 12. s21_from_float_to_decimal
  //
}
END_TEST

START_TEST(t_from_decimal_to_int) {  // 13. s21_from_decimal_to_int
  //
}
END_TEST

START_TEST(t_from_decimal_to_float) {  // 14. s21_from_decimal_to_float
  //
}
END_TEST

START_TEST(t_floor) {  // 15. s21_floor
  //
}
END_TEST

START_TEST(t_round) {  // 16. s21_round
  //
}
END_TEST

START_TEST(t_truncate) {  // 17. s21_truncate
  //
}
END_TEST

START_TEST(t_negate) {  // 18. s21_negate
  //
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