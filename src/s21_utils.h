#ifndef S21_UTILS_H
#define S21_UTILS_H
#define BYTES_IN_DECIMAL 4
#define BYTES_IN_BCD 8
#define INT_BIT 32
#include <stdint.h>

#include "s21_decimal.h"

typedef struct {
  uint32_t bits[BYTES_IN_BCD];
  int32_t scale;
  int32_t sign;
} bcd;

int get_bit(s21_decimal value, int bit);
void set_bit(s21_decimal *value, int bit);
void unset_bit(s21_decimal *value, int bit);

void init_bcd(bcd *bsd_number, s21_decimal number);

void print_bits(int n);
void print_bits_bsd(bcd number);
void print_bits_decimal(s21_decimal number);

int get_bit_in_bcd(bcd value, int bit);
void set_bit_in_bcd(bcd *value, int bit);
void unset_bit_in_bcd(bcd *value, int bit);

void left_bit_shift_decimal(s21_decimal *decimal);
void left_bit_shift_bcd(bcd *bcd_number);
void left_to_N_bit_shift_bcd(bcd *bcd_number, int number);

void decimal_to_bcd(s21_decimal *decimal, bcd *bcd_number);
void bcd_to_decimal(bcd *bcd_number, s21_decimal *decimal);

void normalize_scale(bcd *number_1, bcd *number_2);

void full_convert_two_bcd_with_normalize(s21_decimal *value_1,
                                         s21_decimal *value_2,
                                         bcd *value_1_in_bcd,
                                         bcd *value_2_in_bcd);

void reset_bcd(bcd *value);
void reset_decimal(s21_decimal *value);

void tmp_result_of_adding(bcd value_1, bcd value_2, bcd *result_in_bcd);
void tmp_result_of_diff(bcd value_1, bcd value_2, bcd *result_in_bcd);
void tmp_result_of_mult(bcd value_1_in_bcd, bcd value_2_in_bcd,
                        bcd *result_in_bcd);
int check_decimal_for_zero(s21_decimal value);
void copy_decimal(s21_decimal src, s21_decimal *dst);
s21_decimal abs_decimal(s21_decimal value);
int is_positive_decimal(s21_decimal value);
void sub_smaller_from_larger(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void set_minus_to_decimal(s21_decimal *dst);

#endif
