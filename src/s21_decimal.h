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

#define F_MAX 1233.01  // 4523462362123231234562456.23123

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
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

int get_sign(s21_decimal num);
void set_sign(s21_decimal *num, int sign_value);
int get_scale(s21_decimal num);
void set_scale(s21_decimal *num, int scale_value);
int get_bit(s21_decimal src, int index);
void set_bit(s21_decimal *src, int index, int value);
long double get_mantissa(s21_decimal *src);
void debug_display_decimal(char *name, s21_decimal src);
void debug_display_big_decimal(char *name, s21_big_decimal src);
void debug_display_float(float *src);
void debug_display_int(int src);
void reset_decimal(s21_decimal *src);
void import_to_big_decimal(s21_decimal src, s21_big_decimal *dst);
void import_to_small_decimal(s21_big_decimal src, s21_decimal *dst);
void reset_big_decimal(s21_big_decimal *src);
int decimal_is_zero(s21_decimal src);
int big_decimal_is_zero(s21_big_decimal src);
int get_bit_big_decimal(s21_big_decimal src, int index);
void set_bit_big_decimal(s21_big_decimal *dst, int index, int bit);
int get_sign_big_decimal(s21_big_decimal num);
void set_sign_big_decimal(s21_big_decimal *num, int sign_value);
int get_scale_big_decimal(s21_big_decimal num);
void set_scale_big_decimal(s21_big_decimal *num, int scale_value);
void switch_endian_big_decimal(s21_big_decimal *x);
int big_decimal_mantissa_shift_l(s21_big_decimal *dst, int offset);
void big_decimal_mantissa_shift_r(s21_big_decimal *dst, int offset);
long double get_mantissa_big_decimal(s21_big_decimal *src);
void max_decimal(s21_decimal *dst);
void min_decimal(s21_decimal *dst);
// void small_decimal(s21_decimal *dst);

void equalize_scale(s21_decimal *value_1, s21_decimal *value_2);

s21_decimal add_decimals_mantissa(s21_decimal *x, s21_decimal *y);
s21_decimal sub_decimals_mantissa(s21_decimal *x, s21_decimal *y);
void decimal_mantissa_shift_l(s21_decimal *dec, int offset);
void decimal_mantissa_shift_r(s21_decimal *dec, int offset);
int s21_mantisa_compare(s21_decimal *value_1, s21_decimal *value_2);

void add_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
void sub_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
int mul_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result);
void big_decimal_div10(s21_big_decimal* src); 

void switchEndian(s21_decimal *x);

void decimal_x10(s21_decimal *src);
void decimal_div10(s21_decimal *src, unsigned int roundup);

float rand_float(int random, float min, float max);

#endif
