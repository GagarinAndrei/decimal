// #include <stdio.h>

#include "s21_decimal.h"
#include "s21_utils.h"

// // 79,228,162,514,264,337,593,543,950,335

int main() {
  // s21_decimal value_1 = {{1, 0, 0, 0}};
  // s21_decimal value_2 = {{100, 0, 0, 0x00020000}};
  // normalize_scale(&value_1, &value_2);
  // mult_decimal_to_ten(&value_1);
  // mul_decimal_to_ten(&value_1);
  // mul_decimal_to_ten(&value_2);
  // div_decimal_to_ten(&value_1);
  // right_bit_shift_decimal(&value_1);
  // int return_value = s21_is_less(value_1, value_2);
  // printf("RESULT = %d\n", return_value);
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{1, 1, 1, 0}};
  s21_decimal result = {0};
  // int x = 2;
  // float result_float = 0, y = 1.2345678;
  // z = x + y;
  // s21_from_int_to_decimal(x, &value_1); // 2 
  // s21_from_float_to_decimal(y, &value_2); // 1.234567
  // normalize_scale(&value_1,&value_2);
  printf("%d\n", s21_add(value_1, value_2, &result));
  // s21_from_decimal_to_float(result, &result_float);
  // (fabs((result_float - z)) < 1e-6, 1))? 1 : 0;
  // printf("%f = FLOAT\n", result_float);
  print_bits_decimal(value_1);
  printf("\n");
  print_bits_decimal(value_2);
  printf("\n");
  print_bits_decimal(result);

  return 0;
}