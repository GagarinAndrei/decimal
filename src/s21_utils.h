#ifndef S21_UTILS_H
#define S21_UTILS_H
#define BYTES_IN_DECIMAL 4
#define BYTES_IN_BCD 8
#define INT_BIT 32
#include <stdint.h>

#include "s21_decimal.h"

int get_bit(s21_decimal value, int bit);
void set_bit(s21_decimal *value, int bit);
void unset_bit(s21_decimal *value, int bit);

void print_bits(int n);
void print_bits_decimal(s21_decimal number);

int left_bit_shift_decimal(s21_decimal *decimal);
void reset_decimal(s21_decimal *value);
int digits(int n);

#endif
