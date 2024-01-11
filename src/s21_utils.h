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

void print_bits(int n);
void print_bits_decimal(s21_decimal number);

int left_bit_shift_decimal(s21_decimal *decimal);

void normalize_scale(s21_decimal *number_1, s21_decimal *number_2);

void reset_decimal(s21_decimal *value);

int check_decimal_for_zero(s21_decimal value);
void copy_decimal(s21_decimal src, s21_decimal *dst);
s21_decimal abs_decimal(s21_decimal value);
int is_positive_decimal(s21_decimal value);
void sub_smaller_from_larger(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void set_minus_to_decimal(s21_decimal *dst);
int digits(int n);
int get_scale(s21_decimal value);
void set_scale(s21_decimal *dst, int scale);
int mul_decimal_to_ten(s21_decimal *value);
#endif
