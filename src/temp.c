// #include <stdio.h>

#include "s21_decimal.h"
#include "s21_utils.h"
#include <stdio.h>

// // 79,228,162,514,264,337,593,543,950,335

int main() {
  // int x = 10, y = 2147483638,
  int result_int = 0;
  s21_decimal result = {0};
  // s21_decimal value_1 = {0};
  // s21_decimal value_2 = {0};
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int return_value = s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_int(result, &result_int);

  printf("VALUE_1\n");
  print_bits_decimal(value_1);
  printf("\n");
  printf("VALUE_2\n");
  print_bits_decimal(value_2);
  printf("\n");
  printf("RESULT\n");
  print_bits_decimal(result);
  printf("\n");
  printf("RETURN_VALUE = %d\n", return_value);
  printf("RESULT_INT = %d\n", result_int);

  return 0;
}