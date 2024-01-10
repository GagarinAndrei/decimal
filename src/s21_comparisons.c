#include "s21_decimal.h"
#include "s21_utils.h"

/**
 * сравнивает 2 значения s21_decimal
 * @param value_1 первое значение
 * @param value_2 второе значение
 * @return 0 - если первое не больше, 1 - если первое больше.
 */
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
    int flag = 1;
  if (is_positive_decimal(value_1) == is_positive_decimal(value_2)) {
    for (int bit = 95; bit >= 0 && flag == 1; bit--) {
      if (get_bit(value_1, bit) < get_bit(value_2, bit)) {
        flag = 0;
      }
      if (get_bit(value_1, bit) > get_bit(value_2, bit)) {
        break;
      }
      if (bit == 0 && get_bit(value_1, bit) == get_bit(value_2, bit)) {
        flag = 0;
      }
    }
  }
  if (is_positive_decimal(value_1) && !is_positive_decimal(value_2)) flag = 1;
  if (!is_positive_decimal(value_1) && is_positive_decimal(value_2)) flag = 0;
  if (!is_positive_decimal(value_1) && !is_positive_decimal(value_2))
    flag = !flag;

  return flag;
}
/**
 * сравнивает 2 значения s21_decimal
 * @param value_1 первое значение
 * @param value_2 второе значение
 * @return 0 - если первое не меньше, 1 - если первое меньше.
 */
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  for (int bit = 95; bit >= 0; bit--) {
    if (get_bit(value_1, bit) < get_bit(value_2, bit)) {
      flag = 1;
      break;
    }
  }
  if (is_positive_decimal(value_1) && !is_positive_decimal(value_2)) flag = 0;
  if (!is_positive_decimal(value_1) && is_positive_decimal(value_2)) flag = 1;
   if (!is_positive_decimal(value_1) && !is_positive_decimal(value_2))
    flag = !flag;
  return flag;
}

/**
 * сравнивает 2 значения s21_decimal
 * @param value_1 первое значение
 * @param value_2 второе значение
 * @return 0 - если первое не больше, 1 - если первое больше или равно.
 */
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  
  if(s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2)) {
    flag = 1;
  }

  return flag;
}
/**
 * сравнивает 2 значения s21_decimal
 * @param value_1 первое значение
 * @param value_2 второе значение
 * @return 0 - если первое не меньше , 1 - если первое меньше или равно.
 */
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  if(s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2)) {
    flag = 1;
  }
  return flag;
}
/**
 * сравнивает 2 значения s21_decimal
 * @param value_1 первое значение
 * @param value_2 второе значение
 * @return 0 - если не равны, 1 - если равны.
 */
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int flag = 1;
  for (int bit = 95; bit >= 0; bit--) {
    if (get_bit(value_1, bit) != get_bit(value_2, bit)) {
      flag = 0;
      break;
    }
    
  }
  if(is_positive_decimal(value_1) != is_positive_decimal(value_2)){
    flag = 0;
  }
  if(check_decimal_for_zero(value_1) && check_decimal_for_zero(value_2)){
    flag = 1;
  }

  return flag;
}

/**
 * сравнивает 2 значения s21_decimal
 * @param value_1 первое значение
 * @param value_2 второе значение
 * @return 0 - если равны, 1 - если не равны.
 */
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  for (int bit = 95; bit >= 0; bit--) {
    if (get_bit(value_1, bit) != get_bit(value_2, bit)) {
      flag = 1;
      break;
    }
  }

  if(is_positive_decimal(value_1) != is_positive_decimal(value_2)) {
    flag = 1;
  }
  if(check_decimal_for_zero(value_1)&& check_decimal_for_zero(value_2)){
    flag = 0;
  }

  return flag;
}
