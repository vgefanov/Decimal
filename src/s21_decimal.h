#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_


typedef struct {
    unsigned bits[4];
} s21_decimal;


#define TRUE  1
#define FALSE 0
typedef unsigned short bool;


// Арифметические операторы

// Сложение +
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Вычитание -
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Умножение *
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Деление /
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Остаток от деления Mod
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);


// Операторы сравнения

// Меньше <
int s21_is_less(s21_decimal, s21_decimal);

// Меньше или равно <=
int s21_is_less_or_equal(s21_decimal, s21_decimal);

// Больше >
int s21_is_greater(s21_decimal, s21_decimal);

// Больше или равно >=
int s21_is_greater_or_equal(s21_decimal, s21_decimal);

// Равно ==
int s21_is_equal(s21_decimal, s21_decimal);

// Не равно !=
int s21_is_not_equal(s21_decimal, s21_decimal);


// Преобразователи

// Из int
int s21_from_int_to_decimal(int src, s21_decimal *dst);

// Из float
int s21_from_float_to_decimal(float src, s21_decimal *dst);

// В int
int s21_from_decimal_to_int(s21_decimal src, int *dst);

// В float
int s21_from_decimal_to_float(s21_decimal src, float *dst);


// Другие функции

// Округляет указанное Decimal число до ближайшего целого числа в сторону отрицательной бесконечности.
int s21_floor(s21_decimal value, s21_decimal *result);

// Округляет Decimal до ближайшего целого числа.
int s21_round(s21_decimal value, s21_decimal *result);

// Возвращает целые цифры указанного Decimal числа; любые дробные цифры отбрасываются, включая конечные нули.
int s21_truncate(s21_decimal value, s21_decimal *result);

// Возвращает результат умножения указанного Decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result);

#endif  // SRC_S21_DECIMAL_H_
