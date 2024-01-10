#include <stddef.h>
#include <stdio.h>

#include "s21_decimal.h"
#include "s21_utils.h"

// /**
//  * сложовка двух децолов
//  * @param value_1 первый децл
//  * @param value_2 второй децл
//  * @param result итоговый децл
//  * @return 0 - OK
//  * 1 - число слишком велико или равно бесконечности
//  * 2 - число слишком мало или равно отрицательной бесконечности
//  */
// int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   bcd value_1_in_bcd, value_2_in_bcd, result_in_bcd;

//   s21_decimal val1 = value_1;
//   s21_decimal val2 = value_2;

//   reset_bcd(&value_1_in_bcd);
//   reset_bcd(&value_2_in_bcd);
//   reset_bcd(&result_in_bcd);

//   full_convert_two_bcd_with_normalize(&val1, &val2, &value_1_in_bcd,
//                                       &value_2_in_bcd);
//   int is_different_signs = 0;

//   if (value_1_in_bcd.sign && value_2_in_bcd.sign) {
//     result_in_bcd.sign = MINUS;
//   } else if (value_1_in_bcd.sign || value_2_in_bcd.sign)
//     is_different_signs = 1;

//   if (!is_different_signs)
//     tmp_result_of_adding(value_1_in_bcd, value_2_in_bcd, &result_in_bcd);
//   else {
//     value_1.bits[3] &= ~MINUS;
//     value_2.bits[3] &= ~MINUS;

//     if (s21_is_greater(value_1, value_2)) {
//       tmp_result_of_diff(value_1_in_bcd, value_2_in_bcd, &result_in_bcd);
//     } else {
//       tmp_result_of_diff(value_2_in_bcd, value_1_in_bcd, &result_in_bcd);
//     }
//   }
//   result_in_bcd.scale = value_1_in_bcd.scale;

//   print_bits_bsd(result_in_bcd);
//   // конвертировать result_in_bcd в децимал и записать в result
//   // и вернуть код выполнения операции
//   result->bits[0] = 1;
//   result->bits[1] = 1;
//   result->bits[2] = 1;
//   result->bits[3] = 0;
//   return 0;
// }

// /**
//  * Вычитовка децла из децла
//  * @param value_1 Децл, из которого нужно вычесть
//  * @param value_2 Вычитаемый децл
//  * @param result Децл, в который записывается результат вычитовки
//  * @return 0 - OK
//  * 1 - число слишком велико или равно бесконечности
//  * 2 - число слишком мало или равно отрицательной бесконечности
// */
// int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   bcd value_1_in_bcd, value_2_in_bcd, result_in_bcd;

//   s21_decimal val1 = value_1;
//   s21_decimal val2 = value_2;

//   reset_bcd(&value_1_in_bcd);
//   reset_bcd(&value_2_in_bcd);
//   reset_bcd(&result_in_bcd);

//   full_convert_two_bcd_with_normalize(&val1, &val2, &value_1_in_bcd,
//                                       &value_2_in_bcd);

//   if (value_1_in_bcd.sign && !value_2_in_bcd.sign) {
//     tmp_result_of_adding(value_1_in_bcd, value_2_in_bcd, &result_in_bcd);
//     result_in_bcd.sign = MINUS;
//   } else if ((!value_1_in_bcd.sign && !value_2_in_bcd.sign) ||
//              (value_1_in_bcd.sign && value_2_in_bcd.sign)) {
//     value_1.bits[3] &= ~MINUS;
//     value_2.bits[3] &= ~MINUS;

//     if (s21_is_greater(value_1, value_2)) {
//       tmp_result_of_diff(value_1_in_bcd, value_2_in_bcd, &result_in_bcd);
//     } else {
//       if (value_1_in_bcd.sign && value_2_in_bcd.sign) {
//         tmp_result_of_diff(value_2_in_bcd, value_1_in_bcd, &result_in_bcd);
//         result_in_bcd.sign &= ~MINUS;
//       } else {
//         tmp_result_of_diff(value_2_in_bcd, value_1_in_bcd, &result_in_bcd);
//         result_in_bcd.sign |= MINUS;
//       }
//     }
//   } else if (!value_1_in_bcd.sign && value_2_in_bcd.sign) {
//     tmp_result_of_adding(value_1_in_bcd, value_2_in_bcd, &result_in_bcd);
//   }

//   result_in_bcd.scale = value_1_in_bcd.scale;

//   print_bits_bsd(result_in_bcd);
//   result->bits[0] = 1;
//   result->bits[1] = 1;
//   result->bits[2] = 1;
//   result->bits[3] = 0;
//   return 0;
// }

// int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   bcd value_1_in_bcd, value_2_in_bcd, result_in_bcd;
//   s21_decimal val1 = value_1;
//   s21_decimal val2 = value_2;

//   reset_bcd(&value_1_in_bcd);
//   reset_bcd(&value_2_in_bcd);
//   reset_bcd(&result_in_bcd);

//   full_convert_two_bcd_with_normalize(&val1, &val2, &value_1_in_bcd,
//                                       &value_2_in_bcd);
//   if (value_1_in_bcd.sign != value_2_in_bcd.sign) result_in_bcd.sign = MINUS;
//   result_in_bcd.scale = value_1_in_bcd.scale; // ?

//   if (s21_is_greater(value_1, value_2)) {
//     tmp_result_of_mult(value_1_in_bcd, value_2_in_bcd, &result_in_bcd);
//   } else {
//     tmp_result_of_mult(value_2_in_bcd, value_1_in_bcd, &result_in_bcd);
//   }

//   // print_bits_bsd(result_in_bcd);

//   result->bits[0] = 1;
//   result->bits[1] = 1;
//   result->bits[2] = 1;
//   result->bits[3] = 0;

//   return 0;
// }

// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
