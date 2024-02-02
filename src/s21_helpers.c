#include "s21_decimal.h"

/*S21_DECIMAL BASIC HELPERS*/

int get_scale(s21_decimal num) { return ((SCALE & num.bits[3]) >> 16); }

void set_scale(s21_decimal* num, int scale_value) {
  num->bits[3] &= 0x80000000;
  scale_value <<= 16;
  num->bits[3] |= scale_value;
}

int get_sign(s21_decimal num) { return (num.bits[3] & MINUS) != 0; }

void set_sign(s21_decimal* num, int sign_value) {
  int mask = MINUS;
  if (sign_value == 0)
    num->bits[3] &= ~mask;
  else
    num->bits[3] |= mask;
}

int get_bit(s21_decimal src, int index) {
  int mask = 1u << (index % 32);
  return (src.bits[index / 32] & mask) != 0;
}

void set_bit(s21_decimal* src, int index, int value) {
  int arr_index = index / 32;
  int bit_index = index % 32;
  if (value == 1) {
    src->bits[arr_index] |= (1u << bit_index);
  } else if (value == 0) {
    src->bits[arr_index] &= ~(1u << bit_index);
  }
}

void reset_decimal(s21_decimal* src) { *src = (s21_decimal){0}; }

int decimal_is_zero(s21_decimal src) {
  return (src.bits[0] == 0 && src.bits[1] == 0 && src.bits[2] == 0);
}

void max_decimal(s21_decimal* dst) {
  dst->bits[0] = 0b11111111111111111111111111111111;
  dst->bits[1] = 0b11111111111111111111111111111111;
  dst->bits[2] = 0b11111111111111111111111111111111;
  dst->bits[3] = 0b00000000000111000000000000000000;
}

void min_decimal(s21_decimal* dst) {
  dst->bits[0] = 0b11111111111111111111111111111111;
  dst->bits[1] = 0b11111111111111111111111111111111;
  dst->bits[2] = 0b11111111111111111111111111111111;
  dst->bits[3] = 0b10000000000111000000000000000000;
}

void switchEndian(s21_decimal* x) {
  unsigned int temp0 = x->bits[0];
  unsigned int temp2 = x->bits[2];
  x->bits[0] = temp2;
  x->bits[2] = temp0;
}

void decimal_mantissa_shift_l(s21_decimal* dec, int offset) {
  unsigned int* byte;
  size_t size = sizeof(unsigned int);
  size--;
  size_t basic_size = size;

  switchEndian(dec);

  for (int i = 0; i < offset; i++) {
    for (byte = dec->bits; basic_size--; ++byte) {
      unsigned int bit = 0;
      if (basic_size) {
        bit = (byte[1] & (1 << (32 - 1))) ? 1 : 0;
      }
      *byte <<= 1;
      *byte |= bit;
    }
    basic_size = size;
  }

  switchEndian(dec);
}

void decimal_mantissa_shift_r(s21_decimal* dec, int offset) {
  switchEndian(dec);

  while (offset--) {
    int carry = 0;
    for (int i = 0; i < 3; ++i) {
      int next = (dec->bits[i] & 1) ? 0x80000000 : 0;
      dec->bits[i] = carry | (dec->bits[i] >> 1);
      carry = next;
    }
  }

  switchEndian(dec);
}

long double get_mantissa(s21_decimal* src) {
  unsigned int* b = &src->bits[0];
  unsigned int byte;

  long double mantissa = 0;
  long double power = 1;
  for (short i = 0; i < 0x60; i++, power *= 2) {
    byte = (b[i / 0x20] >> i) & 1;
    mantissa += byte * power;
  }
  return mantissa;
}

/*BIG DECIMAL BASIC HELPERS*/

int get_bit_big_decimal(s21_big_decimal src, int index) {
  unsigned long mask = 1UL << (index % 64);
  return (src.bits[index / 64] & mask) != 0;
}

void set_bit_big_decimal(s21_big_decimal* dst, int index, int bit) {
  unsigned long mask = 1UL << (index % 64);
  if (bit == 0)
    dst->bits[index / 64] = dst->bits[index / 64] & ~mask;
  else
    dst->bits[index / 64] = dst->bits[index / 64] | mask;
}

int get_sign_big_decimal(s21_big_decimal num) {
  return (num.scale & MINUS) != 0;
}

void set_sign_big_decimal(s21_big_decimal* num, int sign_value) {
  int mask = MINUS;
  if (sign_value == 0)
    num->scale &= ~mask;
  else
    num->scale |= mask;
}

int get_scale_big_decimal(s21_big_decimal num) {
  return ((SCALE & num.scale) >> 16);
}

void set_scale_big_decimal(s21_big_decimal* num, int scale_value) {
  int sign = get_sign_big_decimal(*num);
  num->scale = 0;
  scale_value <<= 16;
  num->scale = num->scale | scale_value;
  set_sign_big_decimal(num, sign);
}

void reset_big_decimal(s21_big_decimal* src) { *src = (s21_big_decimal){0}; }

void switch_endian_big_decimal(s21_big_decimal* x) {
  uint64_t temp0 = x->bits[0];
  uint64_t temp1 = x->bits[1];
  uint64_t temp2 = x->bits[2];
  uint64_t temp4 = x->bits[4];
  uint64_t temp5 = x->bits[5];
  uint64_t temp6 = x->bits[6];

  x->bits[0] = temp6;
  x->bits[6] = temp0;
  x->bits[1] = temp5;
  x->bits[5] = temp1;
  x->bits[2] = temp4;
  x->bits[4] = temp2;
}

int big_decimal_mantissa_shift_l(s21_big_decimal* dst, int offset) {
  int error = 0;
  uint64_t buffer[7] = {0};
  for (int i = 0; i < offset; i++) {
    for (int j = 0; j < 6; j++) {
      buffer[j] = get_bit_big_decimal(*dst, (j + 1) * 64 - 1);
    }
    for (int j = 6; j > 0 && !error; j--) {
      if (get_bit_big_decimal(*dst, 447)) error = 1;
      dst->bits[j] <<= 1;
      set_bit_big_decimal(dst, j * 64, buffer[j - 1]);
    }
    dst->bits[0] <<= 1;
  }
  return error;
}

void big_decimal_mantissa_shift_r(s21_big_decimal* dst, int offset) {
  uint64_t buffer[6] = {0};
  for (int i = 0; i < offset; i++) {
    for (int j = 0; j < 6; j++) {
      buffer[j] = get_bit_big_decimal(*dst, (j + 1) * 64);
    }
    for (int j = 0; j < 6; j++) {
      dst->bits[j] >>= 1;
      set_bit_big_decimal(dst, (j + 1) * 64 - 1, buffer[j]);
    }
    dst->bits[6] >>= 1;
  }
}

long double get_mantissa_big_decimal(s21_big_decimal* src) {
  uint64_t* b = &src->bits[0];
  unsigned int byte;

  long double mantissa = 0;
  long double power = 1;
  for (short i = 0; i < 0x1C0; i++, power *= 2) {
    byte = (b[i / 0x40] >> i) & 1;
    mantissa += byte * power;
  }
  return mantissa;
}

int big_decimal_is_zero(s21_big_decimal src) {
  return (src.bits[0] == 0 && src.bits[1] == 0 && src.bits[2] == 0 &&
          src.bits[3] == 0 && src.bits[4] == 0 && src.bits[5] == 0 &&
          src.bits[6] == 0);
}

/*IMPORT FUNCTIONS*/

void import_to_big_decimal(s21_decimal src, s21_big_decimal* dst) {
  dst->bits[0] = src.bits[1] & MAX4BITE;
  dst->bits[0] <<= 32;
  dst->bits[0] |= src.bits[0] & MAX4BITE;
  dst->bits[1] = src.bits[2] & MAX4BITE;
  dst->scale = src.bits[3] & MAX4BITE;
}

void import_to_small_decimal(s21_big_decimal src, s21_decimal* dst) {
  // normalize
  dst->bits[0] = src.bits[0] & MAX4BITE;
  src.bits[0] >>= 32;
  dst->bits[1] = src.bits[0] & MAX4BITE;
  dst->bits[2] = src.bits[1] & MAX4BITE;
  dst->bits[3] = src.scale & MAX4BITE;
}

/*ARITHMETICS FUNCTIONS*/

s21_decimal add_decimals_mantissa(s21_decimal* x, s21_decimal* y) {
  s21_decimal result = *x;
  unsigned int carry = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t tmp = (uint64_t)x->bits[i] + y->bits[i] + carry;
    result.bits[i] = (uint32_t)tmp;
    carry = tmp >> 32;
  }
  return result;
}

s21_decimal sub_decimals_mantissa(s21_decimal* x, s21_decimal* y) {
  s21_decimal result = *x;
  unsigned int borrow = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t tmp = (uint64_t)x->bits[i] - y->bits[i] - borrow;
    result.bits[i] = (uint32_t)tmp;
    borrow = (tmp >> 32) & 1;
  }
  return result;
}

// Степени чисел принимаются за 10^0, знаки не учитываются
void add_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal* result) {
  int res = 0, overflow = 0;
  for (int i = 0; i < 448; i++) {
    res = get_bit_big_decimal(value_1, i) + get_bit_big_decimal(value_2, i) +
          overflow;
    overflow = res / 2;
    set_bit_big_decimal(result, i, res % 2);
  }
}

int mul_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal* result) {
  int count = 0, error = 0;
  // if (get_sign_big_decimal(value_1) != get_sign_big_decimal(value_2))
  //   set_sign_big_decimal(result, 1); проверяем это в материнской функции
  int res_scale =
      get_scale_big_decimal(value_1) + get_scale_big_decimal(value_2);
  for (int i = 0; i < 448; i++) {
    if (get_bit_big_decimal(value_2, i)) {
      error = big_decimal_mantissa_shift_l(&value_1, i - count);
      add_big_decimal(value_1, *result, result);
      count = i;
    }
  }
  set_scale_big_decimal(result, res_scale);
  return error;
}

// Степени чисел принимаются за 10^0, знаки не учитываются
void sub_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal* result) {
  int tmp = 0, res = 0;
  for (int i = 0; i < 448; i++) {
    res =
        get_bit_big_decimal(value_1, i) - get_bit_big_decimal(value_2, i) - tmp;
    tmp = res < 0;
    res = abs(res);
    set_bit_big_decimal(result, i, res % 2);
  }
}

// Не учитывает скейл, делит только мантиссу 
void big_decimal_div10(s21_big_decimal* src) {
  s21_big_decimal src_copy = *src;
  s21_big_decimal src_copy2 = *src;
  big_decimal_mantissa_shift_r(&src_copy, 1);
  big_decimal_mantissa_shift_r(&src_copy2, 2);
  s21_big_decimal q = {0}, temp = {0};
  add_big_decimal(src_copy, src_copy2, &q);

  for (int i = 4; i < 512; i *= 2) {  // поч 512?
    src_copy = q;
    big_decimal_mantissa_shift_r(&src_copy, i);
    add_big_decimal(src_copy, q, &temp);
    q = temp;
  }
  big_decimal_mantissa_shift_r(&q, 3);
  src_copy2 = q;
  big_decimal_mantissa_shift_l(&src_copy2, 2);
  reset_big_decimal(&temp);
  add_big_decimal(src_copy2, q, &temp);
  src_copy2 = temp;
  s21_big_decimal r;
  sub_big_decimal(*src, src_copy2, &r);
  reset_big_decimal(&temp);
  add_big_decimal(src_copy, q, &temp);

  if (temp.bits[0] >= 9) {
    s21_big_decimal one = {
        .bits[0] = 0b00000000000000000000000000000000000000000000000000000001,
        .bits[1] = 0b00000000000000000000000000000000000000000000000000000000,
        .bits[2] = 0b00000000000000000000000000000000000000000000000000000000,
        .bits[3] = 0b00000000000000000000000000000000000000000000000000000000,
        .bits[4] = 0b00000000000000000000000000000000000000000000000000000000,
        .bits[5] = 0b00000000000000000000000000000000000000000000000000000000,
        .bits[6] = 0b00000000000000000000000000000000000000000000000000000000,
        .scale = 0b00000000000000000000000000000000,
    };
    reset_big_decimal(&q);
    add_big_decimal(temp, one, &q);
  }

  *src = q;
}

void decimal_x10(s21_decimal* src) {
  s21_decimal dec3 = *src;
  s21_decimal dec2 = *src;

  decimal_mantissa_shift_l(&dec3, 3);
  decimal_mantissa_shift_l(&dec2, 1);

  *src = add_decimals_mantissa(&dec2, &dec3);
}

void decimal_div10(s21_decimal* src, unsigned int roundup) {
  s21_decimal src_copy = *src;
  s21_decimal src_copy2 = *src;

  decimal_mantissa_shift_r(&src_copy, 1);
  decimal_mantissa_shift_r(&src_copy2, 2);
  s21_decimal q = add_decimals_mantissa(&src_copy, &src_copy2);

  for (int i = 4; i < 512; i *= 2) {
    src_copy = q;
    decimal_mantissa_shift_r(&src_copy, i);
    q = add_decimals_mantissa(&q, &src_copy);
  }

  decimal_mantissa_shift_r(&q, 3);

  src_copy2 = q;
  decimal_mantissa_shift_l(&src_copy2, 2);
  src_copy2 = add_decimals_mantissa(&q, &src_copy2);

  decimal_mantissa_shift_l(&src_copy2, 1);

  s21_decimal r = sub_decimals_mantissa(src, &src_copy2);

  q = add_decimals_mantissa(&q, &src_copy);

  if (r.bits[0] >= (0xA - roundup)) {
    s21_decimal one = {
        .bits[0] = 0b00000000000000000000000000000001,
        .bits[1] = 0b00000000000000000000000000000000,
        .bits[2] = 0b00000000000000000000000000000000,
        .bits[3] = 0b00000000000000000000000000000000,
    };
    q = add_decimals_mantissa(&q, &one);
  }

  *src = q;
}

int s21_mantisa_compare(s21_decimal* value_1, s21_decimal* value_2) {
  int flag = -1;

  for (int i = 2; i >= 0; i--) {
    if (value_1->bits[i] == value_2->bits[i]) {
      continue;
    } else {
      flag = value_1->bits[i] < value_2->bits[i];
      break;
    }
  }
  return flag;
}

void equalize_scale(s21_decimal* value_1, s21_decimal* value_2) {
  int exp_1 = get_scale(*value_1);
  int exp_2 = get_scale(*value_2);

  if (exp_1 != exp_2) {
    if (exp_1 < exp_2) {
      for (; exp_1 < exp_2; exp_1++) {
        decimal_x10(value_1);
        set_scale(value_1, exp_2);
      }
    } else {
      for (; exp_2 < exp_1; exp_2++) {
        decimal_x10(value_2);
        set_scale(value_2, exp_1);
      }
    }
  }
}

#if FALSE

u_int32_t div10(u_int32_t dividend) {
  u_int64_t invDivisor = 0x1999999A;
  return (u_int32_t)((invDivisor * dividend) >> 32);
}

unsigned long long divu10(unsigned long long n) {
  unsigned long long q, r;
  q = (n >> 1) + (n >> 2);
  q = q + (q >> 4);
  q = q + (q >> 8);
  q = q + (q >> 16);
  q = q >> 3;
  r = n - (((q << 2) + q) << 1);
  return q + (r > 9);  // return q+((r+6)>>4);
}

#endif