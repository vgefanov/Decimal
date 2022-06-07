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

int get_bit(big_decimal src, int i) {
  unsigned int bit = 1u << (i % 32);
  return !!(src.bits[i / 32] & bit);
}

void set_sign(s21_decimal *op, int sign) {
  // устанавливает знак
  if (sign == 0) {
    op->bits[3] <<= 1;
    op->bits[3] >>= 1;
  }
  if (sign == 1) {
    int mask = ~0;
    mask >>= 31;
    mask <<= 31;
    op->bits[3] = op->bits[3] | mask;
  }
}

void set_cexp(s21_decimal *op, int scale) {
  int sign = get_sign(*op);
  op->bits[3] = scale;
  op->bits[3] <<= 16;
  if (sign == 1) {
    set_sign(op, 1);
  }
}

void set_exp(s21_decimal *op, int value) {
  op->bits[3] &= SIGN;
  value <<= 16;
  op->bits[3] |= value;
}

void set_bit(unsigned int *source_number, int bit_position, int bit) {
  // устанавливает значение определенного бита
  unsigned int mask = 1;
  mask <<= bit_position;
  if (bit == 0) {
    mask = ~mask;
    *source_number &= mask;
  }
  if (bit == 1) {
    *source_number |= mask;
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

void set_bit_big_decimal(big_decimal *src, int i, int value) {
  unsigned int bit = 1u << (i % 32);
  if (value == 1) {
    src->bits[i / 32] |= bit;
  } else {
    src->bits[i / 32] &= ~bit;
  }
}

big_decimal simple_sub(big_decimal value_1, big_decimal value_2) {
  big_decimal result = {{0, 0, 0, 0, 0, 0}, value_1.cexp, 0};
  bool taken = FALSE;
  for (int i = 0; i < 192; i++) {
    int bit_value_1 = get_bit(value_1, i);
    int bit_value_2 = get_bit(value_2, i);
    if (bit_value_1 && bit_value_2) {
      if (taken) {
        set_bit_big_decimal(&result, i, 1);
      } else {
        set_bit_big_decimal(&result, i, 0);
      }
    } else if (bit_value_1 && !bit_value_2) {
      if (taken) {
        set_bit_big_decimal(&result, i, 0);
        taken = FALSE;
      } else {
        set_bit_big_decimal(&result, i, 1);
      }
    } else if (!bit_value_1 && bit_value_2) {
      if (taken) {
        set_bit_big_decimal(&result, i, 0);
        taken = TRUE;
      } else {
        set_bit_big_decimal(&result, i, 1);
        taken = TRUE;
      }
    } else if (!bit_value_1 && !bit_value_2) {
      if (taken) {
        set_bit_big_decimal(&result, i, 0);
        taken = TRUE;
      } else {
        set_bit_big_decimal(&result, i, 0);
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
  if (big_op1.cexp > big_op2.cexp) {
    big_op2 = normalize(big_op2, big_op1.cexp - big_op2.cexp);
    exp = big_op1.cexp;
  }
  if (big_op2.cexp > big_op1.cexp) {
    big_op1 = normalize(big_op1, big_op2.cexp - big_op1.cexp);
    exp = big_op2.cexp;
  }
  if (!sign1 && !sign2) {
    if (s21_is_less(value_1, value_2)) {
      dest = simple_sub(big_op2, big_op1);
      sign_res = 1;
    } else {
      dest = simple_sub(big_op1, big_op2);
    }
  } else if (sign1 && sign2) {
    dest = simple_add(big_op1, big_op2);
    sign_res = 1;
  } else if (sign1 && !sign2) {
    if (s21_is_less(value_1, value_2)) {
      dest = simple_sub(big_op2, big_op1);
    } else {
      dest = simple_sub(big_op1, big_op2);
      sign_res = 1;
    }
  } else if (!sign1 && sign2) {
    dest = simple_add(big_op1, big_op2);
    sign_res = 1;
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
      (compare_null(op1) == FALSE && compare_sign(op1, op2) == -1))
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

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int exit_status = 0;
  if (dst == NULL) {
    exit_status = 1;
  } else {
    int float_number_bits = (((*(int *)&src)));
    int float_number_sign = (int)((float_number_bits >> 31) & 1u);
    int exponent = 0;
    set_sign(dst, float_number_sign);
    for (int i = 0; i < 8; i++) {
      int bit = (int)((float_number_bits >> (30 - i)) & 1u);
      exponent = exponent << 1;
      set_bit((unsigned int *)&exponent, 0, bit);
    }
    exponent = exponent - 127;
    unsigned int int_part = 0;
    float scale_part = src;
    scale_part = scale_part - (float)(int)scale_part;
    if (exponent > 95) {
      exit_status = 1;
    } else {
      int degree = exponent;
      for (int i = 0; i < 24 && degree != -1; i++, degree--) {
        int bit = 1;
        if (i != 0) {
          bit = (int)((float_number_bits >> (23 - i)) & 1u);
        }
        if (degree > 0) {
          int tmp = 1;
          for (int j = 0; j < degree; j++) {
            tmp *= 2;
          }
          int_part += tmp * bit;
        } else if (degree == 0) {
          if (bit == 1) {
            int_part += 1;
          }
        }
      }
      scale_part *= 1000000;
      s21_decimal res = {{0, 0, 0, 0}};
      s21_decimal tmp = {{0, 0, 0, 0}};
      tmp.bits[0] = (unsigned int)scale_part;
      dst->bits[0] = int_part;
      for (int m = 0; m < 6; m++) {
        big_decimal big_dst = to_big_decimal(*dst);
        scale(big_dst);
      }
      s21_add(tmp, *dst, &res);
      *dst = res;
      set_cexp(dst, 6);
    }
  }
  return exit_status;
}

// // Возвращает целые цифры указанного Decimal числа; любые дробные цифры
// // отбрасываются, включая конечные нули
// int s21_truncate(s21_decimal value, s21_decimal *result) {
//   int value_cexp = get_cexp(value);
//   int value_sign = get_sign(value);
//   for (int i = 0; i < value; i++) {

//   }
//   }

// Возвращает результат умножения указанного Decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result) { return 0; }

void print_decimal(s21_decimal op) {
  printf("[%s] %x %x %x (%x)\n", op.bits[3], op.bits[2], op.bits[1],
         op.bits[0]);
}

// void main() {
//   float x = 123.456;
//   s21_decimal y;
//   s21_from_float_to_decimal(x, y);
//   print_decimal(s21_decimal y);
//   //   s21_decimal test = {3, 0, 0, 0};
//   //   s21_decimal test2 = {3, 0, 0, 0};
//   // printf("test=[%d]\n", s21_is_not_equal(test, test2));
//   //   // printf("test=[%d]\n", compare_null(test));
//   //   // printf("test=[%d]\n", compare_sign(test, test2));
//   //   // printf("test_sign=[%d]\n", compare_sign(test, test2));
//   //   // printf("test=[%d]\n", compare_digit(test, test2));
//   //   // print_big_decimal(to_big_decimal(test));
//   //   // print_big_decimal(to_big_decimal(test2));

//   //   //   s21_decimal test2 = {0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f, 0x80100000};
//   //   //   print_big_decimal(to_big_decimal(test2));

//   //   //   // 4 fafa fafa fafa fafa faf6
//   //   //   print_big_decimal(scale(to_big_decimal(test2)));

//   //   //   // 23 86f2 6fc1 0000
//   //   //   print_big_decimal(normalize(to_big_decimal(test), 0x10));
//   //   //   s21_decimal test3 = {0x6fc10000, 0x002386f2, 0, 0x80200000};
//   //   //   printf("test3=[%d]", s21_is_equal(test, test3));

//   //   //   s21_decimal test4 = {0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f, 0x80100000};
//   //   //   print_big_decimal(to_big_decimal(test2));
// }
