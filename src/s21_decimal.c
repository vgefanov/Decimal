#include "s21_decimal.h"


#include <stdio.h>


#define CEXP 0x00FF0000
#define SIGN 0x80000000


typedef struct {
    unsigned bits[6];
    unsigned cexp;
    unsigned sign;
} big_decimal;


// Возвращает степень коэффициента масштабирования
unsigned get_cexp(s21_decimal op) { return (op.bits[3] & CEXP) >> 16; }


// Возвращает знак
unsigned get_sign(s21_decimal op) { return (op.bits[3] & SIGN) >> 31; }


// Конвертирует decimal в big_decimal
big_decimal to_big_decimal(s21_decimal op) {
    big_decimal result = {
        {op.bits[0], op.bits[1], op.bits[2], 0, 0, 0},
        get_cexp(op),
        get_sign(op),
    };
    return result;
}


// Печатает big_decimal
void print_big_decimal(big_decimal op) {
    printf("[%s] %x %x %x %x %x %x (%x)\n", op.sign ? "-" : "+", op.bits[5],
        op.bits[4], op.bits[3], op.bits[2], op.bits[1], op.bits[0], op.cexp);
}


// Увеличивает коэффициент масштабирования на 1, увеличивает мантиссу на 10
big_decimal scale_big_decimal(big_decimal op) {
    big_decimal result = {{0, 0, 0, 0, 0, 0}, op.cexp + 1, op.sign};
    unsigned long long accum = 0;
    for (int i = 0; i < 6; i++) {
        accum = accum + (unsigned long long)op.bits[i] * 10;
        result.bits[i] = (unsigned)accum;
        accum = accum >> 32;
    }
    return result;
}


// Приводит big_decimal к нужному коэффициенту масштабирования
big_decimal normalize_big_decimal(big_decimal op, int cexp_add) {
    while (cexp_add--) {
        op = scale_big_decimal(op);
    }
    return op;
}


// Операторы сравнения

// сравнивает big_decimal с 0
bool is_null_big_decimal(big_decimal op) {
    int result = TRUE;
    for (int i = 5; i >= 0; i--) {
        if (op.bits[i] != 0) {
            result = FALSE;
            break;
        }
    }
    return result;
}


// сравнивает знаки двух big_decimal
// Возвращает:
// 1  op1 + op2 -
// 0  op1 + op2 +, op1 - op2 -
// -1 op1 - op2 +
int compare_sign_big_decimal(big_decimal op1, big_decimal op2) {
    int result = 0;
    if (op1.sign == 1 && op2.sign == 1) result = -2;
    if (op1.sign == 1 && op2.sign == 0) result = -1;
    if (op1.sign == 0 && op2.sign == 1) result =  1;
    if (op1.sign == 0 && op2.sign == 0) result =  2;
    return result;
}


// сравнивает значение двух децималов
int compare_digit_big_decimal(big_decimal op1, big_decimal op2) {
    int result = 0;
    if (op1.cexp > op2.cexp) {
        op2 = normalize_big_decimal(op2, op1.cexp - op2.cexp);
    }
    if (op2.cexp > op1.cexp) {
        op1 = normalize_big_decimal(op1, op2.cexp - op1.cexp);
    }
    for (int i = 5; i >= 0; i--) {
        if (op1.bits[i] > op2.bits[i]) {
            result = 1;
            break;
        } else if (op1.bits[i] < op2.bits[i]) {
            result = -1;
            break;
        }
    }
    return result;
}


// Меньше <
int s21_is_less(s21_decimal op1, s21_decimal op2) {
    big_decimal b_op1 = to_big_decimal(op1);
    big_decimal b_op2 = to_big_decimal(op2);
    int result = FALSE;
    if ((compare_sign_big_decimal(b_op1, b_op2) == 2 && compare_digit_big_decimal(b_op1, b_op2) == -1) ||
        (compare_sign_big_decimal(b_op1, b_op2) == -2 && compare_digit_big_decimal(b_op1, b_op2) == 1) ||
        (!is_null_big_decimal(b_op1) && compare_sign_big_decimal(b_op1, b_op2) == -1))
        result = TRUE;
    return result;
}


// Меньше или равно <=
int s21_is_less_or_equal(s21_decimal op1, s21_decimal op2) {
    return (s21_is_less(op1, op2) || s21_is_equal(op1, op2));
}


// Больше >
int s21_is_greater(s21_decimal op1, s21_decimal op2) {
    return (!s21_is_less(op1, op2) && !s21_is_equal(op1, op2));
}


// Больше или равно >=
int s21_is_greater_or_equal(s21_decimal op1, s21_decimal op2) {
    return (s21_is_greater(op1, op2) || s21_is_equal(op1, op2));
}


// Не равно !=
int s21_is_not_equal(s21_decimal op1, s21_decimal op2) {
    return !s21_is_equal(op1, op2);
}


// Возвращает результат умножения указанного Decimal на -1.
// int s21_negate(s21_decimal value, s21_decimal *result) { return 0; }