#include "s21_decimal.h"
#include "s21_utils.h"

#define FLOAT_ACCURACY 7  // 7 значимых цифр по условию задачи

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

/**
 * Конвертирует float в decimal
 * @param src конвертируемый float
 * @param dst указатель на decimal, в который запишется результат функции
 * @return int код ошибки:
 * 0 - OK,
 * 1 - ошибка конвертации
 */
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int exponent = 0;
  unsigned int intValue = (int)src;
  float fraction = src - intValue;

  reset_decimal(dst);

  int digits_counter = FLOAT_ACCURACY - (digits(intValue));
  if (0 > digits_counter) {
    intValue /= pow(10, digits_counter * -1);
    intValue *= pow(10, digits_counter * -1);
  }
  while (fraction != 0.0f && (fraction - (int)fraction) != 0.0f &&
         exponent < digits_counter) {
    fraction *= 10.0f;
    exponent++;
  }

  while ((int)fraction % 10 == 0 && fraction != 0) {
    fraction /= 10;
    exponent--;
  }

  intValue = intValue * pow(10, exponent) + fraction;

  dst->bits[0] = intValue;
  dst->bits[3] = exponent << 16;

  return 0;
}

/**
 * Конвертирует decimal в float
 * @param src конвертируемый s21_decimal
 * @param dst указатель на float, в который запишется результат функции
 * @return int код ошибки:
 * 0 - OK,
 * 1 - ошибка конвертации
 */
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (src.bits[1] || src.bits[2]) {
    return 1;
  }

  *dst = 0.0;

  int scale = (src.bits[3] & SCALE) >> 16;
  for (int i = 0; i < INT_BIT; i++) {
    if (get_bit(src, i)) {
      *dst += pow(2, i);
    }
  }
  while (scale) {
    *dst /= 10;
    scale--;
  }
  if (src.bits[3] & MINUS) {
    *dst = *dst * (-1);
  }

  return 0;
}