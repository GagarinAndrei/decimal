#include "s21_utils.h"

#include "s21_decimal.h"

int get_bit(s21_decimal value, int bit) {
  int result;
  int index = bit / 32;
  unsigned int mask = 1 << (bit % 32);
  result = (value.bits[index] & mask) ? 1 : 0;

  return result;
}

void set_bit(s21_decimal *value, int bit) {
  int index = bit / 32;
  unsigned int mask = 1 << (bit % 32);
  value->bits[index] |= mask;
}

void unset_bit(s21_decimal *value, int bit) {
  int index = bit / 32;
  unsigned int mask = ~(1 << (bit % 32));
  value->bits[index] &= mask;
}

void init_bcd(bcd *bcd_number, s21_decimal number) {
  for (int i = 0; i < BYTES_IN_BCD; i++) {
    bcd_number->bits[i] = 0;
  }

  bcd_number->sign = MINUS & number.bits[3] ? MINUS : 0;
  bcd_number->scale = SCALE & number.bits[3];
  unset_bit_in_bcd(bcd_number, 127);
  bcd_number->scale >>= 16;
}

void decimal_to_bcd(s21_decimal *decimal, bcd *bcd_number) {
  int bits_in_decimal = BYTES_IN_DECIMAL * 32;

  for (int shift_counter = 0; shift_counter < bits_in_decimal;
       shift_counter++) {
    // Коррекция

    for (int place = 0; place < BYTES_IN_BCD * 8; place++) {
      if (place % 8) {
        // Коррекция старших разрядов
        if (((bcd_number->bits[place / 8] >> ((place % 8) * 4)) & 15) >= 5) {
          bcd_number->bits[place / 8] += (3 << ((place % 8) * 4));
        }
      } else {
        // Коррекция младших разрядов
        if (((bcd_number->bits[place / 8]) & 15) >= 5) {
          bcd_number->bits[place / 8] += 3;
        }
      }
    }

    left_bit_shift_bcd(bcd_number);
    if (get_bit(*decimal, bits_in_decimal - 1) && shift_counter > 31) {
      set_bit_in_bcd(bcd_number, 0);
    }
    left_bit_shift_decimal(decimal);
  }
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

void left_bit_shift_bcd(bcd *bcd_number) {
  for (int i = BYTES_IN_BCD - 1; i >= 0; i--) {
    bcd_number->bits[i] <<= 1;
    if (i > 0) {
      int highest_bit_in_right_int = ((i - 1) * INT_BIT) + (INT_BIT - 1);
      if (get_bit_in_bcd(*bcd_number, highest_bit_in_right_int)) {
        set_bit_in_bcd(bcd_number, highest_bit_in_right_int + 1);
      }
    }
  }
}

int get_bit_in_bcd(bcd value, int bit) {
  int result;
  int index = bit / 32;
  unsigned int mask = 1 << (bit % 32);
  result = (value.bits[index] & mask) ? 1 : 0;

  return result;
}

void set_bit_in_bcd(bcd *value, int bit) {
  int index = bit / 32;
  unsigned int mask = 1 << (bit % 32);
  value->bits[index] |= mask;
}

void unset_bit_in_bcd(bcd *value, int bit) {
  int index = bit / 32;
  unsigned int mask = ~(1 << (bit % 32));
  value->bits[index] &= mask;
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

void print_bits_bsd(bcd number) {
  for (int i = 0; i < BYTES_IN_BCD; i++) {
    print_bits(number.bits[i]);
  }
  print_bits(number.scale);
  print_bits(number.sign);
}

void print_bits_decimal(s21_decimal number) {
  for (int i = 0; i < BYTES_IN_DECIMAL; i++) {
    print_bits(number.bits[i]);
  }
}

void normalize_scale(bcd *number_1, bcd *number_2) {
  int32_t max_scale =
      (number_1->scale > number_2->scale) ? number_1->scale : number_2->scale;
  int32_t min_scale =
      (number_1->scale < number_2->scale) ? number_1->scale : number_2->scale;
  int is_min_scale = (max_scale > number_1->scale) ? 1 : 0;

  for (int i = min_scale; i < max_scale; i++) {
    if (is_min_scale) {
      number_1->scale++;
      for (int i = 0; i < 4; ++i) left_bit_shift_bcd(number_1);
    } else {
      number_2->scale++;
      for (int i = 0; i < 4; ++i) left_bit_shift_bcd(number_2);
    }
  }
}

void full_convert_two_bcd_with_normalize(s21_decimal *value_1,
                                         s21_decimal *value_2,
                                         bcd *value_1_in_bcd,
                                         bcd *value_2_in_bcd) {
  init_bcd(value_1_in_bcd, *value_1);
  init_bcd(value_2_in_bcd, *value_2);
  decimal_to_bcd(value_1, value_1_in_bcd);
  decimal_to_bcd(value_2, value_2_in_bcd);
  normalize_scale(value_1_in_bcd, value_2_in_bcd);
}

void reset_bcd(bcd *value) {
  for (int i = 0; i < BYTES_IN_BCD; i++) {
    value->bits[i] = 0;
  }
  value->scale = 0;
  value->sign = 0;
}

void bcd_add(bcd value_1, bcd value_2, bcd *result_in_bcd) {
  unsigned int mask;
  int unit_in_mind = 0;
  int temp_result;
  for (int i = 0; i < BYTES_IN_BCD; i++) {
    for (int ii = 0; ii < 32; ii += 4) {
      mask = 15 << (ii);
      temp_result = ((value_1.bits[i] & mask) >> ii) +
                    ((value_2.bits[i] & mask) >> ii) + unit_in_mind;
      unit_in_mind = 0;
      if (temp_result > 9) {
        temp_result = temp_result % 10;
        unit_in_mind = 1;
      }
      result_in_bcd->bits[i] |= (temp_result << ii);
    }
  }
}

/**
 * value_1 должно быть больше value_2 по модулю
 */
void bcd_diff(bcd value_1, bcd value_2, bcd *result_in_bcd) {
  unsigned int mask;
  int unit_in_mind = 0;
  int temp_result;

  for (int i = 0; i < BYTES_IN_BCD; i++) {
    for (int ii = 0; ii < 32; ii += 4) {
      mask = 15 << (ii);
      temp_result = ((value_1.bits[i] & mask) >> ii) -
                    ((value_2.bits[i] & mask) >> ii) - unit_in_mind;
      unit_in_mind = 0;
      if (temp_result < 0) {
        temp_result = 10 + temp_result;
        unit_in_mind = 1;
      }
      result_in_bcd->bits[i] |= (temp_result << ii);
    }
  }
  if ((unsigned int)value_1.sign == MINUS) {
    result_in_bcd->sign |= MINUS;
  }
}

void bcd_mult(bcd value_1_in_bcd, bcd value_2_in_bcd,
                        bcd *result_in_bcd) {
  unsigned int mask_1;
  unsigned int mask_2;

  int unit_in_mind = 0;
  int numeric_digit;
  int temp_result;

  for (size_t i = 0; i < BYTES_IN_BCD; i++) {
    numeric_digit = 0;
    for (size_t iii = 0; iii < 32; iii += 4) {
      for (size_t ii = 0; ii < 32; ii += 4) {
        mask_1 = 15 << (ii);
        mask_2 = 15 << (iii);
        temp_result = ((value_1_in_bcd.bits[i] & mask_1) >> ii) *
                          ((value_2_in_bcd.bits[i] & mask_2) >> iii) +
                      unit_in_mind;
        unit_in_mind = 0;
        if (temp_result > 9) {
          unit_in_mind = temp_result / 10;
          temp_result = temp_result % 10;
        }
        result_in_bcd->bits[i] |= (temp_result << (ii + 4 * numeric_digit));
      }
      numeric_digit++;
    }
  }
}

void bcd_div(bcd value_1_in_bcd, bcd value_2_in_bcd, bcd *result_in_bcd) {
  unsigned int mask_1;
  unsigned int mask_2;

  int unit_in_mind = 0;
  int numeric_digit;
  int temp_result;


  for (size_t i = 0; i < BYTES_IN_BCD; i++) {
    numeric_digit = 0;
    for (size_t iii = 0; iii < 32; iii += 4) {
      for (size_t ii = 0; ii < 32; ii += 4) {
        mask_1 = 15 << (ii);
        mask_2 = 15 << (iii);
        // temp_result = ((value_1_in_bcd.bits[i] & mask_1) >> ii) *
        //                   ((value_2_in_bcd.bits[i] & mask_2) >> iii) +
        //               unit_in_mind;
        // unit_in_mind = 0;
        if (temp_result > 9) {
          // unit_in_mind = temp_result / 10;
          // temp_result = temp_result % 10;
        }
        // result_in_bcd->bits[i] |= (temp_result << (ii + 4 * numeric_digit));
      }
      // numeric_digit++;
    }
  }
}
