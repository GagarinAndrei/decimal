#include "s21_utils.h"

#include "s21_decimal.h"

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

/**
 * Сдвиг влево всех битов мантиссы структуры s21_decimal на одну позицию
 * @param decimal указатель на структуру s21_decimal
 * @return 0 - ошибка переноса;
 * 1 - success
*/
int left_bit_shift_decimal(s21_decimal *decimal) {
  if(get_bit(*decimal, 95)) {
    return 0;
  }
  for (int i = BYTES_IN_DECIMAL - 1; i >= 0; i--) {
    decimal->bits[i] <<= 1;
    if (i > 0) {
      int highest_bit_in_right_int = ((i - 1) * INT_BIT) + (INT_BIT - 1);
      if (get_bit(*decimal, highest_bit_in_right_int)) {
        set_bit(decimal, highest_bit_in_right_int + 1);
      }
    }
  }

  return 1;
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

/**
 * Обнуление s21_decimal
 * @param value адрес на нужный элемент
*/
void reset_decimal(s21_decimal *value) {
  for(int i = 0; i < BYTES_IN_DECIMAL; i++) {
    value->bits[i] = 0;
  }
}

int digits(int n) {
  if(n < 0) n *= -1;
  if (n < 10) return 1;

  return 1 + digits(n / 10);
}