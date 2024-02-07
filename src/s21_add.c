#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  am_code code = AM_ERR;

  if (result != NULL) {
    s21_reset(result);
    code = AM_OK;
    s21_big_decimal big_value_1, big_value_2, res;

    s21_decimal_to_big(value_1, &big_value_1);
    s21_decimal_to_big(value_2, &big_value_2);

    res = s21_add_big(big_value_1, big_value_2);

    int new_scale = s21_post_normalization(&res);

    if (new_scale == AM_OK) {
      s21_big_to_decimal(res, result);
      s21_set_scale(result, new_scale);
    } else {
      code = new_scale;
    }
  }

  return code;
}

s21_big_decimal s21_add_big(s21_big_decimal value_1, s21_big_decimal value_2) {
  s21_big_decimal res;

  int exp_1 = s21_get_scale_big(value_1);
  int exp_2 = s21_get_scale_big(value_2);

  if (exp_1 != exp_2) {
    s21_equalize_scale_big(&value_1, &value_2);
  }

  int sign_1 = s21_get_sign_big(value_1);
  int sign_2 = s21_get_sign_big(value_2);

  if (sign_1 != sign_2) {
    int bigger = s21_mantisa_compare_big(value_1, value_2);
    switch (bigger) {
      case 1:
        res = s21_sub_mantissas_big(value_2, value_1);
        break;
      default:
        res = s21_sub_mantissas_big(value_1, value_2);
        break;
    }

    s21_set_sign_big(&res, bigger == 0 ? sign_1 : sign_2);
  } else {
    res = s21_add_mantissas_big(value_1, value_2);

    // convert big res to decimal result; catch errors
    s21_set_sign_big(&res, sign_1);
  }

  return res;
}
