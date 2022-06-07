#include "s21_decimal.h"

#include <limits.h>
#include <stdio.h>

#define CEXP 0x00FF0000
#define SIGN 0x80000000

typedef struct {
  unsigned bits[6];
  unsigned cexp;
  unsigned sign;
} big_decimal;

unsigned get_cexp(s21_decimal op) {
  // Возвращает степень коэффициента масштабирования
  return ((op.bits[3] & CEXP) >> 16);
}

void set_exp(s21_decimal *op, int value) {
  op->bits[3] &= SIGN;
  value <<= 16;
  op->bits[3] |= value;
}

unsigned get_sign(s21_decimal op) {
  // Возвращает знак
  return (op.bits[3] & SIGN) >> 31;
}

// Устанавливает знак
void set_sign(s21_decimal *value, int sign) {
  if (sign == 1) {
    value->bits[3] |= SIGN;
  } else if (sign == 0) {
    value->bits[3] &= ~SIGN;
  }
}

s21_decimal big_decimal_to_decimal(big_decimal src) {
  s21_decimal result = {src.bits[0], src.bits[1], src.bits[2], 0};
  set_sign(&result, src.sign);
  set_exp(&result, src.cexp);
  return result;
}

big_decimal to_big_decimal(s21_decimal op) {
  // Конвертирует decimal в big_decimal
  big_decimal result = {
      {op.bits[0], op.bits[1], op.bits[2], 0, 0, 0},
      get_cexp(op),
      get_sign(op),
  };
  return result;
}

void print_big_decimal(big_decimal op) {
  printf("[%s] %x %x %x %x %x %x (%x)\n", op.sign ? "-" : "+", op.bits[5],
         op.bits[4], op.bits[3], op.bits[2], op.bits[1], op.bits[0], op.cexp);
}

big_decimal scale(big_decimal op) {
  // Увеличивает коэффициент масштабирования на 1, увеличивает мантиссу на 10
  big_decimal result = {{0, 0, 0, 0, 0, 0}, op.cexp + 1, op.sign};
  unsigned long long accum = 0;
  for (int i = 0; i < 6; i++) {
    accum = accum + (unsigned long long)op.bits[i] * 10;
    result.bits[i] = (unsigned)accum;
    accum = accum >> 32;
  }
  return result;
}

big_decimal normalize(big_decimal op, int cexp_add) {
  while (cexp_add--) {
    op = scale(op);
  }
  return op;
}

// сравнивает децимал с 0
bool compare_null(s21_decimal op) {
  big_decimal big_op = to_big_decimal(op);
  int result = TRUE;
  for (int i = 5; i >= 0; i--) {
    if (big_op.bits[i] != 0) {
      result = FALSE;
      break;
    }
  }
  return result;
}
// сравнивает знаки двух децималов
int compare_sign(s21_decimal op1, s21_decimal op2) {
  big_decimal big_op1 = to_big_decimal(op1);
  big_decimal big_op2 = to_big_decimal(op2);
  int result = 0;
  if (big_op1.sign == 1 && big_op2.sign == 1) result = -2;  // (-,-)
  if (big_op1.sign == 1 && big_op2.sign == 0) result = -1;  // (-,+)
  if (big_op1.sign == 0 && big_op2.sign == 1) result = 1;   // (+,-)
  if (big_op1.sign == 0 && big_op2.sign == 0) result = 2;   // (+,+)
  return result;
}
// сравнивает значение двух децималов
int compare_digit(s21_decimal op1, s21_decimal op2) {
  big_decimal big_op1 = to_big_decimal(op1);
  big_decimal big_op2 = to_big_decimal(op2);
  int result = 0;
  if (big_op1.cexp > big_op2.cexp) {
    big_op2 = normalize(big_op2, big_op1.cexp - big_op2.cexp);
  }
  if (big_op2.cexp > big_op1.cexp) {
    big_op1 = normalize(big_op1, big_op2.cexp - big_op1.cexp);
  }
  for (int i = 5; i >= 0; i--) {
    if (big_op1.bits[i] > big_op2.bits[i]) {
      result = 1;
      break;
    } else if (big_op1.bits[i] < big_op2.bits[i]) {
      result = -1;
      break;
    }
  }
  return result;
}
// Меньше <
int s21_is_less(s21_decimal op1, s21_decimal op2) {
  int result = FALSE;
  if ((compare_sign(op1, op2) == 2 && compare_digit(op1, op2) == -1) ||
      (compare_sign(op1, op2) == -2 && compare_digit(op1, op2) == 1) ||
      (compare_null(op1) == FALSE && compare_null(op2) == FALSE &&
       compare_sign(op1, op2) == -1))
    result = TRUE;
  return result;
}
// Меньше или равно <=
int s21_is_less_or_equal(s21_decimal op1, s21_decimal op2) {
  int result = FALSE;
  if (s21_is_less(op1, op2) == TRUE || s21_is_equal(op1, op2) == TRUE)
    result = TRUE;
  return result;
}
// Больше >
int s21_is_greater(s21_decimal op1, s21_decimal op2) {
  int result = FALSE;
  if (s21_is_less(op1, op2) == FALSE && s21_is_equal(op1, op2) == FALSE)
    result = TRUE;
  return result;
}
// Больше или равно >=
int s21_is_greater_or_equal(s21_decimal op1, s21_decimal op2) {
  int result = FALSE;
  if (s21_is_greater(op1, op2) == TRUE || s21_is_equal(op1, op2) == TRUE)
    result = TRUE;
  return result;
}
// Равно ==
int s21_is_equal(s21_decimal op1, s21_decimal op2) {
  bool result = FALSE;
  if (((compare_null(op1) == TRUE) && (compare_null(op2) == TRUE)) ||
      (compare_null(op1) == FALSE) && (compare_null(op2) == FALSE) &&
          (compare_digit(op1, op2) == 0) &&
          ((compare_sign(op1, op2) == -2) || (compare_sign(op1, op2) == 2)))
    result = TRUE;
  return result;
}
// Не равно !=
int s21_is_not_equal(s21_decimal op1, s21_decimal op2) {
  int result = FALSE;
  if (s21_is_equal(op1, op2) == FALSE) result = TRUE;
  return result;
}

// Записывает в dst 0
void decimal_default(s21_decimal *dst) {
  for (int i = 0; i < 4; i++) dst->bits[i] = 0;
}

// Возвращает результат умножения указанного Decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;
  if (get_sign(value)) {
    set_sign(result, 0);
  } else {
    set_sign(result, 1);
  }
  return 0;
}

// преобразовывает int в decimal
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  decimal_default(dst);
  if (src < 0) {
    src *= -1;
    set_sign(dst, 1);
  }
  dst->bits[0] = src;
  return 0;
}

s21_decimal div_10(s21_decimal src) {
  s21_decimal dst;
  decimal_default(&dst);
  return dst;
}

s21_decimal cut_decimal(s21_decimal src) {
  s21_decimal dst;
  decimal_default(&dst);
  set_sign(&dst, get_sign(src));
  dst = src;
  for (int i = get_cexp(src); i > 0; i--) {
    dst = div_10(dst);
  }
  return dst;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 1;
  src = cut_decimal(src);
  if (src.bits[0] <= ((unsigned int)INT_MAX) && !src.bits[1] && !src.bits[2]) {
    *dst = src.bits[0];
    res = 0;
    if (get_sign(src)) {
      *dst *= -1;
    }
  }
  return res;
}

int get_bit(big_decimal src, int i) {
  unsigned int bit = 1u << (i % 32);
  return !!(src.bits[i / 32] & bit);
}

void set_bit(big_decimal *src, int i, int value) {
  unsigned int bit = 1u << (i % 32);
  if (value == 1) {
    src->bits[i / 32] |= bit;
  } else {
    src->bits[i / 32] &= ~bit;
  }
}

big_decimal shift_bit_left(big_decimal src) {
  big_decimal dst = {0, 0, 0, 0, 0, 0, 0, 0};
  set_bit(&dst, 0, 0);
  for (int i = 1; i < 192; i++) {
    set_bit(&dst, i, get_bit(src, i - 1));
  }
  return dst;
}

big_decimal shift_bit_right(big_decimal src) {
  big_decimal dst = {0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 191; i++) {
    set_bit(&dst, i, get_bit(src, i + 1));
  }
  set_bit(&dst, 191, 0);
  return dst;
}

big_decimal simple_sub(big_decimal value_1, big_decimal value_2) {
  big_decimal result = {{0, 0, 0, 0, 0, 0}, value_1.cexp, 0};
  bool taken = FALSE;
  for (int i = 0; i < 192; i++) {
    int bit_value_1 = get_bit(value_1, i);
    int bit_value_2 = get_bit(value_2, i);
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
        // taken = TRUE;
      } else {
        set_bit(&result, i, 1);
        taken = TRUE;
      }
    } else if (!bit_value_1 && !bit_value_2) {
      if (taken) {
        set_bit(&result, i, 1);
        // taken = FALSE;
      } else {
        set_bit(&result, i, 0);
      }
    }
  }
  return result;
}

// сложение двух положительных
big_decimal simple_add(big_decimal value_1, big_decimal value_2) {
  big_decimal result = {{0, 0, 0, 0, 0, 0}, value_1.cexp, 0};
  unsigned long long accum = 0;
  for (int i = 0; i < 6; i++) {
    accum = accum + (unsigned long long)value_1.bits[i] +
            (unsigned long long)value_2.bits[i];
    result.bits[i] = (unsigned)accum;
    accum = accum >> 32;
  }
  return result;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  bool error = FALSE;
  big_decimal big_op1 = to_big_decimal(value_1);
  big_decimal big_op2 = to_big_decimal(value_2);
  big_decimal dest = {0, 0, 0, 0, 0, 0, 0, 0};
  unsigned sign1 = get_sign(value_1), sign2 = get_sign(value_2), sign_res = 0,
           exp = 0;
  set_sign(&value_1, 0);
  set_sign(&value_2, 0);
  if (big_op1.cexp > big_op2.cexp) {
    big_op2 = normalize(big_op2, big_op1.cexp - big_op2.cexp);
  }
  if (big_op2.cexp > big_op1.cexp) {
    big_op1 = normalize(big_op1, big_op2.cexp - big_op1.cexp);
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
      sign_res = 1;
    } else {
      dest = simple_sub(big_op1, big_op2);
    }
  } else if (sign1 && !sign2) {
    dest = simple_add(big_op1, big_op2);
    sign_res = 1;
  } else if (!sign1 && sign2) {
    dest = simple_add(big_op1, big_op2);
    sign_res = 0;
  }
  *result = big_decimal_to_decimal(dest);
  set_sign(result, sign_res);
  set_exp(result, exp);
  return error;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  bool error = FALSE;
  big_decimal big_op1 = to_big_decimal(value_1);
  big_decimal big_op2 = to_big_decimal(value_2);
  big_decimal dest = {0, 0, 0, 0, 0, 0, 0, 0};
  unsigned sign1 = get_sign(value_1), sign2 = get_sign(value_2), sign_res = 0,
           exp = 0;
  if (big_op1.cexp > big_op2.cexp) {
    big_op2 = normalize(big_op2, big_op1.cexp - big_op2.cexp);
  }
  if (big_op2.cexp > big_op1.cexp) {
    big_op1 = normalize(big_op1, big_op2.cexp - big_op1.cexp);
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
      dest = simple_sub(big_op2, big_op1);
      sign_res = 1;
    }
  }

  *result = big_decimal_to_decimal(dest);
  set_sign(result, sign_res);
  set_exp(result, exp);
  return error;
}

int big_desimal_is_null(big_decimal value) {
  bool result = FALSE;
  int i = 0;
  for (int i = 0; i < 6; i++)
    if (value.bits[i]) result = TRUE;
  return result;
}

big_decimal big_decimal_mul(s21_decimal value_1, s21_decimal value_2) {
  big_decimal big_op1 = to_big_decimal(value_1);
  big_decimal big_op2 = to_big_decimal(value_2);
  big_decimal dst = {0, 0, 0, 0, 0, 0, 0, 0};
  unsigned exp = (unsigned)(get_cexp(value_1) + get_cexp(value_2));
  while (big_desimal_is_null(big_op2)) {
    if (get_bit(big_op2, 0)) {
      dst = simple_add(dst, big_op1);
    }
    big_op1 = shift_bit_left(big_op1);
    big_op2 = shift_bit_right(big_op2);
  }
  dst.cexp = exp;
  return dst;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  big_decimal res_big = big_decimal_mul(value_1, value_2);
  *result = big_decimal_to_decimal(res_big);
}

// ******** div!!!!

int greater_big_decimal(big_decimal src1, big_decimal src2) {
  bool greater = FALSE;
  for (int i = 5; i >= 0; i--) {
    if (src1.bits[i] > src2.bits[i]) {
      greater = TRUE;
      break;
    } else if (src1.bits[i] < src2.bits[i]) {
      break;
    }
  }
  return greater;
}

int equal_big_decimal(big_decimal src1, big_decimal src2) {
  bool equal = TRUE;
  for (int i = 0; i < 6 && equal; i++) {
    if (src1.bits[i] != src2.bits[i]) {
      equal = FALSE;
    }
  }
  return equal;
}

int greater_or_equal_big_decimal(big_decimal src1, big_decimal src2) {
  int greater_or_equal = FALSE;
  if (greater_big_decimal(src1, src2) || equal_big_decimal(src1, src2)) {
    greater_or_equal = TRUE;
  }
  return greater_or_equal;
}

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
