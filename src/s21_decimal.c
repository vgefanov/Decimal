#include "s21_decimal.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CEXP 0x00FF0000U
#define SIGN 0x80000000U

typedef struct {
    unsigned bits[6];
    unsigned cexp;
    unsigned sign;
} big_decimal;

int get_bit(big_decimal src, int i);
big_decimal simple_add(big_decimal op1, big_decimal op2);
big_decimal simple_div(big_decimal src1, big_decimal src2);
big_decimal simple_mul(big_decimal big_op1, big_decimal big_op2);

// Возвращает степень коэффициента масштабирования
unsigned get_cexp(s21_decimal op) { return (op.bits[3] & CEXP) >> 16; }

// Устанавливает степень коэффициента масштабирования
void set_cexp(s21_decimal *op, int value) { op->bits[3] = (op->bits[3] & SIGN) | (value << 16); }

// Возвращает знак
unsigned get_sign(s21_decimal op) { return (op.bits[3] & SIGN) >> 31; }

// Устанавливает знак
void set_sign(s21_decimal *value, int sign) {
    value->bits[3] = (sign) ? value->bits[3] | SIGN : value->bits[3] & ~SIGN;
}

// Конвертирует s21_decimal в big_decimal
big_decimal to_big_decimal(s21_decimal op) {
    big_decimal result = {
        {op.bits[0], op.bits[1], op.bits[2], 0, 0, 0},
        get_cexp(op),
        get_sign(op),
    };
    return result;
}

// Возвращает остаток от деления на 10
int big_decimal_mod_10(big_decimal src) {
    int dst = 0;
    for (int i = 191; i >= 0; i--) {
        dst = dst << 1;
        dst |= get_bit(src, i);
        if (dst >= 10) dst -= 10;
    }
    return dst;
}

// Конвертирует big_decimal в s21_decimal
s21_decimal big_decimal_to_decimal(big_decimal src, int *err_code) {
    *err_code = RESULT_SUCCESS;
    big_decimal ten = {10, 0, 0, 0, 0, 0, 0, 0};
    big_decimal one = {1, 0, 0, 0, 0, 0, 0, 0};
    unsigned cexp = src.cexp;
    unsigned sign = src.sign;
    int tmp_out = 0;
    bool full = FALSE;
    while (((src.bits[3] || src.bits[4] || src.bits[5]) && cexp) || cexp > 28) {
        full = TRUE;
        tmp_out = big_decimal_mod_10(src);
        src = simple_div(src, ten);
        cexp--;
    }
    if (src.bits[3] || src.bits[4] || src.bits[5]) {
        src = (big_decimal){0, 0, 0, 0, 0, 0, 0, 0};
        *err_code = MAXLIMIT_ERROR;
    }
    if (full && tmp_out > 4) {
        src = simple_add(src, one);
    }
    s21_decimal result = {src.bits[0], src.bits[1], src.bits[2], 0};
    set_sign(&result, sign);
    set_cexp(&result, cexp);
    return result;
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

// Сравнивает big_decimal с 0
bool is_null_big_decimal(big_decimal op) {
    int result = TRUE;
    for (int i = 5; i >= 0; i--) {
        if (op.bits[i]) {
            result = FALSE;
            break;
        }
    }
    return result;
}

// Сравнивает знаки двух big_decimal
int compare_sign_big_decimal(big_decimal op1, big_decimal op2) {
    int result = 0;
    if (op1.sign == 1 && op2.sign == 1) result = -2;
    if (op1.sign == 1 && op2.sign == 0) result = -1;
    if (op1.sign == 0 && op2.sign == 1) result = 1;
    if (op1.sign == 0 && op2.sign == 0) result = 2;
    return result;
}

// Сравнивает значение двух big_decimal
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

// Устанавливает s21_decimal в 0
void decimal_default(s21_decimal *dst) {
    for (int i = 0; i < 4; i++) {
        dst->bits[i] = 0;
    }
}

// Тестирует i-й бит big_decimal
int get_bit(big_decimal src, int i) {
    unsigned int bit = 1u << (i % 32);
    return !!(src.bits[i / 32] & bit);
}

// Устанавливает/cбрасывает i-й бит big_decimal
void set_bit(big_decimal *src, int i, int value) {
    unsigned int bit = 1u << (i % 32);
    if (value == 1) {
        src->bits[i / 32] |= bit;
    } else {
        src->bits[i / 32] &= ~bit;
    }
}

// Складывает два big_decimal без учета знака
big_decimal simple_add(big_decimal op1, big_decimal op2) {
    big_decimal result = {{0, 0, 0, 0, 0, 0}, op1.cexp, 0};
    unsigned long long accum = 0;
    for (int i = 0; i < 6; i++) {
        accum = accum + (unsigned long long)op1.bits[i] + (unsigned long long)op2.bits[i];
        result.bits[i] = (unsigned)accum;
        accum = accum >> 32;
    }
    return result;
}

// Вычитает из большего big_decimal меньшее без учета знака
big_decimal simple_sub(big_decimal op1, big_decimal op2) {
    big_decimal result = {{0, 0, 0, 0, 0, 0}, op1.cexp, 0};
    bool taken = FALSE;
    for (int i = 0; i < 192; i++) {
        int bit_value_1 = get_bit(op1, i);
        int bit_value_2 = get_bit(op2, i);
        if (bit_value_1 && bit_value_2) {
            if (taken) {
                set_bit(&result, i, 1);
            } else {
                set_bit(&result, i, 0);
            }
        } else if (bit_value_1 && !bit_value_2) {
            if (taken) {
                set_bit(&result, i, 0);
                taken = FALSE;
            } else {
                set_bit(&result, i, 1);
            }
        } else if (!bit_value_1 && bit_value_2) {
            if (taken) {
                set_bit(&result, i, 0);
            } else {
                set_bit(&result, i, 1);
                taken = TRUE;
            }
        } else if (!bit_value_1 && !bit_value_2) {
            if (taken) {
                set_bit(&result, i, 1);
            } else {
                set_bit(&result, i, 0);
            }
        }
    }
    return result;
}

// Сдвигает big_decimal влево на 1 разряд
big_decimal shift_bit_left(big_decimal src) {
    big_decimal dst = {0, 0, 0, 0, 0, 0, 0, 0};
    set_bit(&dst, 0, 0);
    for (int i = 1; i < 192; i++) {
        set_bit(&dst, i, get_bit(src, i - 1));
    }
    return dst;
}

// Сдвигает big_decimal вправо на 1 разряд
big_decimal shift_bit_right(big_decimal src) {
    big_decimal dst = {0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 191; i++) {
        set_bit(&dst, i, get_bit(src, i + 1));
    }
    set_bit(&dst, 191, 0);
    return dst;
}

big_decimal simple_mul(big_decimal big_op1, big_decimal big_op2) {
    unsigned exp = big_op1.cexp + big_op2.cexp;

    big_decimal dst = {0, 0, 0, 0, 0, 0, 0, 0};
    while (!is_null_big_decimal(big_op2)) {
        if (get_bit(big_op2, 0)) {
            dst = simple_add(dst, big_op1);
        }
        big_op1 = shift_bit_left(big_op1);
        big_op2 = shift_bit_right(big_op2);
    }
    dst.cexp = exp;
    return dst;
}

// Проверяет, что первый big_decimal больше второго
int greater_big_decimal(big_decimal src1, big_decimal src2) {
    int i = 5;
    for (; i >= 0 && src1.bits[i] == src2.bits[i]; i--) {
    }
    return (src1.bits[i] > src2.bits[i]) ? TRUE : FALSE;
}

// Проверяет два big_decimal на равенство
int equal_big_decimal(big_decimal src1, big_decimal src2) {
    bool equal = TRUE;
    for (int i = 0; i < 6 && equal; i++) {
        if (src1.bits[i] != src2.bits[i]) {
            equal = FALSE;
        }
    }
    return equal;
}

// Проверяет, что первый big_decimal больше или равен второму
int greater_or_equal_big_decimal(big_decimal src1, big_decimal src2) {
    return (greater_big_decimal(src1, src2) || equal_big_decimal(src1, src2));
}

// Простое деление
big_decimal simple_div(big_decimal src1, big_decimal src2) {
    big_decimal dst = {0, 0, 0, 0, 0, 0, 0, 0};
    int shift = 0;
    while (!get_bit(src2, 191 - shift)) {
        shift++;
    }
    for (int i = 0; !get_bit(src1, 191 - i); i++) {
        shift--;
    }
    if (shift >= 0) {
        for (int k = 0; k < shift; k++) {
            src2 = shift_bit_left(src2);
        }
        while (shift >= 0) {
            set_bit(&dst, 0, greater_or_equal_big_decimal(src1, src2));
            if (get_bit(dst, 0)) {
                src1 = simple_sub(src1, src2);
            }
            src2 = shift_bit_right(src2);
            if (shift) dst = shift_bit_left(dst);
            shift--;
        }
    }
    return dst;
}

// Вычисляет остаток от деления без знаков
big_decimal simple_mod(big_decimal src1, big_decimal src2) {
    int shift = 0;
    while (!get_bit(src2, 191 - shift)) {
        shift++;
    }
    for (int i = 0; !get_bit(src1, 191 - i); i++) {
        shift--;
    }
    if (shift >= 0) {
        for (int k = 0; k < shift; k++) {
            src2 = shift_bit_left(src2);
        }
        while (shift >= 0) {
            if (greater_or_equal_big_decimal(src1, src2)) {
                src1 = simple_sub(src1, src2);
            }
            src2 = shift_bit_right(src2);
            shift--;
        }
    }
    return src1;
}

// Арифметические операторы

// Сложение +
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = RESULT_SUCCESS;
    big_decimal big_op1 = to_big_decimal(value_1);
    big_decimal big_op2 = to_big_decimal(value_2);
    big_decimal dest = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned sign1 = get_sign(value_1), sign2 = get_sign(value_2), sign_res = 0, exp = 0;
    if (big_op1.cexp > big_op2.cexp) {
        big_op2 = normalize_big_decimal(big_op2, big_op1.cexp - big_op2.cexp);
    }
    if (big_op2.cexp > big_op1.cexp) {
        big_op1 = normalize_big_decimal(big_op1, big_op2.cexp - big_op1.cexp);
    }
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);
    exp = big_op1.cexp;
    if (!sign1 && !sign2) {
        dest = simple_add(big_op1, big_op2);
    } else if (sign1 && sign2) {
        sign_res = 1;
        dest = simple_add(big_op1, big_op2);
    } else if (sign1 && !sign2) {
        if (s21_is_less(value_1, value_2)) {
            dest = simple_sub(big_op2, big_op1);
        } else {
            dest = simple_sub(big_op1, big_op2);
            sign_res = 1;
        }
    } else if (!sign1 && sign2) {
        if (s21_is_less(value_1, value_2)) {
            dest = simple_sub(big_op2, big_op1);
            sign_res = 1;
        } else {
            dest = simple_sub(big_op1, big_op2);
            sign_res = 0;
        }
    }
    dest.cexp = exp;
    if (is_null_big_decimal(dest)) {
        sign_res = 0;
    }
    *result = big_decimal_to_decimal(dest, &error);
    if (!error) {
        set_sign(result, sign_res);
    } else {
        if (sign_res) {
            error = MINLIMIT_ERROR;
        }
    }
    return error;
}

// Вычитание -
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = RESULT_SUCCESS;
    big_decimal big_op1 = to_big_decimal(value_1);
    big_decimal big_op2 = to_big_decimal(value_2);
    big_decimal dest = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned sign1 = get_sign(value_1), sign2 = get_sign(value_2), sign_res = 0, exp = 0;
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);
    if (big_op1.cexp > big_op2.cexp) {
        big_op2 = normalize_big_decimal(big_op2, big_op1.cexp - big_op2.cexp);
    }
    if (big_op2.cexp > big_op1.cexp) {
        big_op1 = normalize_big_decimal(big_op1, big_op2.cexp - big_op1.cexp);
    }
    exp = big_op1.cexp;
    if (!sign1 && !sign2) {
        if (s21_is_less(value_1, value_2)) {
            dest = simple_sub(big_op2, big_op1);
            sign_res = 1;
        } else {
            dest = simple_sub(big_op1, big_op2);
            sign_res = 0;
        }
    } else if (sign1 && sign2) {
        if (s21_is_less(value_1, value_2)) {
            dest = simple_sub(big_op2, big_op1);
        } else {
            sign_res = 1;
            dest = simple_sub(big_op1, big_op2);
        }
    } else if (sign1 && !sign2) {
        dest = simple_add(big_op1, big_op2);
        sign_res = 1;
    } else if (!sign1 && sign2) {
        dest = simple_add(big_op1, big_op2);
        sign_res = 0;
    }
    dest.cexp = exp;
    *result = big_decimal_to_decimal(dest, &error);
    set_sign(result, sign_res);
    return error;
}

// Умножение *
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = RESULT_SUCCESS;
    int sign1 = get_sign(value_1), sign2 = get_sign(value_2), sign_res = 1;
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);
    if ((sign1 && sign2) || (!sign1 && !sign2)) {
        sign_res = 0;
    }
    big_decimal big_op1 = to_big_decimal(value_1);
    big_decimal big_op2 = to_big_decimal(value_2);
    if (is_null_big_decimal(big_op1) || is_null_big_decimal(big_op2)) {
        big_op1.cexp = 0;
        big_op2.cexp = 0;
    }
    big_decimal res_big = simple_mul(big_op1, big_op2);
    *result = big_decimal_to_decimal(res_big, &error);
    if (!error) {
        set_sign(result, sign_res);
    } else {
        error = (sign_res) ? MINLIMIT_ERROR : MAXLIMIT_ERROR;
    }
    return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int result_code = RESULT_SUCCESS;
    int sign1 = get_sign(value_1), sign2 = get_sign(value_2), sign_res = 1;
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);
    if ((sign1 && sign2) || (!sign1 && !sign2)) {
        sign_res = 0;
    }
    big_decimal value_1_big_decimal = to_big_decimal(value_1);
    big_decimal value_2_big_decimal = to_big_decimal(value_2);
    if (is_null_big_decimal(value_2_big_decimal)) {
        result_code = DIVBYZERO_ERROR;
        *result = (s21_decimal){0, 0, 0, 0};
    } else {
        if (value_1_big_decimal.cexp > value_2_big_decimal.cexp) {
            value_2_big_decimal = normalize_big_decimal(value_2_big_decimal,
                                                        value_1_big_decimal.cexp - value_2_big_decimal.cexp);
        }
        if (value_2_big_decimal.cexp > value_1_big_decimal.cexp) {
            value_1_big_decimal = normalize_big_decimal(value_1_big_decimal,
                                                        value_2_big_decimal.cexp - value_1_big_decimal.cexp);
        }
        big_decimal dst_big_decimal = simple_div(value_1_big_decimal, value_2_big_decimal);
        value_1_big_decimal = simple_mod(value_1_big_decimal, value_2_big_decimal);
        int cexp = 0;
        while (cexp < 28 && !is_null_big_decimal(value_1_big_decimal)) {
            big_decimal ten = {10, 0, 0, 0, 0, 0, 0, 0};
            value_1_big_decimal = simple_mul(value_1_big_decimal, ten);
            dst_big_decimal = simple_mul(dst_big_decimal, ten);
            dst_big_decimal =
                simple_add(dst_big_decimal, simple_div(value_1_big_decimal, value_2_big_decimal));
            value_1_big_decimal = simple_mod(value_1_big_decimal, value_2_big_decimal);
            cexp++;
        }
        dst_big_decimal.cexp = cexp;
        *result = big_decimal_to_decimal(dst_big_decimal, &result_code);
        set_sign(result, sign_res);
    }
    return result_code;
}

// Остаток от деления Mod
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int result_code = RESULT_SUCCESS;
    int sign = get_sign(value_1);
    int dst_exp = 0;
    dst_exp = get_cexp(value_1) >= get_cexp(value_2) ? get_cexp(value_1) : get_cexp(value_2);
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);
    if (s21_is_greater(value_1, value_2)) {
        big_decimal value_1_big_decimal = to_big_decimal(value_1);
        big_decimal value_2_big_decimal = to_big_decimal(value_2);
        if (is_null_big_decimal(value_2_big_decimal)) {
            result_code = DIVBYZERO_ERROR;
        } else {
            if (value_1_big_decimal.cexp > value_2_big_decimal.cexp) {
                value_2_big_decimal = normalize_big_decimal(
                    value_2_big_decimal, value_1_big_decimal.cexp - value_2_big_decimal.cexp);
            }
            if (value_2_big_decimal.cexp > value_1_big_decimal.cexp) {
                value_1_big_decimal = normalize_big_decimal(
                    value_1_big_decimal, value_2_big_decimal.cexp - value_1_big_decimal.cexp);
            }
            value_1_big_decimal = simple_mod(value_1_big_decimal, value_2_big_decimal);
            value_1 = big_decimal_to_decimal(value_1_big_decimal, &result_code);
        }
    } else {
        dst_exp = get_cexp(value_1);
    }
    set_cexp(&value_1, dst_exp);
    set_sign(&value_1, sign);
    *result = value_1;
    return result_code;
}

// Операторы сравнения

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

// Равно ==
int s21_is_equal(s21_decimal op1, s21_decimal op2) {
    big_decimal b_op1 = to_big_decimal(op1);
    big_decimal b_op2 = to_big_decimal(op2);
    bool result = FALSE;
    if (is_null_big_decimal(b_op1) && is_null_big_decimal(b_op2)) {
        result = TRUE;
    } else {
        int sign = compare_sign_big_decimal(b_op1, b_op2);
        if ((sign == -2 || sign == 2) && (compare_digit_big_decimal(b_op1, b_op2) == 0)) {
            result = TRUE;
        }
    }
    return result;
}

// Не равно !=
int s21_is_not_equal(s21_decimal op1, s21_decimal op2) { return !s21_is_equal(op1, op2); }

// Преобразователи

// Преобразовывает int в decimal
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    decimal_default(dst);
    if (src < 0) {
        src *= -1;
        set_sign(dst, 1);
    }
    dst->bits[0] = src;
    return RESULT_SUCCESS;
}

// Преобразовывает из float
#define FLOAT2DECIMAL_MASK "%+.6e"
#define FLOAT_STR_LEN 50

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int result_code = RESULT_SUCCESS;
    big_decimal result = {0, 0, 0, 0, 0, 0, 0, 0};
    if (src == -INFINITY) {
        result.sign = 1;
    }
    if (src > MAX_DECIMAL || src < MIN_DECIMAL || isnan(src) || src == INFINITY || src == -INFINITY ||
        src < 1e-28) {
        result_code = RESULT_ERROR;
    } else {
        char float_str[FLOAT_STR_LEN];
        snprintf(float_str, FLOAT_STR_LEN, FLOAT2DECIMAL_MASK, src);
        // Получаем +1.271234e+02
        //          -1.234500e-02
        int cexp_delta = (float_str[11] - '0') * 10 + (float_str[12] - '0');
        if (float_str[10] == '-') {
            cexp_delta = -cexp_delta;
        }
        float_str[9] = 0;
        // Обрезаем нули
        int end_pos = strlen(float_str) - 1;
        while (float_str[end_pos] == '0') {
            float_str[end_pos] = 0;
            end_pos--;
        }
        // Формируем целочисленное представление
        bool after_dot = FALSE;
        int cexp = 0;
        for (int pos = 1; float_str[pos]; pos++) {
            if (float_str[pos] == '.') {
                after_dot = TRUE;
            } else {
                result = scale_big_decimal(result);
                result.bits[0] += (float_str[pos] - '0');
                if (after_dot) {
                    cexp++;
                }
            }
        }
        while (cexp_delta > cexp) {
            result = scale_big_decimal(result);
            cexp++;
        }
        // Pасставляем степень и экспоненту
        result.cexp = cexp - cexp_delta;
        if (float_str[0] == '-') {
            result.sign = 1;
        }
    }
    int temp_result;
    *dst = big_decimal_to_decimal(result, &temp_result);
    return result_code;
}

// В int
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int error = RESULT_SUCCESS;
    big_decimal div10 = {{10, 0, 0, 0, 0, 0}, 0, 0};
    big_decimal tmp = to_big_decimal(src);
    unsigned cexp = get_cexp(src);
    unsigned sign = get_sign(src);
    while (cexp--) {
        tmp = simple_div(tmp, div10);
    }
    if ((!sign && (tmp.bits[0] > (unsigned)INT_MAX)) || (sign && (tmp.bits[0] > (unsigned)INT_MAX + 1))) {
        error = RESULT_ERROR;
    } else {
        *dst = (int)tmp.bits[0];
        if (sign) {
            *dst = -*dst;
        }
    }
    return error;
}

// Преобразовывает во float
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    double result = 0;
    for (int nb = 2; nb >= 0; nb--) {
        for (int i = 31; i >= 0; i--) {
            result *= 2;
            if (src.bits[nb] & ((unsigned)1 << i)) {
                result += 1;
            }
        }
    }
    unsigned cexp = get_cexp(src);
    while (cexp--) {
        result /= 10;
    }
    if (get_sign(src)) {
        result = -result;
    }
    *dst = (float)result;
    return RESULT_SUCCESS;
}

// Другие функции

// Округляет указанное Decimal число до ближайшего целого числа в сторону
// отрицательной бесконечности.
int s21_floor(s21_decimal value, s21_decimal *result) {
    s21_decimal delta = {0x87ffffff, 0x1f128130, 0x1027e72f, 0x801c0000};
    unsigned sign = get_sign(value);
    unsigned cexp = get_cexp(value);
    if (cexp != 0) {
        if (sign) {
            s21_add(value, delta, &value);
            s21_round(value, result);
        } else {
            s21_truncate(value, result);
        }
    } else {
        *result = value;
    }
    return RESULT_SUCCESS;
}

// Округляет Decimal до ближайшего целого числа.
int s21_round(s21_decimal value, s21_decimal *result) {
    unsigned sign = get_sign(value);
    unsigned cexp = get_cexp(value);
    if (cexp != 0) {
        s21_decimal tmp = {5, 0, 0, 0x00010000};

        if (sign) {
            tmp.bits[3] = 0x80010000;
            s21_add(value, tmp, &value);
        } else {
            s21_add(value, tmp, &value);
        }
        s21_truncate(value, result);
    } else {
        *result = value;
    }
    return RESULT_SUCCESS;
}

// Возвращает целые цифры указанного Decimal числа; любые дробные цифры
// отбрасываются, включая конечные нули.
int s21_truncate(s21_decimal value, s21_decimal *result) {
    int error = RESULT_SUCCESS;
    big_decimal div10 = {{10, 0, 0, 0, 0, 0}, 0, 0};
    big_decimal tmp = to_big_decimal(value);
    unsigned cexp = tmp.cexp;
    unsigned sign = tmp.sign;
    while (cexp--) {
        tmp = simple_div(tmp, div10);
    }
    tmp.sign = sign;
    *result = big_decimal_to_decimal(tmp, &error);
    return error;
}

// Возвращает результат умножения указанного Decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result) {
    *result = value;
    if (get_sign(value)) {
        set_sign(result, 0);
    } else {
        set_sign(result, 1);
    }
    return RESULT_SUCCESS;
}
