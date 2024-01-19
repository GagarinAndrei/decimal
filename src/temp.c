#include <stdio.h>

#include "s21_decimal.h"
#include "s21_utils.h"

// // // 79,228,162,514,264,337,593,543,950,335

int main() {
  s21_decimal result = {0};
  reset_decimal(&result);
  // s21_decimal remainder = {0};
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{3, 0, 0, 0}};

  // remainder = integer_quotient(value_1, value_2, &result);
  // fractional_quitient(value_1, value_2, &result);
  s21_div(value_1, value_2, &result);
  // printf("VALUE_1\n");
  // print_bits_decimal(value_1);
  // printf("VALUE_2\n");
  // print_bits_decimal(value_2);

  printf("RESULT\n");
  print_bits_decimal(result);
  // printf("REMAINDER\n");
  // print_bits_decimal(remainder);
  // decimal_pow_of_two(0, &result);
  // printf("\n");
  // printf("POWER_OF_TWO\n");
  // print_bits_decimal(result);
  // printf("\n");

  // int res = 23456345;
  // for (int i = 0; i < 5; i++) {

  // reset_decimal(&result);
  // s21_from_int_to_decimal(res, &result);
  // print_bits_decimal(result);
  // printf("\n");
  // s21_from_decimal_to_int(result, &res);
  // printf("%d\n", res);
  // }


  return 0;
}