#include "s21_decimal.h"
#include "s21_utils.h"
#include <math.h>
#include <stdio.h>
#include <stdint.h>

#define FLOAT_BIT 32
#define MAX_DECIMAL powl(2.0, 96)
#define MIN_DECIMAL (-1 * MAX_DECIMAL)
#define MAX_POW 28
#define FLOAT_ACCURACY 7 // 7 значимых цифр по условию задачи
#define MANTISSA_END 96 

// // int s21_from_float_to_decimal(float src, s21_decimal *dst) {
// // // 	Значения с одиночной точностью и типом float имеют 4 байта, 
// // //  состоят из бита знака, 
// // //	8-битной экспоненты excess-127 и 23-битной мантиссы.
// // //  Мантисса представляет число от 1,0 до 2,0. 
// // //  Поскольку бит высокого порядка мантиссы всегда равен 1, он не сохраняется в числе. 
// // //  Это представление обеспечивает для типа float диапазон примерно от 3,4E–38 до 3,4E+38.

// // //	Поскольку экспоненты хранятся в форме без знака, экспоненты смещены на половину своего возможного значения. 
// // //	Для типа float смещение составляет 127
// // //	Можно вычислить фактическое значение экспоненты, вычтя значение смещения из значения экспоненты.


// // }

// // Чтобы перевести десятичную дробь в двоичную систему счисления, необходимо:
// // а) целую часть дроби перевести в двоичную систему согласно изученному алгоритму в пункте 2.1.1
// // б) дробную часть дроби умножить на 2, записать  полученную цифру результата ДО запятой (всегда равна 0 или 1, что логично), далее ТОЛЬКО дробную часть полученного результата снова умножить на 2, снова записать полученную цифру результата ДО запятой (0 или 1) и так далее, пока дробная часть результата умножения не станет равна 0 или до требуемого количества знаков после запятой (требуемой точности) (равно количеству умножений на 2). 
// // Затем необходимо записать полученную последовательность записанных нулей и единиц ПО ПОРЯДКУ после точки, разделяющей целую и дробную части вещественного (дробного) числа.

// // Пример 1.
// // Переведем число 2.25 (2 целых 25 сотых) из десятичной системы в двоичную. В двоичной системе дробь будет равна 10.01. Как мы это получили?

// // Число состоит из целой части ( до точки) - это 2 и дробной части - это 0.25.

// //  1) Перевод целой части:
// // 2/2 = 1 (остаток 0)
// // Целая часть будет 10.
// //  2)Перевод дробной части.
// // 0.25 * 2 = 0.5 (0)
// // 0.5   * 2 = 1.0 (1)
// // Дробная часть стала в результате последовательного умножения на 2 стала равна 0. Прекращаем умножение. 
// // Теперь "собираем" дробную часть ПО ПОРЯДКУ - получаем 0.01 в двоичной системе.
// // 3)Складываем целую и дробную части - получаем, что десятичная дробь 2.25 будет равна двоичной дроби 10.01.

// // Пример 2.
// // Переведем число 0.116 из десятичной системы в двоичную.

// // 0.116 * 2 = 0.232 (0)
// // 0.232 * 2 = 0.464 (0)
// // 0.464 * 2 = 0.928 (0)
// // 0.928 * 2 = 1.856 (1)     //отбрасываем целую часть данного результата
// // 0.856 * 2 = 1.712 (1)     //отбрасываем целую часть данного результата
// // 0.712 * 2 = 1.424 (1)     //отбрасываем целую часть данного результата
// // 0.424 * 2 = 0.848 (0)

// //     Как мы видим, умножение продолжается и продолжается, дробная часть результат никак не становится равной 0. Тогда решим, что мы переведем нашу десятичную дробь в двоичную с точностью до 7 знаков (бит) после точки (в дробной части). Вспоминаем, что мы же изучали про малозначимые разряды - чем дальше разряд (бит) от целой части, тем легче мы можем им пренебречь (объяснение в разделе 1 лекции, кто забыл).

// //     Получаем двоичную дробь 0.0001110 с точностью до 7 бит после точки.

// void reset_decimal(s21_decimal *dst);
// int get_mantissa_from_string(char *str);
// int get_exponent_from_string(char *str);

// void print_bits(int n);
// void print_bits_decimal(s21_decimal number) {
//     for(int i = 0; i < BYTES_IN_DECIMAL; i++) {
//         print_bits(number.bits[i]);
//     }
// }

// int main() {
// 	float f1 = 500.001;
// 	float f2 = 2.25E+0;
// 	int *ptrF1 = (int*)&f1;
// 	int *ptrF2 = (int*)&f2;
// 	print_bits(*ptrF1);
//     printf("%f\n", f1);
// 	print_bits(*ptrF2);
//     printf("%f\n", f2);

//     s21_decimal dec;
//     s21_from_float_to_decimal(f1, &dec);
//     printf("@%d@\n", dec.bits[0]);

//     print_bits_decimal(dec);

// 	return 0;
// }


// /**
//  * Обнуление элемента типа s21_decimal
//  * @param dst указатель на обнуляемый элемент 
// */
// void reset_decimal(s21_decimal *dst) {
//     for(int i = 0; i < BYTES_IN_DECIMAL; i++) {
//         dst->bits[i] = 0;
//     }
// }

// /**
// *   Выводит биты типа int в stdout
// *   @param n То, что выводим
// */
// void print_bits(int n) {
//     int i;
//     for (i = INT_BIT - 1; i >= 0; i--) {
//         printf("%d", (n & (1 << i)) != 0);
//         if(i == 31 || i == 24 || i == 16 || i == 8) {
//             printf(" ");
//         }
//     }
//     printf("\n");
// }

/**
 * Получение мантиссы из строчного представления типа float в научной нотации
 * @param str Указатель на строку
 * @return мантисса
 * 
*/
int get_mantissa_from_string(char *str) {
    int result = 0;
    char *ptr = str;
    result = strtol(ptr, NULL, 10);
    while (*ptr && *ptr != '.') {
        ptr++;
        if (*ptr == 'E') {
            ++ptr;
            break;
        }
    }
    ptr++;
	result = result * (pow(10, FLOAT_ACCURACY)) + strtol(ptr, NULL, 10);

    return result;
}

/**
 * Получение экспоненты из строчного представления типа float в научной нотации
 * @param str Указатель на строку
 * @return множитель экспоненты
 * 
*/
int get_exponent_from_string(char *str) {
    int result = 0;
    char *ptr = str;
    while (*ptr) {
        if (*ptr == 'E') {
            ++ptr;
            result = strtol(ptr, NULL, 10);
            break;
        }
        ++ptr;
    }

    return result;
}

// /**
//  * Конвертирует float в decimal
//  * @param src конвертируемый float
//  * @param dst указатель на decimal, в который запишется результат функции
//  * @return int код ошибки:
//  * 0 - OK, 
//  * 1 - ошибка конвертации
//  */
// // int s21_from_float_to_decimal(float src, s21_decimal *dst) { 
// //   int return_value = 0;
// //   reset_decimal(dst);
// //   if (fabs(src) < powl(10.0, -1 * MAX_POW)) {
// //     return_value = 1;
// //   } else if (src >= MAX_DECIMAL) {
// //     return_value = 1;
// //   } else if (src <= MIN_DECIMAL) {
// //     return_value = 1;
// //   } else {
// //     int scale = 0;
// //     if (src < 0.0)
// //       dst->bits[3] |= MINUS; 
// //     src = fabsl(src);
// //     for(; !(int)src && scale < MAX_POW; src *=10) { // normalize
// //         scale++;
// //     }
    
// //     for (int i = 0; src < MAX_DECIMAL && scale < MAX_POW && i < FLOAT_ACCURACY; i++) {
// //       src *= (long double)10.0;
// //       scale++;
// //     }
// //     for (int i = 0; src >= powl(10.0, -1 * (FLOAT_ACCURACY + 1)) && i < MANTISSA_END; i++) {
// //       src = floorl(src) / 2;
// //       if (src - floorl(src) > powl(10.0, -1 * (FLOAT_ACCURACY + 1))) {
// //         s21_set_bit(dst, i);
// //       } 
// //     }
// //     dst->bits[3] |= (scale << 16);

// //   }
// //   return return_value;
// // }

/**
 * Конвертирует float в decimal
 * @param src конвертируемый float
 * @param dst указатель на decimal, в который запишется результат функции
 * @return int код ошибки:
 * 0 - OK, 
 * 1 - ошибка конвертации
 */
// int s21_from_float_to_decimal(float src, s21_decimal *dst) {
//     char float_str[32] = {0};

//     sprintf(float_str, "%0.6E", src);
//     int mantissa = get_mantissa_from_string(float_str);
//     int exponent = get_exponent_from_string(float_str);
//     printf("mant = %d, expo = %d, str = %s\n", mantissa, exponent, float_str);

//     dst->bits[0] = mantissa;
//     dst->bits[3] = exponent << 16;

//     return 0;
// }


