#include "s21_decimal.h"
#include "s21_utils.h"

/**
 * Сложение двух s21_decimal
 * @param value_1 1ое число
 * @param value_2 2ое число
 * @param result результат сложения
 * @result 0 - OK,
 * 1 - число слишком велико или равно бесконечности,
 * 2 - число слишком мало или равно отрицательной бесконечности
 */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  reset_decimal(result);
  normalize_scale(&value_1, &value_2);
  int result_code = 0;

  if (is_positive_decimal(value_1) == is_positive_decimal(value_2)) {
    int one_to_mind = 0;
    for (int index = 0; index < BYTES_IN_DECIMAL; index++) {
      for (int bit = 0; bit < INT_BIT; bit++) {
        if (get_bit(value_1, bit + (index * INT_BIT)) +
                get_bit(value_2, bit + (index * INT_BIT)) + one_to_mind ==
            0) {
          continue;
        }
        if (get_bit(value_1, bit + (index * INT_BIT)) +
                get_bit(value_2, bit + (index * INT_BIT)) + one_to_mind ==
            1) {
          set_bit(result, bit + (index * INT_BIT));
          one_to_mind = 0;
        }
        if (get_bit(value_1, bit + (index * INT_BIT)) +
                get_bit(value_2, bit + (index * INT_BIT)) + one_to_mind ==
            2) {
          one_to_mind = 1;
          continue;
        }
        if (get_bit(value_1, bit + (index * INT_BIT)) +
                get_bit(value_2, bit + (index * INT_BIT)) + one_to_mind ==
            3) {
          one_to_mind = 1;
          set_bit(result, bit + (index * INT_BIT));
        }
      }
    }
    if (!is_positive_decimal(value_1)) { // если оба знака не положительные
      set_minus_to_decimal(result);
    }
  }
  if (is_positive_decimal(value_1) != is_positive_decimal(value_2)) {
    s21_sub(abs_decimal(value_1), abs_decimal(value_2), result);
    if (s21_is_greater(abs_decimal(value_1), abs_decimal(value_2))) {
      set_minus_to_decimal(result);
    }
  }
  if (get_scale(value_1))
    set_scale(result, get_scale(value_1));

  if (get_bit(*result, 96)) {
    result_code = is_positive_decimal(*result) ? 1 : 2;
  }
  return result_code;
}

/**
 * вычитание s21_decimal из s21_decimal
 * @param value_1 1ое число
 * @param value_2 2ое число
 * @param result результат сложения
 * @result 0 - OK,
 * 1 - число слишком велико или равно бесконечности,
 * 2 - число слишком мало или равно отрицательной бесконечности
 */
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  reset_decimal(result);
  normalize_scale(&value_1, &value_2);
  if (is_positive_decimal(value_1) == is_positive_decimal(value_2)) {
    sub_smaller_from_larger(abs_decimal(value_1), abs_decimal(value_2), result);
    if (s21_is_greater(abs_decimal(value_1), abs_decimal(value_2))) {
      result->bits[3] |= (value_1.bits[3] & MINUS);
    } else {
      result->bits[3] |= (value_2.bits[3] & ~MINUS);
    }
  } else if (is_positive_decimal(value_1) && !is_positive_decimal(value_2)) {
    s21_add(abs_decimal(value_1), abs_decimal(value_2), result);
  } else if (!is_positive_decimal(value_1) && is_positive_decimal(value_2)) {
    s21_add(abs_decimal(value_1), abs_decimal(value_2), result);
    set_minus_to_decimal(result);
  }
  
  if (get_bit(*result, 96)) {
    return is_positive_decimal(*result) ? 1 : 2;
  }
  return 0;
}

/**
 * Умножение двух s21_decimal
 * @param value_1 1ое число
 * @param value_2 2ое число
 * @param result результат умножения
 * @result 0 - OK,
 * 1 - число слишком велико или равно бесконечности,
 * 2 - число слишком мало или равно отрицательной бесконечности
 */
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = 0;
  normalize_scale(&value_1, &value_2);
  s21_decimal tmp_value;
  normalize_scale(&value_1, &value_2);
  reset_decimal(result);
  for (int i = 0; i < INT_BIT * (BYTES_IN_DECIMAL - 1); i++) {
    if (get_bit(value_1, i)) {
      copy_decimal(value_2, &tmp_value);
      if (left_bit_shift_N_decimal(&tmp_value, i)) {
        s21_add(*result, tmp_value, result);
      } else {
        error_code =
            (is_positive_decimal(value_1) != is_positive_decimal(value_2)) ? 2
                                                                           : 1;
      }
    }
  }
  if (is_positive_decimal(value_1) != is_positive_decimal(value_2)) {
    set_minus_to_decimal(result);
  }

  return error_code;
}
