#include "s21_decimal.h"

/*S21_DECIMAL BASIC HELPERS*/

void s21_reset(s21_decimal *src) { *src = (s21_decimal){0}; }

void s21_reset_big(s21_big_decimal *src) { *src = (s21_big_decimal){0}; }

int s21_is_zero(s21_decimal src) {
  return (src.bits[0] == 0 && src.bits[1] == 0 && src.bits[2] == 0);
}

long double s21_get_mantissa(s21_decimal *src) {
  unsigned const int *b = &src->bits[0];

  long double mantissa = 0;
  long double power = 1;
  for (short i = 0; i < 0x60; i++, power *= 2) {
    unsigned int byte = (b[i / 0x20] >> i) & 1;
    mantissa += byte * power;
  }
  return mantissa;
}

int s21_get_sign(s21_decimal num) { return (num.bits[3] & MINUS) != 0; }

int s21_get_sign_big(s21_big_decimal num) { return (num.scale & MINUS) != 0; }

void s21_set_sign(s21_decimal *num, int sign_value) {
  int mask = MINUS;
  if (sign_value == 0) {
    num->bits[3] &= ~mask;
  } else {
    num->bits[3] |= mask;
  }
}

void s21_set_sign_big(s21_big_decimal *num, int sign_value) {
  int mask = MINUS;
  if (sign_value == 0)
    num->scale &= ~mask;
  else
    num->scale |= mask;
}

int s21_get_scale(s21_decimal num) { return ((SCALE & num.bits[3]) >> 16); }

int s21_get_scale_big(s21_big_decimal num) {
  return ((SCALE & num.scale) >> 16);
}

void s21_set_scale(s21_decimal *num, int scale_value) {
  num->bits[3] &= MINUS;
  scale_value <<= 16;
  num->bits[3] |= scale_value;
}

void s21_set_scale_big(s21_big_decimal *num, int scale_value) {
  int sign = s21_get_sign_big(*num);
  num->scale = 0;
  scale_value <<= 16;
  num->scale = scale_value;
  s21_set_sign_big(num, sign);
}

int s21_get_bit(s21_decimal src, int index) {
  int mask = 1u << (index % 32);
  return (src.bits[index / 32] & mask) != 0;
}

int s21_get_bit_big(s21_big_decimal src, int index) {
  unsigned long mask = 1UL << (index % 32);
  return (src.bits[index / 32] & mask) != 0;
}

void s21_set_bit_big(s21_big_decimal *dst, int index, int bit) {
  unsigned long mask = 1UL << (index % 32);
  if (bit == 0) {
    dst->bits[index / 32] = dst->bits[index / 32] & ~mask;
  } else {
    dst->bits[index / 32] = dst->bits[index / 32] | mask;
  }
}

void s21_mantissa_shift_l(s21_decimal *dec, int offset) {
  unsigned int *byte;
  size_t size = sizeof(unsigned int);
  size--;
  size_t basic_size = size;
  s21_switch_endian(dec);
  for (int i = 0; i < offset; i++) {
    for (byte = dec->bits; basic_size--; ++byte) {
      unsigned int bit = 0;
      if (basic_size) {
        bit = (byte[1] & MINUS) ? 1 : 0;
      }
      *byte <<= 1;
      *byte |= bit;
    }
    basic_size = size;
  }
  s21_switch_endian(dec);
}

int s21_big_mantissa_shift_l(s21_big_decimal *dst, int offset) {
  unsigned int *byte;
  int error = 0;
  size_t size = sizeof(unsigned int) * 4;
  size_t basic_size = size;
  s21_switch_endian_big(dst);
  for (int i = 0; i < offset; i++) {
    for (byte = dst->bits; basic_size--; ++byte) {
      unsigned int bit = 0;
      if (basic_size) {
        bit = (byte[1] & MINUS) ? 1 : 0;
      }
      *byte <<= 1;
      *byte |= bit;
    }
    basic_size = size;
  }
  s21_switch_endian_big(dst);

  return error;
}

void s21_mantissa_shift_r(s21_decimal *dec, int offset) {
  s21_switch_endian(dec);
  while (offset--) {
    int carry = 0;
    for (int i = 0; i < 3; ++i) {
      int next = (dec->bits[i] & 1) ? MINUS : 0;
      dec->bits[i] = carry | (dec->bits[i] >> 1);
      carry = next;
    }
  }
  s21_switch_endian(dec);
}

void s21_big_mantissa_shift_r(s21_big_decimal *dec, int offset) {
  s21_switch_endian_big(dec);
  while (offset--) {
    int carry = 0;
    for (int i = 0; i < 16; ++i) {
      int next = (dec->bits[i] & 1) ? MINUS : 0;
      dec->bits[i] = carry | (dec->bits[i] >> 1);
      carry = next;
    }
  }
  s21_switch_endian_big(dec);
}

void s21_decimal_to_big(s21_decimal src, s21_big_decimal *dst) {
  s21_reset_big(dst);
  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->scale = src.bits[3];
}

am_code s21_big_to_decimal(s21_big_decimal src, s21_decimal *dst) {
  am_code flag = AM_ERR;
  if (dst != NULL) {
    flag = s21_post_normalization(&src);
    s21_reset(dst);
    dst->bits[0] = src.bits[0];
    dst->bits[1] = src.bits[1];
    dst->bits[2] = src.bits[2];
    dst->bits[3] = src.scale;
  }

  return flag;
}

void s21_switch_endian(s21_decimal *x) {
  unsigned int temp0 = x->bits[0];
  unsigned int temp2 = x->bits[2];
  x->bits[0] = temp2;
  x->bits[2] = temp0;
}

void s21_switch_endian_big(s21_big_decimal *x) {
  for (int i = 0; i < 0x8; i++) {
    unsigned int temp = x->bits[i];
    x->bits[i] = x->bits[0xF - i];
    x->bits[0xF - i] = temp;
  }
}

void s21_equalize_scale_big(s21_big_decimal *value_1,
                            s21_big_decimal *value_2) {
  int exp_1 = s21_get_scale_big(*value_1);
  int exp_2 = s21_get_scale_big(*value_2);
  // printf("scale: %d, %d\n", exp_1, exp_2);
  if (exp_1 != exp_2) {
    if (exp_1 < exp_2) {
      for (; exp_1 < exp_2; exp_1++) {
        s21_x10_big(value_1);
        s21_set_scale_big(value_1, exp_2);
      }
    } else {
      for (; exp_2 < exp_1; exp_2++) {
        s21_x10_big(value_2);
        s21_set_scale_big(value_2, exp_1);
      }
    }
  }
}

s21_decimal s21_add_mantissas(s21_decimal x, s21_decimal y) {
  s21_decimal result = x;
  unsigned int carry = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t tmp = (uint64_t)x.bits[i] + y.bits[i] + carry;
    result.bits[i] = (uint32_t)tmp;
    carry = tmp >> 32;
  }
  return result;
}

s21_big_decimal s21_add_mantissas_big(s21_big_decimal x, s21_big_decimal y) {
  s21_big_decimal result = x;
  unsigned int carry = 0;
  for (int i = 0; i < 16; i++) {
    uint64_t tmp = (uint64_t)x.bits[i] + y.bits[i] + carry;
    result.bits[i] = (uint32_t)tmp;
    carry = tmp >> 32;
  }
  return result;
}

s21_decimal s21_sub_mantissas(s21_decimal x, s21_decimal y) {
  s21_decimal result = x;
  unsigned int borrow = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t tmp = (uint64_t)x.bits[i] - y.bits[i] - borrow;
    result.bits[i] = (uint32_t)tmp;
    borrow = (tmp >> 32) & 1;
  }
  return result;
}

s21_big_decimal s21_sub_mantissas_big(s21_big_decimal x, s21_big_decimal y) {
  s21_big_decimal result = x;
  unsigned int borrow = 0;
  for (int i = 0; i < 16; i++) {
    uint64_t tmp = (uint64_t)x.bits[i] - y.bits[i] - borrow;
    result.bits[i] = (uint32_t)tmp;
    borrow = (tmp >> 32) & 1;
  }
  return result;
}

int s21_mantisa_compare_big(s21_big_decimal value_1, s21_big_decimal value_2) {
  int flag = -1;

  for (int i = 15; i >= 0; i--) {
    if (value_1.bits[i] == value_2.bits[i]) {
      continue;
    } else {
      flag = value_1.bits[i] > value_2.bits[i];
      break;
    }
  }
  return flag;
}

int s21_mul_big(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal *result) {
  int count = 0, error = 0;

  int res_scale = s21_get_scale_big(value_1) + s21_get_scale_big(value_2);
  for (int i = 0; i < 512; i++) {
    if (s21_get_bit_big(value_2, i)) {
      error = s21_big_mantissa_shift_l(&value_1, i - count);
      *result = s21_add_mantissas_big(value_1, *result);
      count = i;
    }
  }
  s21_set_scale_big(result, res_scale);
  return error;
}

void s21_div10(s21_decimal *src, unsigned int roundup) {
  s21_decimal src_copy = *src;
  s21_decimal src_copy2 = *src;

  s21_mantissa_shift_r(&src_copy, 1);
  s21_mantissa_shift_r(&src_copy2, 2);
  s21_decimal q = s21_add_mantissas(src_copy, src_copy2);

  for (int i = 4; i < 512; i *= 2) {
    src_copy = q;
    s21_mantissa_shift_r(&src_copy, i);
    q = s21_add_mantissas(q, src_copy);
  }

  s21_mantissa_shift_r(&q, 3);

  src_copy2 = q;
  s21_mantissa_shift_l(&src_copy2, 2);
  src_copy2 = s21_add_mantissas(q, src_copy2);

  s21_mantissa_shift_l(&src_copy2, 1);

  s21_decimal r = s21_sub_mantissas(*src, src_copy2);

  q = s21_add_mantissas(q, src_copy);

  if (r.bits[0] >= (0xA - roundup)) {
    s21_decimal one;
    s21_set_one(&one);
    q = s21_add_mantissas(q, one);
  }

  *src = q;
}

void s21_div10_big(s21_big_decimal *src, unsigned int roundup) {
  s21_big_decimal src_copy = *src;
  s21_big_decimal src_copy2 = *src;
  s21_big_mantissa_shift_r(&src_copy, 1);
  s21_big_mantissa_shift_r(&src_copy2, 2);
  s21_big_decimal q = {0}, temp = {0};
  q = s21_add_mantissas_big(src_copy, src_copy2);

  for (int i = 4; i < 512; i *= 2) {
    src_copy = q;
    s21_big_mantissa_shift_r(&src_copy, i);
    temp = s21_add_mantissas_big(src_copy, q);
    q = temp;
  }
  s21_big_mantissa_shift_r(&q, 3);
  src_copy2 = q;
  s21_big_mantissa_shift_l(&src_copy2, 2);
  s21_reset_big(&temp);
  temp = s21_add_mantissas_big(src_copy2, q);
  src_copy2 = temp;

  s21_reset_big(&temp);
  temp = s21_add_mantissas_big(src_copy, q);

  if (temp.bits[0] >= (0xA - roundup)) {
    s21_big_decimal one;
    s21_set_one_big(&one);
    s21_reset_big(&q);
    q = s21_add_mantissas_big(temp, one);
  }

  *src = q;
}

void s21_x10(s21_decimal *src) {
  s21_decimal dec3 = *src;
  s21_decimal dec2 = *src;

  s21_mantissa_shift_l(&dec3, 3);
  s21_mantissa_shift_l(&dec2, 1);

  *src = s21_add_mantissas(dec2, dec3);
}

void s21_x10_big(s21_big_decimal *src) {
  s21_big_decimal dec3 = *src;
  s21_big_decimal dec2 = *src;

  s21_big_mantissa_shift_l(&dec3, 3);
  s21_big_mantissa_shift_l(&dec2, 1);

  *src = s21_add_mantissas_big(dec2, dec3);
}

void s21_divide_big(s21_big_decimal dividend, s21_big_decimal divisor,
                    s21_big_decimal *quotient, s21_big_decimal *remainder,
                    int stop) {
  int num_bits;
  int bit;

  s21_equalize_scale_big(&dividend, &divisor);
  int sign_dividend = s21_get_sign_big(dividend);
  int sign_divisor = s21_get_sign_big(divisor);
  s21_set_sign_big(&dividend, 0);
  s21_set_sign_big(&divisor, 0);

  s21_big_decimal d;
  s21_reset_big(&d);

  s21_reset_big(remainder);
  s21_reset_big(quotient);

  int dividend_scale = s21_get_scale_big(dividend);
  int divisor_scale = s21_get_scale_big(divisor);
  int div_new_scale = dividend_scale;

  if (stop == 1) {
    for (int i = 0; i < 33; i++) {
      s21_x10_big(&dividend);
      div_new_scale++;
    }
  }

  num_bits = 512;

  while (s21_is_less_big(*remainder, divisor) && num_bits > 0) {
    bit = s21_get_bit_big(dividend, 512 - 1);
    s21_big_mantissa_shift_l(remainder, 1);
    if (bit)
      s21_set_bit_big(remainder, 0, bit);

    d = dividend;
    s21_big_mantissa_shift_l(&dividend, 1);

    num_bits--;
  }

  dividend = d;
  s21_big_mantissa_shift_r(remainder, 1);
  num_bits++;

  for (int i = 0; i < num_bits; i++) {
    s21_big_decimal t;
    int q;
    bit = s21_get_bit_big(dividend, 512 - 1);
    s21_big_mantissa_shift_l(remainder, 1);
    if (bit)
      s21_set_bit_big(remainder, 0, bit);

    t = s21_sub_mantissas_big(*remainder, divisor);

    q = !s21_get_bit_big(t, 512 - 1);

    s21_big_mantissa_shift_l(&dividend, 1);
    s21_big_mantissa_shift_l(quotient, 1);
    if (q) {
      s21_set_bit_big(quotient, 0, q);
      *remainder = t;
    }
  }
  if (stop == 0) {
    s21_big_decimal quot_2 = {0};
    s21_big_decimal rem_2 = {0};
    s21_divide_big(*remainder, divisor, &quot_2, &rem_2, 1);
    *quotient = s21_add_big(*quotient, quot_2);
  } else {
    s21_set_scale_big(quotient, div_new_scale + dividend_scale - divisor_scale);
  }
  s21_set_sign_big(quotient, sign_dividend ^ sign_divisor);
}

void s21_upscale_x10(s21_decimal *dec) {
  s21_x10(dec);
  s21_set_scale(dec, (s21_get_scale(*dec) + 1));
}

void s21_set_one(s21_decimal *dec) {
  s21_reset(dec);
  dec->bits[0] = 1u;
}

void s21_set_one_big(s21_big_decimal *dec) {
  s21_reset_big(dec);
  dec->bits[0] = 1u;
}

void s21_decrease_scale_big(s21_big_decimal *dst, int n) {
  int scale = s21_get_scale_big(*dst);
  for (int i = 0; i < n; i++) {
    scale--;
  }
  s21_set_scale_big(dst, scale);
}

am_code s21_post_normalization(s21_big_decimal *result) {
  am_code flag = AM_ERR;
  if (result != NULL) {
    flag = AM_OK;
    int scale = s21_get_scale_big(*result);
    int dop = 0;

    while (true) {
      bool bits = false;
      for (int i = 3; i < 16; i++) {
        bits += result->bits[i] > 0;
      }
      bits = bits && scale > 0;
      if (!bits)
        break;
      if (scale == 1 && result->bits[3])
        dop = 1;
      s21_decrease_scale_big(result, 1);
      s21_div10_big(result, 0);
      scale--;
    }

    while ((result->bits[0] || result->bits[1] || result->bits[2]) &&
           scale > 28) {
      s21_decrease_scale_big(result, 1);
      s21_div10_big(result, 0);
      scale--;
    }

    if (dop && scale == 0 && result->bits[3] == 0 &&
        s21_get_bit_big(*result, 0)) {
      s21_set_bit_big(result, 0, 0);
    }
    for (int i = 3; i < 16; i++) {
      if (result->bits[i]) {
        flag = AM_OF;
        break;
      }
    }

    if (flag == AM_OF && s21_get_sign_big(*result)) {
      flag = AM_NOF;
    }
  }

  return flag;
}

val_code s21_decimal_validation(s21_decimal value) {
  val_code flag = VAL_OK;
  int scale = s21_get_scale(value);
  if (scale > 28) {
    flag = VAL_ERR;
  } else {
    for (int i = 96; i < 112; i++) {
      if (s21_get_bit(value, i) != 0) {
        flag = VAL_ERR;
        break;
      }
    }
    for (int i = 120; i < 127 && flag; i++) {
      if (s21_get_bit(value, i) != 0) {
        flag = VAL_ERR;
        break;
      }
    }
  }

  return flag;
}

// void s21_increase_scale_big(s21_big_decimal* dst, int n) {
//   int scale = s21_get_scale_big(*dst);
//   for (int i = 0; i < n; i++) {
//     scale++;
//   }
//   s21_set_scale_big(dst, scale);
// }

int s21_is_big_zero(s21_big_decimal src) {
  int flag = 1;
  for (int i = 0; i < 16; i++) {
    if (src.bits[i] == 0)
      continue;
    flag = 0;
    break;
  }
  return flag;
}

// // returns : -1 if equal, 1 if left bigger, 0 if right bigger
// int s21_mantisa_compare(s21_decimal value_1, s21_decimal value_2) {
//   int flag = -1;

//   for (int i = 2; i >= 0; i--) {
//     if (value_1.bits[i] == value_2.bits[i]) {
//       continue;
//     } else {
//       flag = value_1.bits[i] > value_2.bits[i];
//       break;
//     }
//   }
//   return flag;
// }

// void s21_equalize_scale(s21_decimal* value_1, s21_decimal* value_2) {
//   int exp_1 = s21_get_scale(*value_1);
//   int exp_2 = s21_get_scale(*value_2);

//   if (exp_1 != exp_2) {
//     if (exp_1 < exp_2) {
//       for (; exp_1 < exp_2; exp_1++) {
//         s21_x10(value_1);
//         s21_set_scale(value_1, exp_2);
//       }
//     } else {
//       for (; exp_2 < exp_1; exp_2++) {
//         s21_x10(value_2);
//         s21_set_scale(value_2, exp_1);
//       }
//     }
//   }
// }

// long double s21_get_mantissa_big(s21_big_decimal* src) {
//   unsigned int* b = &src->bits[0];
//   unsigned int byte;

//   long double mantissa = 0;
//   long double power = 1;
//   for (short i = 0; i < 0x200; i++, power *= 2) {
//     byte = (b[i / 0x20] >> i) & 1;
//     mantissa += byte * power;
//   }
//   return mantissa;
// }

// void s21_upscale_x10_big(s21_big_decimal* dec) {
//   s21_x10_big(dec);
//   s21_set_scale_big(dec, (s21_get_scale_big(*dec) + 1));
// }

// void s21_set_bit(s21_decimal* src, int index, int value) {
//   int arr_index = index / 32;
//   int bit_index = index % 32;
//   if (value == 1) {
//     src->bits[arr_index] |= (1u << bit_index);
//   } else if (value == 0) {
//     src->bits[arr_index] &= ~(1u << bit_index);
//   }
// }

// // Степени чисел принимаются за 10^0, знаки не учитываются
// void s21_add_big(s21_big_decimal value_1, s21_big_decimal value_2,
//                  s21_big_decimal* result) {
//   int res = 0, overflow = 0;
//   for (int i = 0; i < 448; i++) {
//     res = s21_get_bit_big(value_1, i) + s21_get_bit_big(value_2, i) +
//     overflow; overflow = res / 2; s21_set_bit_big(result, i, res % 2);
//   }
// }

// // Степени чисел принимаются за 10^0, знаки не учитываются
// void s21_sub_big(s21_big_decimal value_1, s21_big_decimal value_2,
//                  s21_big_decimal* result) {
//   int tmp = 0, res = 0;
//   for (int i = 0; i < 448; i++) {
//     res = s21_get_bit_big(value_1, i) - s21_get_bit_big(value_2, i) - tmp;
//     tmp = res < 0;
//     res = abs(res);
//     s21_set_bit_big(result, i, res % 2);
//   }
// }