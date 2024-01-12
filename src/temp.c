// #include <stdio.h>

#include "s21_decimal.h"
#include "s21_utils.h"
#include <stdio.h>

// // 79,228,162,514,264,337,593,543,950,335

int main() {
  // s21_decimal value_1 = {0};
  // s21_decimal value_2 = {0};
  // s21_decimal result = {0};
  // int x = 10, y = 2147483638, result_int = 0;
  // s21_from_int_to_decimal(x, &value_1);
  // s21_from_int_to_decimal(y, &value_2);
  // int return_value = s21_sub(value_1, value_2, &result);
  // s21_from_decimal_to_int(result, &result_int);
  // printf("%d\n", return_value);
  s21_decimal value_1 = {{123456, 1, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456, 1, 0xFFFFFFFF, 0x10000}};
  // int return_value = s21_is_greater(value_1, value_2);
  printf("VALUE_1\n");
  print_bits_decimal(value_1);
  printf("\n");
  printf("VALUE_2\n");
  print_bits_decimal(value_2);
  printf("\n");
  printf("RESULT\n");
  // print_bits_decimal(result);

  return 0;
}