#include <stdio.h>

#include "s21_decimal.h"
#include "s21_utils.h"

// 79,228,162,514,264,337,593,543,950,335

int main() {
  s21_decimal value_1 = {{7, 0, 0, 0}};
  s21_decimal value_2 = {{7, 0, 0, 0}};
  s21_decimal result;
  s21_div(value_1, value_2, &result);
  printf("\n");

  s21_decimal value_3 = {{21, 0, 0, 0}};
  s21_decimal value_4 = {{3, 0, 0, 0}};
  s21_div(value_3, value_4, &result);
  printf("\n");

  s21_decimal value_5 = {{20, 0, 0, MINUS}};
  s21_decimal value_6 = {{3, 0, 0, MINUS}};
  s21_div(value_5, value_6, &result);
  printf("\n");

  s21_decimal value_7 = {{2, 0, 0, MINUS}};
  s21_decimal value_8 = {{31, 0, 0, MINUS}};
  s21_div(value_7, value_8, &result);
  printf("\n");

  s21_decimal value_9 = {{2, 0, 0, MINUS}};
  s21_decimal value_10 = {{30, 0, 0, 0}};
  s21_div(value_9, value_10, &result);
  printf("\n");

  s21_decimal value_11 = {{3, 0, 0, 0}};
  s21_decimal value_12 = {{21, 0, 0, 0}};
  s21_div(value_11, value_12, &result);
  printf("\n");

  s21_decimal value_13 = {{25, 0, 0, 0}};
  s21_decimal value_14 = {{55, 0, 0, 0}};
  s21_div(value_13, value_14, &result);
  printf("\n");

  // s21_decimal value_5 = {{227, 0, 0, 0}};
  // bcd bcd5;
  // init_bcd(&bcd5, value_5);
  // decimal_to_bcd(&value_5, &bcd5);
  // print_bits_bsd(bcd5);
  // bcd bcd_number1;
  // bcd bcd_number2;
  // full_convert_two_bcd_with_normalize(&value_1, &value_2, &bcd_number1,
  //                                     &bcd_number2);

  // print_bits_bsd(bcd_number1);
  // printf("%d\n", bcd_number1.scale);
  // printf("\n");
  // print_bits_bsd(bcd_number2);
  // printf("%d\n", bcd_number2.scale);
  // printf("\n");
  // s21_sub(value_1, value_2, &result);

  return 0;
}
