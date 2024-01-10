#include <stdio.h>

#include "s21_decimal.h"
#include "s21_utils.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  reset_decimal(result);

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
    if(!is_positive_decimal(value_1)) { // если оба знака не положительные
      set_minus_to_decimal(result);
    }
  }
  if (is_positive_decimal(value_1) != is_positive_decimal(value_2)) {
    s21_sub(abs_decimal(value_1), abs_decimal(value_2), result);
    if(s21_is_greater(abs_decimal(value_1), abs_decimal(value_2))) {
      set_minus_to_decimal(result);
    }
  }

  return 0;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  reset_decimal(result);

  if(is_positive_decimal(value_1) == is_positive_decimal(value_2)){
    sub_smaller_from_larger(abs_decimal(value_1), abs_decimal(value_2) , result);
    if(s21_is_greater(abs_decimal(value_1), abs_decimal(value_2))) {
      result->bits[3] |= (value_1.bits[3] & MINUS);
    } else {

      result->bits[3] |= (value_2.bits[3] & ~MINUS);
    }
  } else if(is_positive_decimal(value_1) && !is_positive_decimal(value_2)){
    s21_add(abs_decimal(value_1), abs_decimal(value_2),result);
  } else if(!is_positive_decimal(value_1) && is_positive_decimal(value_2)) {
    s21_add(abs_decimal(value_1), abs_decimal(value_2),result);
    set_minus_to_decimal(result);
  }



  return 0;
}
