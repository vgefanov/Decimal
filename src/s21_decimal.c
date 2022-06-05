#include "s21_decimal.h"

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
  return (op.bits[3] & CEXP) >> 16;
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

// Операторы сравнения

// Равно ==
int s21_is_equal(s21_decimal op1, s21_decimal op2) {
  bool result = TRUE;
  big_decimal big_op1 = to_big_decimal(op1);
  big_decimal big_op2 = to_big_decimal(op2);
  if (big_op1.sign != big_op2.sign) {
    result = FALSE;
  } else {
    if (big_op1.cexp > big_op2.cexp) {
      big_op2 = normalize(big_op2, big_op1.cexp - big_op2.cexp);
    }
    if (big_op2.cexp > big_op1.cexp) {
      big_op1 = normalize(big_op1, big_op2.cexp - big_op1.cexp);
    }
    for (int i = 0; i < 6; i++) {
      if (big_op1.bits[i] != big_op2.bits[i]) {
        result = FALSE;
        break;
      }
    }
    print_big_decimal(big_op1);
    print_big_decimal(big_op2);
  }
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
  s21_decimal_set_default(dst);
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
  set_sign(&dst, s21_get_sign(src));
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

void main() {
  s21_decimal test = {1, 0, 0, 0x80100000};
  printf("%d\n", get_sign(test));

  s21_decimal test2 = {0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f, 0x80100000};
  print_big_decimal(to_big_decimal(test2));
  // 4 fafa fafa fafa fafa faf6
  print_big_decimal(scale(to_big_decimal(test2)));

  // 23 86f2 6fc1 0000
  print_big_decimal(normalize(to_big_decimal(test), 0x10));
  s21_decimal test3 = {0x6fc10000, 0x002386f2, 0, 0x80200000};
  printf("%d", s21_is_equal(test, test3));
}
