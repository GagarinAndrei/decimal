#include "s21_decimal.h"
#include "s21_utils.h"

// int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
//   int result = 0;
//   bcd value_1_in_bcd;
//   bcd value_2_in_bcd;
//   full_convert_two_bcd_with_normalize(&value_1, &value_2, &value_1_in_bcd,
//                                       &value_2_in_bcd);

//   for (int i = BYTES_IN_BCD - 1; i >= 0; i--) {
//     if (value_1_in_bcd.bits[i] < value_2_in_bcd.bits[i]) {
//       result = 1;
//       i = -1;
//     } else if (value_1_in_bcd.bits[i] > value_2_in_bcd.bits[i]) {
//       result = 0;
//       i = -1;
//     }
//   }
//   if (value_1_in_bcd.sign < 0 && value_2_in_bcd.sign == 0) result = 1;
//   if (value_2_in_bcd.sign < 0 && value_1_in_bcd.sign == 0) result = 0;

//   return (value_1_in_bcd.sign < 0 && value_2_in_bcd.sign < 0) ? !result
//                                                               : result;
// }

// int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
//   return (s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2)) ? 1
//                                                                            : 0;
// }

// int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
//   return (!s21_is_less_or_equal(value_1, value_2)) ? 1 : 0;
// }

// int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
//   return (!s21_is_less(value_1, value_2)) ? 1 : 0;
// }

// int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
//   int result = 1;
//   bcd value_1_in_bcd;
//   bcd value_2_in_bcd;
//   full_convert_two_bcd_with_normalize(&value_1, &value_2, &value_1_in_bcd,
//                                       &value_2_in_bcd);

//   if (value_1_in_bcd.sign < value_2_in_bcd.sign) result = 0;

//   for (int i = 0; i < BYTES_IN_BCD && result != 0; i++) {
//     if (value_1_in_bcd.bits[i] != value_2_in_bcd.bits[i]) {
//       result = 0;
//     }
//   }
//   return result;
// }

// int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
//   int result = 1;
//   bcd value_1_in_bcd;
//   bcd value_2_in_bcd;
//   full_convert_two_bcd_with_normalize(&value_1, &value_2, &value_1_in_bcd,
//                                       &value_2_in_bcd);
//   for (int i = 0; i < BYTES_IN_BCD; i++) {
//     if (value_1_in_bcd.bits[i] == value_2_in_bcd.bits[i]) {
//       result = 0;
//     } else {
//       result = 1;
//       i = BYTES_IN_BCD;
//     }
//   }

//   return result;
// }
