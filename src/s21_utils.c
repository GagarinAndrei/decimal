#include "s21_utils.h"

#include "s21_decimal.h"
#include <stdint.h>

/**
 * Получить значение нужного бита s21_decimal
 * @param value Проверяемый decimal
 * @param bit Проверяемый бит (0 - 127)
 * @return  Значение бита ( 0 | 1 )
 * 
*/
int get_bit(s21_decimal value, int bit) {
  int result;
  int index = bit / 32;
  unsigned int mask = 1 << (bit % 32);
  result = (value.bits[index] & mask) ? 1 : 0;

  return result;
}

/**
 * Установить значение в 1 нужного бита s21_decimal
 * @param value Проверяемый decimal
 * @param bit Проверяемый бит (0 - 127)
 * 
*/
void set_bit(s21_decimal *value, int bit) {
  int index = bit / 32;
  unsigned int mask = 1 << (bit % 32);
  value->bits[index] |= mask;
}

/**
 * Установить значение в 0 нужного бита s21_decimal
 * @param value Проверяемый decimal
 * @param bit Проверяемый бит (0 - 127)
 * 
*/
void unset_bit(s21_decimal *value, int bit) {
  int index = bit / 32;
  unsigned int mask = ~(1 << (bit % 32));
  value->bits[index] &= mask;
}

void left_bit_shift_decimal(s21_decimal *decimal) {
  for (int i = BYTES_IN_DECIMAL - 1; i >= 0; i--) {
    decimal->bits[i] <<= 1;
    if (i > 0) {
      int highest_bit_in_right_int = ((i - 1) * INT_BIT) + (INT_BIT - 1);
      if (get_bit(*decimal, highest_bit_in_right_int)) {
        set_bit(decimal, highest_bit_in_right_int + 1);
      }
    }
  }
}

void print_bits(int n) {
  int i;
  for (i = INT_BIT - 1; i >= 0; i--) {
    printf("%d", (n & (1 << i)) != 0);
    if (!(i % 4)) {
      printf(" ");
    }
  }
  printf("\n");
}

void print_bits_decimal(s21_decimal number) {
  for (int i = 0; i < BYTES_IN_DECIMAL; i++) {
    print_bits(number.bits[i]);
  }
}

/**
 * Проверяет s21_decimal на ноль
 * @param value проверяемый элемент
 * @return 1 - равен 0,
 * 0 - не равен
*/
int check_decimal_for_zero(s21_decimal value) {
  int result = 0;
  for(int i = 0; i < BYTES_IN_DECIMAL; i++) {
    if(value.bits[i] == 0) {
      result = 1;
    }
  }

  return result;
}

void normalize_scale(s21_decimal *number_1, s21_decimal *number_2) {
  int32_t max_scale =
      (number_1->scale > number_2->scale) ? number_1->scale : number_2->scale;
  int32_t min_scale =
      (number_1->scale < number_2->scale) ? number_1->scale : number_2->scale;
  int is_min_scale = (max_scale > number_1->scale) ? 1 : 0;

  for (int i = min_scale; i < max_scale; i++) {
    if (is_min_scale) {
      number_1->scale++;
      for (int i = 0; i < 4; ++i) left_bit_shift_decimal(number_1);
    } else {
      number_2->scale++;
      for (int i = 0; i < 4; ++i) left_bit_shift_decimal(number_2);
    }
  }
}

/**
 * Обнуление s21_decimal
 * @param value адрес на нужный элемент
*/
void reset_decimal(s21_decimal *value) {
  for(int i = 0; i < BYTES_IN_DECIMAL; i++) {
    value->bits[i] = 0;
  }
}