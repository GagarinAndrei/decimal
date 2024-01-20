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
  int result_code = 0;
  reset_decimal(result);
  normalize_scale(&value_1, &value_2);

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
    if (!is_positive_decimal(value_1) &&
        !is_positive_decimal(value_2)) { // если оба знака не положительные
      set_minus_to_decimal(result);
    }
  }
  if (is_positive_decimal(value_1) != is_positive_decimal(value_2)) {
    if (s21_is_greater(abs_decimal(value_1), abs_decimal(value_2))) {
      s21_sub(abs_decimal(value_1), abs_decimal(value_2), result);
      if (!is_positive_decimal(value_1))
        set_minus_to_decimal(result);
    } else {
      s21_sub(abs_decimal(value_2), abs_decimal(value_1), result);
      if (!is_positive_decimal(value_2))
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
  int result_code = 0;
  reset_decimal(result);
  normalize_scale(&value_1, &value_2);
  if (is_positive_decimal(value_1) == is_positive_decimal(value_2)) {
    sub_smaller_from_larger(abs_decimal(value_1), abs_decimal(value_2), result);
    if (s21_is_greater(abs_decimal(value_1), abs_decimal(value_2))) {
      result->bits[3] |= (value_1.bits[3] & MINUS);
    } else if (s21_is_greater(value_2, value_1)) {
      result->bits[3] |= MINUS;
    }
  } else if (is_positive_decimal(value_1) && !is_positive_decimal(value_2)) {
    s21_add(abs_decimal(value_1), abs_decimal(value_2), result);
  } else if (!is_positive_decimal(value_1) && is_positive_decimal(value_2)) {
    s21_add(abs_decimal(value_1), abs_decimal(value_2), result);
    set_minus_to_decimal(result);
  }

  if (get_bit(*result, 96)) {
    result_code = is_positive_decimal(*result) ? 1 : 2;
  }
  return result_code;
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

/**
 * Деление двух s21_decimal
 * @param value_1 1ое число
 * @param value_2 2ое число
 * @param result результат деления
 * @result 0 - OK,
 * 1 - число слишком велико или равно бесконечности
 * 2 - число слишком мало или равно отрицательной бесконечности
 * 3 - деление на 0
 */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int start_index_of_dividend;
  int is_bit_set = 0;
  s21_decimal quotient;
  s21_decimal tmp_dividend;
  s21_decimal divisor;
  copy_decimal(value_2, &divisor);
  reset_decimal(&tmp_dividend);
  reset_decimal(&quotient);

  if (check_decimal_for_zero(value_2))
    return 3;
  int result_code = 0;
  normalize_scale(&value_1, &value_2);

  for (int i = 95; i >= 0; i--) {
    if (get_bit(value_1, i)) {
      start_index_of_dividend = i;
      set_bit(&tmp_dividend, 0);
    }
    break;
  }

  for (int i = start_index_of_dividend; i >= 0; i--) {
    // left_bit_shift_decimal(&quotient);
    if (s21_is_greater(value_2, tmp_dividend)) {
      left_bit_shift_decimal(&quotient);
      left_bit_shift_decimal(&tmp_dividend);
      true_set_bit(&tmp_dividend, get_bit(value_1, i - 1), 0);
    } else {
      set_bit(&quotient, 0);
      is_bit_set = 1;
      s21_sub(tmp_dividend, divisor, &reminder); //остановились на пятом пункте
    }
  }

  // s21_decimal tmp_result_int = {0};
  // s21_decimal tmp_result_frac = {0};
  // s21_decimal dividend, divisor, remainder_of_division;
  // reset_decimal(&remainder_of_division);
  // reset_decimal(&tmp_result_int);
  // reset_decimal(&tmp_result_frac);
  // normalize_scale(&value_1, &value_2);
  // dividend = abs_decimal(value_1);
  // divisor = abs_decimal(value_2);

  // if (s21_is_less(dividend, divisor)) {
  //   fractional_quitient(dividend, divisor, &tmp_result_frac);
  // } else if (s21_is_greater(dividend, divisor)) {
  //   remainder_of_division =
  //       integer_quotient(dividend, divisor, &tmp_result_int);
  //   fractional_quitient(remainder_of_division, divisor, &tmp_result_frac);
  // }
  // if (s21_is_not_equal(dividend, divisor))
  //   s21_add(tmp_result_int, tmp_result_frac, result);
  // else
  //   s21_from_int_to_decimal(1, result);

  if (is_positive_decimal(value_1) != is_positive_decimal(value_2))
    set_minus_to_decimal(result);

  return result_code;
}
