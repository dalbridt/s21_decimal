#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  am_code code = AM_ERR;

  if (result != NULL) {
    code = AM_OK;
    s21_big_decimal big_value_1, big_value_2;

    s21_decimal_to_big(value_1, &big_value_1);
    s21_decimal_to_big(value_2, &big_value_2);

    int exp_1 = s21_get_scale(value_1);
    int exp_2 = s21_get_scale(value_2);

    int sign_1 = s21_get_sign(value_1);
    int sign_2 = s21_get_sign(value_2);

    if (exp_1 != exp_2) {
      s21_equalize_scale(&value_1, &value_2);
    }

    if (sign_1 != sign_2) {
      int bigger = s21_mantisa_compare(&value_1, &value_2);
      switch (bigger) {
        case 1:
          *result = s21_sub_mantissas(&value_2, &value_1);
          break;
        default:
          *result = s21_sub_mantissas(&value_1, &value_2);
          break;
      }
      s21_set_sign(result, bigger == 0 ? sign_1 : sign_2);
    } else {
      *result = s21_add_mantissas(&value_1, &value_2);
      s21_set_sign(result, sign_1);
    }
  }

  return code;
}
