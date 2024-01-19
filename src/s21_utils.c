#include "s21_utils.h"

#include <stdio.h>

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
  if (get_bit(*decimal, 95)) {
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

void right_bit_shift_decimal(s21_decimal *decimal) {
  for (int i = 0; i < BYTES_IN_DECIMAL - 1; i++) {
    decimal->bits[i] >>= 1;
    if (i < BYTES_IN_DECIMAL - 1) {
      int lowest_bit_in_left_int = (i + 1) * INT_BIT;
      if (get_bit(*decimal, lowest_bit_in_left_int)) {
        set_bit(decimal, lowest_bit_in_left_int - 1);
      }
    }
  }
}

int left_bit_shift_N_decimal(s21_decimal *decimal, int n) {
  int code = 1;
  for (int i = 0; i < n; i++) {
    code = left_bit_shift_decimal(decimal);
    if (0 == code) {
      break;
    }
  }

  return code;
}

void right_bit_shift_N_decimal(s21_decimal *decimal, int n) {
  for (int i = 0; i < n; i++) {
    right_bit_shift_decimal(decimal);
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
  printf("\n");
}

/**
 * Проверяет s21_decimal на ноль
 * @param value проверяемый элемент
 * @return 1 - равен 0,
 * 0 - не равен
 */
int check_decimal_for_zero(s21_decimal value) {
  int result = 1;
  for (int i = 0; i < BYTES_IN_DECIMAL - 1; i++) {
    if (value.bits[i] != 0) {
      result = 0;
    }
  }

  return result;
}

/**
 * Обнуление s21_decimal
 * @param value адрес на нужный элемент
 */
void reset_decimal(s21_decimal *value) {
  for (int i = 0; i < BYTES_IN_DECIMAL; i++) {
    value->bits[i] = 0;
  }
}

void copy_decimal(s21_decimal src, s21_decimal *dst) {
  reset_decimal(dst);
  for (int index = 0; index < BYTES_IN_DECIMAL; index++) {
    for (int bit = 0; bit < INT_BIT; bit++) {
      if (get_bit(src, bit + (index * INT_BIT)))
        set_bit(dst, bit + (index * INT_BIT));
    }
  }
}

s21_decimal abs_decimal(s21_decimal value) {
  s21_decimal result;
  copy_decimal(value, &result);
  result.bits[3] &= ~MINUS;
  return result;
}
/**
 * проверяет s21_decimal на положительность
 * @param value первое значение
 * @return 0 - если число отрицательное, 1 - если число положительное.
 */
int is_positive_decimal(s21_decimal value) {
  return (value.bits[3] & MINUS) ? 0 : 1;
}

void sub_smaller_from_larger(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal *result) {
  s21_decimal smaller, larger;
  if (s21_is_greater(value_1, value_2)) {
    copy_decimal(value_1, &larger);
    copy_decimal(value_2, &smaller);
  } else {
    copy_decimal(value_2, &larger);
    copy_decimal(value_1, &smaller);
  }

  int one_to_mind = 0;
  for (int index = 0; index < BYTES_IN_DECIMAL - 1; index++) {
    for (int bit = 0; bit < INT_BIT; bit++) {
      if (get_bit(larger, bit + (index * INT_BIT)) -
              get_bit(smaller, bit + (index * INT_BIT)) - one_to_mind ==
          0) {
        one_to_mind = 0;
        continue;
      }
      if (get_bit(larger, bit + (index * INT_BIT)) -
              get_bit(smaller, bit + (index * INT_BIT)) - one_to_mind ==
          1) {
        set_bit(result, bit + (index * INT_BIT));
        one_to_mind = 0;
      }
      if (get_bit(larger, bit + (index * INT_BIT)) -
              get_bit(smaller, bit + (index * INT_BIT)) - one_to_mind ==
          -1) {
        one_to_mind = 1;
        set_bit(result, bit + (index * INT_BIT));
      }
      if (get_bit(larger, bit + (index * INT_BIT)) -
              get_bit(smaller, bit + (index * INT_BIT)) - one_to_mind ==
          -2) {
        one_to_mind = 1;
      }
    }
  }
}

void set_minus_to_decimal(s21_decimal *dst) { dst->bits[3] |= MINUS; }

int digits(int n) {
  if (n < 0)
    n *= -1;
  if (n < 10)
    return 1;

  return 1 + digits(n / 10);
}

void normalize_scale(s21_decimal *value_1, s21_decimal *value_2) {
  int scale_1, scale_2, diff_scale;
  scale_1 = get_scale(*value_1);
  scale_2 = get_scale(*value_2);
  diff_scale = abs(scale_1 - scale_2);

  for (int i = 0; i < diff_scale; i++) {
    if (scale_1 > scale_2) {
      if (0 == increase_scale(value_2)) {
        decrease_scale(value_1);
      }
    }
    if (scale_2 > scale_1) {
      if (0 == increase_scale(value_1)) {
        // printf("+++++++++++++++++\n");
        decrease_scale(value_2);
      }
    }
  }
}

int is_mantissa_max(s21_decimal value) {
  s21_decimal max_decimal = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  return (s21_is_equal(max_decimal, abs_decimal(value))) ? 1 : 0;
}

void normalize_mantissa(s21_decimal *value_1, s21_decimal *value_2) {
  int scale_1, scale_2;
  int is_mantissa_mult = 1;
  s21_decimal _value_1, _value_2;
  copy_decimal(*value_1, &_value_1);
  copy_decimal(*value_2, &_value_2);
  scale_1 = get_scale(*value_1);
  scale_2 = get_scale(*value_2);
  if (is_mantissa_max(_value_1)) {
    is_mantissa_mult = 0;
  }
  while (scale_1 != scale_2 && is_mantissa_mult) {
    if (is_mantissa_mult) {
      if (!increase_scale(&_value_1)) {
        is_mantissa_mult = 0;
      } else {
        scale_1++;
        // set_scale(value_1, scale_1);
      }
    }
    if (!is_mantissa_mult) {
      decrease_scale(&_value_2);
      scale_2--;
    }
  }
  copy_decimal(_value_1, value_1);
  copy_decimal(_value_2, value_2);
}

int get_scale(s21_decimal value) { return (value.bits[3] & SCALE) >> 16; }

void set_scale(s21_decimal *dst, int scale) {
  dst->bits[3] &= ~SCALE;
  dst->bits[3] |= (SCALE & (scale << 16));
}

/**
 * Увеличение scale Decimal на 1
 * @param value указатель на число, в котором увеличивается scale
 * @return остаток от деления, либо -1 в случае если scale == 0 или Decimal
 == 0
*/
int increase_scale(s21_decimal *value) {
  int success_code = 1;
  if (get_scale(*value) >= MAX_SCALE)
    return 0;
  s21_decimal tmp_eight, tmp_two;
  copy_decimal(*value, &tmp_eight);
  copy_decimal(*value, &tmp_two);
  if (!left_bit_shift_N_decimal(&tmp_eight, 3)) {
    success_code = 0;
  }
  if (!left_bit_shift_decimal(&tmp_two)) {
    success_code = 0;
  }
  if (success_code) {
    if (0 != s21_add(tmp_eight, tmp_two, value)) {
      success_code = 0;
    }
    set_scale(value, get_scale(*value) + 1);
  }
  return success_code;
}

int mult_decimal_to_ten(s21_decimal *value) {
  int error_code = 1;
  s21_decimal tmp_eight, tmp_two;
  copy_decimal(*value, &tmp_eight);
  copy_decimal(*value, &tmp_two);
  if (!left_bit_shift_N_decimal(&tmp_eight, 3)) {
    error_code = 0;
  }
  if (!left_bit_shift_decimal(&tmp_two)) {
    error_code = 0;
  }
  if (error_code) {
    if (0 != s21_add(tmp_eight, tmp_two, value)) {
      error_code = 0;
    }
  }
  return error_code;
}

int mult_decimal_to_ten_n_times(s21_decimal *decimal, int number) {
  int error_code = 1;
  for (int i = 0; i < number; i++) {
    error_code = mult_decimal_to_ten(decimal);
    if (0 == error_code)
      break;
  }
  return error_code;
}

/**
 * Уменьшение scale Decimal на 1
 * @param value указатель на число, в котором уменьшается scale
 * @return остаток от деления, либо -1 в случае если scale == 0 или Decimal == 0
 */
int decrease_scale(s21_decimal *value) {
  if (check_decimal_for_zero(*value) || !get_scale(*value)) {
    return -1;
  }
  int remainder = 0; // остаток
  s21_decimal result;
  reset_decimal(&result);

  for (int i = 95; i >= 0; i--) {
    remainder <<= 1;
    left_bit_shift_decimal(&result);
    if (get_bit(*value, i)) {
      remainder++;
    }
    if (remainder - 10 >= 0) {
      set_bit(&result, 0);
      remainder -= 10;
    }
  }
  result.bits[3] = value->bits[3];

  set_scale(&result, get_scale(*value) - 1);
  copy_decimal(result, value);
  return remainder;
}

s21_decimal integer_quotient(s21_decimal dividend, s21_decimal divisor,
                             s21_decimal *result) {
  int exp = 0;
  s21_decimal pow_of_two = {0};
  s21_decimal remainder, last_value_of_quotient, remainder_of_division = {0};
  copy_decimal(divisor, &remainder);

  while (s21_is_greater_or_equal(dividend, divisor)) {
    while (s21_is_less_or_equal(remainder, dividend)) {
      copy_decimal(remainder, &last_value_of_quotient);
      left_bit_shift_decimal(&remainder);
      exp++;
    }
    exp--;
    s21_sub(dividend, last_value_of_quotient, &remainder);
    decimal_pow_of_two(exp, &pow_of_two);

    s21_add(pow_of_two, *result, result);
    reset_decimal(&pow_of_two);
    copy_decimal(remainder, &dividend);
    copy_decimal(remainder, &remainder_of_division);
    copy_decimal(divisor, &remainder);
    exp = 0;
  }

  return remainder_of_division;
}

void fractional_quitient(s21_decimal remainder, s21_decimal divisor,
                         s21_decimal *result) {
  int scale = 0;
  int exponent = 0; //
  // int tmp_scale_final;//
  s21_decimal integer_result = {0};
  // s21_decimal tmp_result = {0};                   //
  // s21_decimal tmp_scale_decimal = {{1, 0, 0, 0}}; //
  reset_decimal(result);

  while (!check_decimal_for_zero(remainder) && scale < MAX_SCALE) {
    while (s21_is_less(remainder, divisor) && scale < MAX_SCALE) {
      mult_decimal_to_ten(&remainder);
      scale++;
    }
    
    remainder = integer_quotient(remainder, divisor, &integer_result);
    // printf("-=integer_result=-\n");
    // print_bits_decimal(integer_result);
    // if (!check_decimal_for_zero(remainder)) {
    // mult_decimal_to_ten(&integer_result);
    mult_decimal_to_ten(result);
    // printf("%d\n", exponent);
    // print_bits_decimal(tmp_scale_decimal);
    // tmp_scale_final = pow(10, tmp_scale);
    ++exponent;
    // s21_from_int_to_decimal(tmp_scale_final, &tmp_scale_decimal);
    // }
    // s21_mul(integer_result, tmp_scale_decimal, &tmp_result);
    s21_add(*result, integer_result, result);
    // s21_add(*result, integer_result, result);
    // printf("-=result=-\n");
    // print_bits_decimal(*result);
    // printf("-=remainder=-\n");
    // print_bits_decimal(remainder);
    // reset_decimal(&tmp_scale_decimal);
    // set_bit(&tmp_scale_decimal, 0);
    reset_decimal(&integer_result);
  }

  result->bits[3] |= (scale << 16);
}

void decimal_pow_of_two(int pow, s21_decimal *result) {
  s21_decimal two;
  reset_decimal(result);
  s21_from_int_to_decimal(2, &two);
  copy_decimal(two, result);
  if (pow == 0) {
    s21_from_int_to_decimal(1, result);
  } else {
    left_bit_shift_N_decimal(result, pow - 1);
  }
}