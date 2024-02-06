#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal dec_rem;

  divide_decimal(value_1, value_2, result, &dec_rem, 0);
  return 0;
}

void divide_decimal(s21_decimal dividend, s21_decimal divisor,
                    s21_decimal *quotient, s21_decimal *remainder, int stop) {
  int num_bits;
  int q, bit;
  int i;

  equalize_scale(&dividend, &divisor);
  int sign_dividend = get_sign(dividend);
  int sign_divisor = get_sign(divisor);
  set_sign(&dividend, 0);
  set_sign(&divisor, 0);

  s21_decimal d, t;

  reset_decimal(remainder);
  reset_decimal(quotient);

  if (is_decimal_zero(divisor)) return;

  int dividend_scale = get_scale(dividend);
  int divisor_scale = get_scale(divisor);
  int div_new_scale = dividend_scale;

  if (stop == 1) {
    for (int i = 0; i < 7; i++) {
      decimal_x10(&dividend);
      div_new_scale++;
    }
  }

  if (s21_is_equal(divisor, dividend)) {
    decimal_one(quotient);
    return;
  }

  num_bits = 96;

  while (s21_is_less(*remainder, divisor) && num_bits > 0) {
    bit = get_bit(dividend, 95);
    decimal_mantissa_shift_l(remainder, 1);
    if (bit) set_bit(remainder, 0, bit);

    d = dividend;
    decimal_mantissa_shift_l(&dividend, 1);

    num_bits--;
  }

  dividend = d;
  decimal_mantissa_shift_r(remainder, 1);
  num_bits++;

  for (i = 0; i < num_bits; i++) {
    bit = get_bit(dividend, 95);
    decimal_mantissa_shift_l(remainder, 1);
    if (bit) set_bit(remainder, 0, bit);

    t = sub_decimals_mantissa(remainder, &divisor);

    q = !get_bit(t, 95);

    decimal_mantissa_shift_l(&dividend, 1);
    decimal_mantissa_shift_l(quotient, 1);
    if (q) set_bit(quotient, 0, q);

    if (q) {
      *remainder = t;
    }
  }
  if (stop == 0) {
    s21_decimal quot_2 = {0};
    s21_decimal rem_2 = {0};
    divide_decimal(*remainder, divisor, &quot_2, &rem_2, 1);
    s21_add(*quotient, quot_2, quotient);
  } else {
    set_scale(quotient, div_new_scale + dividend_scale - divisor_scale);
  }
  set_sign(quotient, sign_dividend ^ sign_divisor);
}
