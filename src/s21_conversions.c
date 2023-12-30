#include "s21_decimal.h"
#include "s21_utils.h"

// int s21_from_float_to_decimal(float src, s21_decimal *dst);
// int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (isnan((float)src) || isinf((float)src) || !dst) return 1;
  if (src < 0) set_bit(dst, 127);
  int number = abs(src);
  dst->bits[0] = number;
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (!dst || (unsigned int)src.bits[0] > INT32_MAX || src.bits[1] != 0 ||
      src.bits[2] != 0)
    return 1;
  *dst = src.bits[0];
  if (get_bit(src, 127)) *dst = -1 * *dst;
  return 0;
}