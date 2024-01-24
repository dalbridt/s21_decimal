#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  int exp_1 = get_scale(value_1);
  int exp_2 = get_scale(value_2);

  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);

  if (exp_1 != exp_2) {
    if (exp_1 < exp_2) {
      equalize_scale(&value_1, exp_2);
      set_scale(result, exp_2);
    } else {
      equalize_scale(&value_2, exp_1);
      set_scale(result, exp_1);
    }
  }
  // debug_display_decimal("1", value_1);
  // debug_display_decimal("2", value_2);

  if (sign_1 != sign_2) {
    int bigger = s21_mantisa_compare(&value_1, &value_2);
    switch (bigger) {
      case 1:
        *result = sub_decimals_mantissa(&value_2, &value_1);
        break;
      case 0:
        *result = sub_decimals_mantissa(&value_1, &value_2);
        break;
      default:
        // результат = 0;
        break;
    }
    set_sign(result, bigger == 0 ? sign_1 : sign_2);
  } else {
    *result = add_decimals_mantissa(&value_1, &value_2);
    set_sign(result, sign_1);
  }
  return flag;
}
