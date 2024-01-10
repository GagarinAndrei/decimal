#include <stdio.h>

#include "s21_decimal.h"
#include "s21_utils.h"

// 79,228,162,514,264,337,593,543,950,335

int main() {
s21_decimal value_1 = {{12345, 654, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{12, 654, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less(value_1, value_2);
  printf("RESULT = %d\n", return_value);
  print_bits_decimal(value_1);
  printf("\n");
  print_bits_decimal(value_2);

  return 0;
}
