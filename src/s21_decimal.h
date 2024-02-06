#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>   // for debug printing, delete later
#include <stdlib.h>  // for antoha system clear
#include <string.h>
#include <time.h>  // FOR DEBUG RANDOM

#define MINUS 0x80000000  // 0b10000000 00000000 00000000 00000000
#define BLANK 0x0
#define SCALE 0x00ff0000     // 0b00000000 11111111 00000000 00000000
#define MAX4BITE 0xffffffff  // 0b1111111 1111111 1111111 1111111

#define F_MAX 719716300.0

typedef struct s21_decimal {
  unsigned int bits[4];
} s21_decimal;

typedef struct s21_big_decimal {
  uint64_t bits[7];
  uint32_t scale;
} s21_big_decimal;

// Arithmetic Operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// The functions return the error code:

// 0 - OK
// 1 - the number is too large or equal to infinity
// 2 - the number is too small or equal to negative infinity
// 3 - division by 0

typedef enum am_code {
  AM_ERR = -1,
  AM_OK = 0,
  AM_OF = 1,   // overflow
  AM_NOF = 2,  // negative overflow
  AM_DIV0 = 3,
} am_code;

// Comparison Operators
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

// Return value:
// 0 - FALSE
// 1 - TRUE

// Convertors and parsers
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Return value - code error:
// 0 - OK
// 1 - convertation error

// Rounds a specified Decimal number to the closest integer toward negative
// infinity.
int s21_floor(s21_decimal value, s21_decimal *result);
// Rounds a decimal value to the nearest integer.
int s21_round(s21_decimal value, s21_decimal *result);
// Returns the integral digits of the specified Decimal; any fractional digits
// are discarded, including trailing zeroes.
int s21_truncate(s21_decimal value, s21_decimal *result);
// Returns the result of multiplying the specified Decimal value by negative
// one.
int s21_negate(s21_decimal value, s21_decimal *result);

// Return value - code error:
// 0 - OK
// 1 - calculation error

// extra functions - helpers

void reset_decimal(s21_decimal *src);
void reset_big_decimal(s21_big_decimal *src);

int is_decimal_zero(s21_decimal src);
int is_big_decimal_zero(s21_big_decimal src);

long double get_mantissa(s21_decimal *src);
long double get_mantissa_big_decimal(s21_big_decimal *src);

int get_sign(s21_decimal num);
int get_sign_big_decimal(s21_big_decimal num);
void set_sign(s21_decimal *num, int sign_value);
void set_sign_big_decimal(s21_big_decimal *num, int sign_value);

int get_scale(s21_decimal num);
int get_scale_big_decimal(s21_big_decimal num);
void set_scale(s21_decimal *num, int scale_value);
void set_scale_big_decimal(s21_big_decimal *num, int scale_value);

int get_bit(s21_decimal src, int index);
int get_bit_big_decimal(s21_big_decimal src, int index);
void set_bit(s21_decimal *src, int index, int value);
void set_bit_big_decimal(s21_big_decimal *dst, int index, int bit);

void decimal_mantissa_shift_l(s21_decimal *dec, int offset);
int big_decimal_mantissa_shift_l(s21_big_decimal *dst, int offset);
void decimal_mantissa_shift_r(s21_decimal *dec, int offset);
void big_decimal_mantissa_shift_r(s21_big_decimal *dst, int offset);

void decimal_to_big(s21_decimal src, s21_big_decimal *dst);
void big_to_decimal(s21_big_decimal src, s21_decimal *dst);

void switch_endian(s21_decimal *x);
void switch_endian_big_decimal(s21_big_decimal *x);

void equalize_scale(s21_decimal *value_1, s21_decimal *value_2);

s21_decimal add_decimals_mantissa(s21_decimal *x, s21_decimal *y);
s21_decimal sub_decimals_mantissa(s21_decimal *x, s21_decimal *y);

int s21_mantisa_compare(s21_decimal *value_1, s21_decimal *value_2);

void add_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
void sub_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
int mul_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result);

void decimal_div10(s21_decimal *src, unsigned int roundup);
void big_decimal_div10(s21_big_decimal *src);  // UPDATE SUPPORT ROUNDUP

void decimal_x10(s21_decimal *src);
void big_decimal_x10(s21_big_decimal *src);  // NOT REALISED

void divide_decimal(s21_decimal dividend, s21_decimal divisor,
                    s21_decimal *quotient, s21_decimal *remainder, int stop);
void divide_big_decimal(s21_big_decimal dividend, s21_big_decimal divisor,
                        s21_big_decimal *quotient, s21_big_decimal *remainder,
                        int stop);  // NOT REALISED

void upscale_decimal_x10(s21_decimal *dec);
void upscale_big_decimal_x10(s21_big_decimal *dec); // NOT REALISED

void decimal_one(s21_decimal *decimal);

void s21_decreace_scale_big_decimal(s21_big_decimal *dst, int n);
int s21_post_normalization(s21_big_decimal *result, int scale);

// MARK: DEBUG

float rand_float(int random, float min, float max);

void debug_display_int(int src);
void debug_display_float(float *src);
void debug_display_decimal(char *name, s21_decimal src);
void debug_display_big_decimal(char *name, s21_big_decimal src);

#endif
