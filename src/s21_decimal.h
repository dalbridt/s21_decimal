#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H
#include <stddef.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h> // for debug printing, delete later

typedef struct {
  int bits[4];
} s21_decimal;

/*typedef struct {
  uint64_t bits[7];
  uint16_t scale;
} s21_big_decimal;*/

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
void set_sign(s21_decimal num, int sign_value);
int get_scale(s21_decimal num);
void set_scale(s21_decimal* num, int scale_value);

int get_bit(int src, int index); 
void set_bit(s21_decimal * src, int index, int value);
#endif
