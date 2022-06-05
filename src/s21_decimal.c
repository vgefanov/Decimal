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

// // Равно ==
// int s21_is_equal(s21_decimal op1, s21_decimal op2) {
//     bool result = TRUE;
//     big_decimal big_op1 = to_big_decimal(op1);
//     big_decimal big_op2 = to_big_decimal(op2);
//     if (big_op1.sign != big_op2.sign) {
//         result = FALSE;
//     } else {
//         if (big_op1.cexp > big_op2.cexp) {
//             big_op2 = normalize(big_op2, big_op1.cexp - big_op2.cexp);
//         }
//         if (big_op2.cexp > big_op1.cexp) {
//             big_op1 = normalize(big_op1, big_op2.cexp - big_op1.cexp);
//         }
//         for (int i = 0; i < 6; i++) {
//             if (big_op1.bits[i] != big_op2.bits[i]) {
//                 result = FALSE;
//                 break;
//             }
//         }
//         print_big_decimal(big_op1);
//         print_big_decimal(big_op2);
//     }
//     return result;
// }

// // Равно ==
// int s21_is_equal(s21_decimal op1, s21_decimal op2) {
//   bool result = FALSE;
//   if ((compare_null(op1) != 1) && (compare_null(op2) != 1) &&
//       (compare_sign(op1, op2) == 0) && (compare_digit(op1, op2) == 0))
//     result = TRUE;
//   return result;
// }

// сравнивает децимал с 0
bool compare_null(s21_decimal op) {
  big_decimal big_op = to_big_decimal(op);
  int result = 1;
  for (int i = 5; i >= 0; i--) {
    if (big_op.bits[i] != 0) {
      result = 0;
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
  if (big_op1.sign == 1 && big_op2.sign == 0)
    result = -1;
  else if (big_op2.sign == 1 && big_op1.sign == 0)
    result = 1;
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

// // Меньше <
// int s21_is_less(s21_decimal op1, s21_decimal op2) {
//   int result;
//   big_decimal big_op1 = to_big_decimal(op1);
//   big_decimal big_op2 = to_big_decimal(op2);
// }

// Возвращает результат умножения указанного Decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result) { return 0; }

void main() {
  s21_decimal test = {0, 0, 0, 0};
  s21_decimal test2 = {0, 0, 0, 0};
  printf("test=[%d]\n", s21_is_equal(test, test2));
  // printf("test=[%d]\n", compare_null(test));
  // printf("test=[%d]\n", compare_null(test2));
  // printf("test=[%d]\n", compare_sign(test, test2));
  // printf("test=[%d]\n", compare_digit(test, test2));
  // print_big_decimal(to_big_decimal(test));
  // print_big_decimal(to_big_decimal(test2));

  //   s21_decimal test2 = {0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f, 0x80100000};
  //   print_big_decimal(to_big_decimal(test2));

  //   // 4 fafa fafa fafa fafa faf6
  //   print_big_decimal(scale(to_big_decimal(test2)));

  //   // 23 86f2 6fc1 0000
  //   print_big_decimal(normalize(to_big_decimal(test), 0x10));
  //   s21_decimal test3 = {0x6fc10000, 0x002386f2, 0, 0x80200000};
  //   printf("test3=[%d]", s21_is_equal(test, test3));

  //   s21_decimal test4 = {0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f, 0x80100000};
  //   print_big_decimal(to_big_decimal(test2));
}
