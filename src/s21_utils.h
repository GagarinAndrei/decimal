#ifndef S21_UTILS_H
#define S21_UTILS_H
#define BYTES_IN_DECIMAL 4
#define INT_BIT 32
#define MAX_SCALE 28
#include <stdint.h>

#include "s21_decimal.h"

int get_bit(s21_decimal value, int bit);
void set_bit(s21_decimal *value, int bit);
void unset_bit(s21_decimal *value, int bit);
void true_set_bit(s21_decimal *value, int bit, int index_of_bit);

void print_bits(int n);
void print_bits_decimal(s21_decimal number);

int left_bit_shift_decimal(s21_decimal *decimal);
int left_bit_shift_N_decimal(s21_decimal *decimal, int n);
void right_bit_shift_decimal(s21_decimal *decimal);
void right_bit_shift_N_decimal(s21_decimal *decimal, int n);

void normalize_scale(s21_decimal *value_1, s21_decimal *value_2);
void normalize_mantissa(s21_decimal *value_1, s21_decimal *value_2);

void reset_decimal(s21_decimal *value);

int check_decimal_for_zero(s21_decimal value);
void copy_decimal(s21_decimal src, s21_decimal *dst);
s21_decimal abs_decimal(s21_decimal value);
int is_positive_decimal(s21_decimal value);
void sub_smaller_from_larger(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal *result);
void set_minus_to_decimal(s21_decimal *dst);
int digits(int n);
int get_scale(s21_decimal value);
void set_scale(s21_decimal *dst, int scale);
int mult_decimal_to_ten(s21_decimal *value);
int div_decimal_to_ten(s21_decimal *value);
int increase_scale(s21_decimal *value);
int mult_decimal_to_ten_n_times(s21_decimal *decimal, int number);
int decrease_scale(s21_decimal *value);

s21_decimal integer_quotient(s21_decimal dividend, s21_decimal divisor,
                             s21_decimal *result);
void decimal_pow_of_two(int pow, s21_decimal *result);
void fractional_quitient(s21_decimal remainder, s21_decimal divisor,
                         s21_decimal *result);

#endif
