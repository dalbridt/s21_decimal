#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  am_code code = AM_OK;

  if (result != NULL) {
    s21_big_decimal big_value_1, big_value_2;

    decimal_to_big(value_1, &big_value_1);
    decimal_to_big(value_2, &big_value_2);

    int exp_1 = get_scale(value_1);
    int exp_2 = get_scale(value_2);

    int sign_1 = get_sign(value_1);
    int sign_2 = get_sign(value_2);

    if (exp_1 != exp_2) {
      equalize_scale(&value_1, &value_2);
    }
    // debug_display_decimal("1", value_1);
    // debug_display_decimal("2", value_2);

    if (sign_1 != sign_2) {
      int bigger = s21_mantisa_compare(&value_1, &value_2);
      switch (bigger) {
        case 1:
          *result = sub_decimals_mantissa(&value_2, &value_1);
          break;
        default:
          *result = sub_decimals_mantissa(&value_1, &value_2);
          break;
      }
      set_sign(result, bigger == 0 ? sign_1 : sign_2);
    } else {
      *result = add_decimals_mantissa(&value_1, &value_2);
      set_sign(result, sign_1);
    }
  } else {
    code = AM_ERR;
  }

  return code;
}
