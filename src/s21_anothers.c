#include "s21_decimal.h"
#include "s21_utils.h"

/**
 * Округляет указанное Decimal число до ближайшего целого числа в сторону отрицательной бесконечности.
 * @param value Округляемое число
 * @param result Результат округления
 * @return 0 - OK, 
 * 1 - ошибка вычисления
*/
int s21_floor(s21_decimal value, s21_decimal *result) {
	s21_decimal negative_one_decimal = {{ 1, 0, 0, MINUS}};
	int value_scale = get_scale(value);
	if(value_scale) {
		for(int i = 0; i < value_scale; i++) {
			decrease_scale(&value);
		}
		if(!is_positive_decimal(value)) {
			s21_add(value, negative_one_decimal, &value);
		}
	}
	copy_decimal(value, result);

	return 0;
}

/**
 * Округляет Decimal до ближайшего целого числа.
 * @param value Округляемое число
 * @param result Результат округления
 * @return 0 - OK, 
 * 1 - ошибка вычисления
*/
int s21_round(s21_decimal value, s21_decimal *result) {
	s21_decimal one_decimal = {{ 1, 0, 0, 0}};
	int value_scale = get_scale(value);
	int remainder = 0;
	reset_decimal(result);
	if(value_scale) {
		for(int i = 0; i < value_scale; i++) {
			remainder = decrease_scale(&value);
		}
		if(remainder > 5) {
			if(is_positive_decimal(value)) {
				s21_add(value, one_decimal, &value);
			} else {
				s21_sub(value, one_decimal, &value);
			}
		}
	}
	copy_decimal(value, result);

	return 0;
}

/**
 * Возвращает целые цифры указанного Decimal числа; любые дробные цифры отбрасываются, включая конечные нули.
 * @param value Округляемое число
 * @param result Результат округления
 * @return 0 - OK, 
 * 1 - ошибка вычисления
*/
int s21_truncate(s21_decimal value, s21_decimal *result) {
	int value_scale = get_scale(value);
	reset_decimal(result);
	if(value_scale) {
		for(int i = 0; i < value_scale; i++) {
			decrease_scale(&value);
		}
	}
	copy_decimal(value, result);

	return 0;
}

/**
 * Возвращает результат умножения указанного Decimal на -1.
 * @param value число Decimal
 * @param result Результат округления
 * @return 0 - OK, 
 * 1 - ошибка вычисления
*/
int s21_negate(s21_decimal value, s21_decimal *result) {
	value.bits[3] ^= MINUS;
	copy_decimal(value, result);

	return 0;
}

