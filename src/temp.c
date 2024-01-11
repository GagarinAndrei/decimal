#include <stdio.h>

#include "s21_decimal.h"
#include "s21_utils.h"

// 79,228,162,514,264,337,593,543,950,335

int main() {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{100, 0, 0, 0x00020000}};
  normalize_scale(&value_1, &value_2);
  // mul_decimal_to_ten(&value_1);
  // mul_decimal_to_ten(&value_2);
  // div_decimal_to_ten(&value_1);
  // right_bit_shift_decimal(&value_1);
  // int return_value = s21_is_less(value_1, value_2);
  // normalize_scale(&value_1,&value_2);
  // printf("RESULT = %d\n", return_value);
  print_bits_decimal(value_1);
  printf("\n");
  print_bits_decimal(value_2);

  return 0;
}
