#include "s21_decimal.h"

#include <check.h>
#include <float.h>
#include <limits.h>
#include <math.h>

s21_decimal dec_result;
s21_decimal transfer;
s21_decimal number_1;
s21_decimal number_2;

// int int_result = 0;
int int_dst = 0;
float flt_dst = 0;

// ARITHMETIC OPERATORS

START_TEST(int_add) {
  // INT_ADD

  s21_from_int_to_decimal(21, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  dec_result = s21_add(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 21 + 22);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(22, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  dec_result = s21_add(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 22 + 22);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(23, &number_1);
  s21_from_int_to_decimal(21, &number_2);
  dec_result = s21_add(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 23 + 21);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(23, &number_1);
  s21_from_int_to_decimal(21, &number_2);
  dec_result = s21_add(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 23 + 21);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  // NEGATIVE

  s21_from_int_to_decimal(-215, &number_1);
  s21_from_int_to_decimal(222, &number_2);
  dec_result = s21_add(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -215 + 222);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(-2256, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  dec_result = s21_add(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -2256 + 22);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(-223, &number_1);
  s21_from_int_to_decimal(223, &number_2);
  dec_result = s21_add(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -223 + 223);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);
}
END_TEST

START_TEST(float_add) {
  // FLOAT_ADD

  s21_from_float_to_decimal(21.21f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  dec_result = s21_add(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq(flt_dst, 21.21f + 22.22f);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(22.22f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  dec_result = s21_add(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq(flt_dst, 22.22f + 22.22f);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(23.23f, &number_1);
  s21_from_float_to_decimal(21.21f, &number_2);
  dec_result = s21_add(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq(flt_dst, 23.23f + 21.21f);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  // NEGATIVE

  s21_from_float_to_decimal(-21.21f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  dec_result = s21_add(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, -21.21f + 22.22f, 0.000001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(-22.22f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  dec_result = s21_add(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq(flt_dst, -22.22f + 22.22f);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(-23.23f, &number_1);
  s21_from_float_to_decimal(21.21f, &number_2);
  dec_result = s21_add(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, -23.23f + 21.21f, 0.00001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  // 1e-15

  s21_from_float_to_decimal(0.000000000000001f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  dec_result = s21_add(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 22.22f, 0.0001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(0.000000000000001f, &number_1);
  s21_from_float_to_decimal(0.0000000000000001f, &number_2);
  dec_result = s21_add(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 0.000000000000001f + 0.0000000000000001f,
                         0.0001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(0.0000000000000001f, &number_1);
  s21_from_float_to_decimal(0.0000000000000015f, &number_2);
  dec_result = s21_add(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 0.0000000000000001f + 0.0000000000000015f,
                         0.000001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);
}
END_TEST

START_TEST(int_sub) {
  // INT_SUB

  s21_from_int_to_decimal(21, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  dec_result = s21_sub(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 21 - 22);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(22, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  dec_result = s21_sub(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 22 - 22);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(23, &number_1);
  s21_from_int_to_decimal(21, &number_2);
  dec_result = s21_sub(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 23 - 21);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  // NEGATIVE

  s21_from_int_to_decimal(-21, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  dec_result = s21_sub(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -21 - 22);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(-22, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  dec_result = s21_sub(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -22 - 22);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(-23, &number_1);
  s21_from_int_to_decimal(21, &number_2);
  dec_result = s21_sub(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -23 - 21);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);
}
END_TEST

START_TEST(float_sub) {
  // FLOAT_SUB

  s21_from_float_to_decimal(21.21f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  dec_result = s21_sub(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 21.21f - 22.22f, 0.000001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(22.22f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  dec_result = s21_sub(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq(flt_dst, 22.22f - 22.22f);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(23.23f, &number_1);
  s21_from_float_to_decimal(21.21f, &number_2);
  dec_result = s21_sub(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 23.23f - 21.21f, 0.000001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  // NEGATIVE

  s21_from_float_to_decimal(-21.21f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  dec_result = s21_sub(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq(flt_dst, -21.21f - 22.22f);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(-22.22f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  dec_result = s21_sub(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq(flt_dst, -22.22f - 22.22f);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(-23.23f, &number_1);
  s21_from_float_to_decimal(21.21f, &number_2);
  dec_result = s21_sub(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq(flt_dst, -23.23f - 21.21f);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  // 1e-15

  s21_from_float_to_decimal(22.22f, &number_1);
  s21_from_float_to_decimal(0.000000000000001f, &number_2);
  dec_result = s21_sub(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 22.22f - 0.000000000000001f, 0.0001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(0.000000000000001f, &number_1);
  s21_from_float_to_decimal(0.0000000000000001f, &number_2);
  dec_result = s21_sub(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 0.000000000000001f - 0.0000000000000001f,
                         0.0001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(0.0000000000000015f, &number_1);
  s21_from_float_to_decimal(0.0000000000000001f, &number_2);
  dec_result = s21_sub(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 0.0000000000000015f - 0.0000000000000001f,
                         0.001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);
}
END_TEST

START_TEST(int_mul) {
  // INT_MUL

  s21_from_int_to_decimal(21, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 21 * 22);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(22, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 22 * 22);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(23, &number_1);
  s21_from_int_to_decimal(21, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 23 * 21);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(1000, &number_1);
  s21_from_int_to_decimal(7, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 7000);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(INT_MAX, &number_1);
  s21_from_int_to_decimal(1, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 2147483647);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(INT_MAX, &number_1);
  s21_from_int_to_decimal(0, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 0);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  // NEGATIVE

  s21_from_int_to_decimal(-21, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -21 * 22);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(-22, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -22 * 22);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(-23, &number_1);
  s21_from_int_to_decimal(21, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -23 * 21);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(-1000, &number_1);
  s21_from_int_to_decimal(7, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -7000);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(INT_MAX, &number_1);
  s21_from_int_to_decimal(-1, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -2147483647);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);
}
END_TEST

START_TEST(float_mul) {
  // FLOAT_MUL

  s21_from_float_to_decimal(21.21f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 21.21f * 22.22f, 0.0001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(22.22f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 22.22f * 22.22f, 0.0001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(23.23f, &number_1);
  s21_from_float_to_decimal(21.21f, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 23.23f * 21.21f, 0.0001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  // NEGATIVE

  s21_from_float_to_decimal(-21.21f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, -21.21f * 22.22f, 0.0001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(-22.22f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, -22.22f * 22.22f, 0.0001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(-23.23f, &number_1);
  s21_from_float_to_decimal(21.21f, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, -23.23f * 21.21f, 0.0001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  // 1e-15

  s21_from_float_to_decimal(22.22f, &number_1);
  s21_from_float_to_decimal(0.000000000000001f, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 22.22f * 0.000000000000001f, 0.0001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(0.000000000000001f, &number_1);
  s21_from_float_to_decimal(0.0000000000000001f, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq(flt_dst, 0.0f);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(0.0000000000000015f, &number_1);
  s21_from_float_to_decimal(0.0000000000000001f, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 0.0000000000000015f * 0.0000000000000001f,
                         0.0001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(15.0f, &number_1);
  s21_from_float_to_decimal(0.0000000000000001f, &number_2);
  dec_result = s21_mul(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 15.0f * 0.0000000000000001f, 0.0001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);
}
END_TEST

START_TEST(int_div) {
  // INT_DIV

  s21_from_int_to_decimal(22, &number_1);
  s21_from_int_to_decimal(11, &number_2);
  dec_result = s21_div(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 22 / 11);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(25, &number_1);
  s21_from_int_to_decimal(5, &number_2);
  dec_result = s21_div(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 25 / 5);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(2147483647, &number_1);
  s21_from_int_to_decimal(1, &number_2);
  dec_result = s21_div(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 2147483647 / 1);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  // NEGATIVE

  s21_from_int_to_decimal(-22, &number_1);
  s21_from_int_to_decimal(11, &number_2);
  dec_result = s21_div(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -22 / 11);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(25, &number_1);
  s21_from_int_to_decimal(-5, &number_2);
  dec_result = s21_div(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 25 / -5);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(2147483647, &number_1);
  s21_from_int_to_decimal(-1, &number_2);
  dec_result = s21_div(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 2147483647 / -1);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);
}
END_TEST

START_TEST(int_mul_and_div) {
  // INT_MUL_AND_DIV

  s21_decimal dec_mid_result;

  s21_from_int_to_decimal(7, &number_1);
  s21_from_int_to_decimal(2, &number_2);

  dec_result = number_1;

  for (int i = 0; i < 10; i++) {
    dec_result = s21_mul(dec_result, number_2);
  }

  for (int i = 0; i < 10; i++) {
    dec_result = s21_div(dec_result, number_2);
  }
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 7);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(2147483646, &number_1);
  s21_from_int_to_decimal(2, &number_2);

  dec_result = number_1;

  for (int i = 0; i < 50; i++) {
    dec_result = s21_div(number_1, number_2);
  }
  dec_mid_result = dec_result;

  for (int i = 0; i < 50; i++) {
    dec_result = s21_mul(dec_mid_result, number_2);
  }
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 2147483646);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  // NEGATIVE

  s21_from_int_to_decimal(7, &number_1);
  s21_from_int_to_decimal(-2, &number_2);

  dec_result = number_1;
  for (int i = 0; i < 50; i++) {
    dec_result = s21_mul(dec_result, number_2);
  }

  for (int i = 0; i < 50; i++) {
    dec_result = s21_div(dec_result, number_2);
  }
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 7);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(-2, &number_1);
  s21_from_int_to_decimal(15, &number_2);

  dec_result = number_1;
  for (int i = 0; i < 20; i++) {
    dec_result = s21_mul(dec_result, number_2);
  }

  for (int i = 0; i < 20; i++) {
    dec_result = s21_div(dec_result, number_2);
  }

  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -2);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(INT_MIN, &number_1);
  s21_from_int_to_decimal(-2, &number_2);
  dec_result = number_1;

  for (int i = 0; i < 50; i++) {
    dec_result = s21_mul(dec_result, number_2);
  }

  for (int i = 0; i < 50; i++) {
    dec_result = s21_div(dec_result, number_2);
  }
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, INT_MIN);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(2147483646, &number_1);
  s21_from_int_to_decimal(-2, &number_2);
  dec_result = number_1;

  for (int i = 0; i < 3; i++) {
    dec_result = s21_mul(dec_result, number_2);
  }

  for (int i = 0; i < 3; i++) {
    dec_result = s21_div(dec_result, number_2);
  }
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 2147483646);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  // ______________________________________________________
}
END_TEST

START_TEST(float_div) {
  //// FLOAT_DIV

  s21_from_float_to_decimal(21.21f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  dec_result = s21_div(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 21.21f / 22.22f, 0.0001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(22.22f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  dec_result = s21_div(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq(flt_dst, 22.22f / 22.22f);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  // NEGATIVE

  s21_from_float_to_decimal(-21.21f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  dec_result = s21_div(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, -21.21f / 22.22f, 0.0001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(-22.22f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  dec_result = s21_div(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, -22.22f / 22.22f, 0.0001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  // // 1e-15

  s21_from_float_to_decimal(0.000000000000001f, &number_1);
  s21_from_float_to_decimal(0.0000000000000001f, &number_2);
  dec_result = s21_div(number_1, number_2);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq(flt_dst, 0.000000000000001f / 0.0000000000000001f);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);
}
END_TEST

START_TEST(mod) {
  // INT_MOD

  s21_from_int_to_decimal(21, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  dec_result = s21_mod(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 21 % 22);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(22, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  dec_result = s21_mod(number_1, number_2);
  ck_assert_int_eq((int)dec_result.bits[0], 22 % 22);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(23, &number_1);
  s21_from_int_to_decimal(21, &number_2);
  dec_result = s21_mod(number_1, number_2);
  ck_assert_int_eq((int)dec_result.bits[0], 23 % 21);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(1000, &number_1);
  s21_from_int_to_decimal(7, &number_2);
  dec_result = s21_mod(number_1, number_2);
  ck_assert_int_eq((int)dec_result.bits[0], 6);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_int_to_decimal(-1000, &number_1);
  s21_from_int_to_decimal(7, &number_2);
  dec_result = s21_mod(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -6);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);

  s21_from_float_to_decimal(123.0000000f, &number_1);
  s21_from_float_to_decimal(0.0012300f, &number_2);
  dec_result = s21_mod(number_1, number_2);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 0);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
  ck_assert_int_eq(dec_result.value_type, 0);
}
END_TEST

// COMPARISON OPERATORS

START_TEST(int_is_less) {
  // INT_IS_LESS

  s21_from_int_to_decimal(21, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  ck_assert_int_eq(s21_is_less(number_1, number_2), !(21 < 22));

  s21_from_int_to_decimal(22, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  ck_assert_int_eq(s21_is_less(number_1, number_2), !(22 < 22));

  s21_from_int_to_decimal(23, &number_1);
  s21_from_int_to_decimal(21, &number_2);
  ck_assert_int_eq(s21_is_less(number_1, number_2), !(23 < 21));

  s21_from_int_to_decimal(INT_MAX, &number_1);
  s21_from_int_to_decimal(INT_MAX - 500, &number_2);
  ck_assert_int_eq(s21_is_less(number_1, number_2), !(INT_MAX < INT_MAX - 500));

  s21_from_int_to_decimal(INT_MAX, &number_1);
  s21_from_int_to_decimal(INT_MIN, &number_2);
  ck_assert_int_eq(s21_is_less(number_1, number_2), !(INT_MAX < INT_MIN));

  s21_from_int_to_decimal(-21, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  ck_assert_int_eq(s21_is_less(number_1, number_2), !(-21 < 22));

  s21_from_int_to_decimal(-22, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  ck_assert_int_eq(s21_is_less(number_1, number_2), !(-22 < 22));

  s21_from_int_to_decimal(-23, &number_1);
  s21_from_int_to_decimal(21, &number_2);
  ck_assert_int_eq(s21_is_less(number_1, number_2), !(-23 < 21));

  s21_decimal dec_near_zero = {{INT_MIN, INT_MIN, INT_MIN, 0}, 0};
  set_scale(&dec_near_zero, 28);
  number_2 = DEC_MAX_VALUE;
  ck_assert_int_eq(s21_is_less(dec_near_zero, number_2), 0);
}
END_TEST

START_TEST(float_is_less) {
  // FLT_IS_LESS

  s21_from_float_to_decimal(21.21f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  ck_assert_int_eq(s21_is_less(number_1, number_2), !(21.21f < 22.22f));

  s21_from_float_to_decimal(22.22f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  ck_assert_int_eq(s21_is_less(number_1, number_2), !(22.22f < 22.22f));

  s21_from_float_to_decimal(23.23f, &number_1);
  s21_from_float_to_decimal(21.21f, &number_2);
  ck_assert_int_eq(s21_is_less(number_1, number_2), !(23.23f < 21.21f));

  s21_from_float_to_decimal(FLT_MAX, &number_1);
  s21_from_float_to_decimal(FLT_MAX - 21.21f, &number_2);
  ck_assert_int_eq(s21_is_less(number_1, number_2),
                   !(FLT_MAX < FLT_MAX - 21.21f));

  s21_from_float_to_decimal(FLT_MIN, &number_1);
  s21_from_float_to_decimal(FLT_MIN + 21.21f, &number_2);
  ck_assert_int_eq(s21_is_less(number_1, number_2),
                   !(FLT_MIN < FLT_MIN + 21.21f));
}
END_TEST

START_TEST(int_is_less_or_equal) {
  // INT_IS_LESS_OR_EQUAL

  s21_from_int_to_decimal(21, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  ck_assert_int_eq(s21_is_less_or_equal(number_1, number_2), !(21 <= 22));

  s21_from_int_to_decimal(22, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  ck_assert_int_eq(s21_is_less_or_equal(number_1, number_2), !(22 <= 22));

  s21_from_int_to_decimal(23, &number_1);
  s21_from_int_to_decimal(21, &number_2);
  ck_assert_int_eq(s21_is_less_or_equal(number_1, number_2), !(23 <= 21));

  s21_from_int_to_decimal(23, &number_1);
  s21_from_int_to_decimal(21, &number_2);
  ck_assert_int_eq(s21_is_less_or_equal(number_1, number_2), !(23 <= 21));

  s21_from_int_to_decimal(INT_MAX, &number_1);
  s21_from_int_to_decimal(INT_MAX, &number_2);
  ck_assert_int_eq(s21_is_less_or_equal(number_1, number_2),
                   !(INT_MAX <= INT_MAX));

  s21_from_int_to_decimal(INT_MAX, &number_1);
  s21_from_int_to_decimal(INT_MAX - 555, &number_2);
  ck_assert_int_eq(s21_is_less_or_equal(number_1, number_2),
                   !(INT_MAX <= INT_MAX - 555));

  s21_from_int_to_decimal(INT_MAX, &number_1);
  s21_from_int_to_decimal(INT_MIN + 555, &number_2);
  ck_assert_int_eq(s21_is_less_or_equal(number_1, number_2),
                   !(INT_MAX <= INT_MIN + 555));
}
END_TEST

START_TEST(float_is_less_or_equal) {
  // FLOAT_IS_LESS_OR_EQUAL

  s21_from_float_to_decimal(21.21f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  ck_assert_int_eq(s21_is_less_or_equal(number_1, number_2),
                   !(21.21f <= 22.22f));

  s21_from_float_to_decimal(22.22f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  ck_assert_int_eq(s21_is_less_or_equal(number_1, number_2),
                   !(22.22f <= 22.22f));

  s21_from_float_to_decimal(23.23f, &number_1);
  s21_from_float_to_decimal(21.21f, &number_2);
  ck_assert_int_eq(s21_is_less_or_equal(number_1, number_2),
                   !(23.23f <= 21.21f));

  // s21_from_float_to_decimal(FLT_MAX, &number_1);
  // s21_from_float_to_decimal(FLT_MAX - 21.21f, &number_2);
  // ck_assert_int_eq(s21_is_less_or_equal(number_1, number_2),
  //                  !(FLT_MAX <= FLT_MAX - 21.21f));

  s21_from_float_to_decimal(FLT_MIN, &number_1);
  s21_from_float_to_decimal(FLT_MIN + 21.21f, &number_2);
  ck_assert_int_eq(s21_is_less_or_equal(number_1, number_2),
                   !(FLT_MIN <= FLT_MIN + 21.21f));

  s21_from_float_to_decimal(FLT_MAX, &number_1);
  s21_from_float_to_decimal(FLT_MAX, &number_2);
  ck_assert_int_eq(s21_is_less_or_equal(number_1, number_2),
                   !(FLT_MAX <= FLT_MAX));
}
END_TEST

START_TEST(int_is_greater) {
  // INT_IS_GREATER

  s21_from_int_to_decimal(21, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  ck_assert_int_eq(s21_is_greater(number_1, number_2), !(21 > 22));

  s21_from_int_to_decimal(22, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  ck_assert_int_eq(s21_is_greater(number_1, number_2), !(22 > 22));

  s21_from_int_to_decimal(23, &number_1);
  s21_from_int_to_decimal(21, &number_2);
  ck_assert_int_eq(s21_is_greater(number_1, number_2), !(23 > 21));

  s21_from_int_to_decimal(INT_MAX, &number_1);
  s21_from_int_to_decimal(INT_MAX, &number_2);
  ck_assert_int_eq(s21_is_greater(number_1, number_2), !(INT_MAX > INT_MAX));

  s21_from_int_to_decimal(INT_MAX, &number_1);
  s21_from_int_to_decimal(INT_MAX - 200, &number_2);
  ck_assert_int_eq(s21_is_greater(number_1, number_2),
                   !(INT_MAX > INT_MAX - 200));

  s21_from_int_to_decimal(INT_MAX - 200, &number_1);
  s21_from_int_to_decimal(INT_MAX, &number_2);
  ck_assert_int_eq(s21_is_greater(number_1, number_2),
                   !(INT_MAX - 200 > INT_MAX));

  s21_from_int_to_decimal(INT_MIN + 200, &number_1);
  s21_from_int_to_decimal(INT_MAX, &number_2);
  ck_assert_int_eq(s21_is_greater(number_1, number_2),
                   !(INT_MIN + 200 > INT_MAX));

  s21_decimal dec_near_zero = {{INT_MIN, INT_MIN, INT_MIN, 0}, 0};
  set_scale(&dec_near_zero, 28);
  number_2 = DEC_MAX_VALUE;
  ck_assert_int_eq(s21_is_greater(number_2, dec_near_zero), 0);
}
END_TEST

START_TEST(float_is_greater) {
  // FLOAT_IS_GREATER

  s21_from_float_to_decimal(21.21f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  ck_assert_int_eq(s21_is_greater(number_1, number_2), !(21.21f > 22.22f));

  s21_from_float_to_decimal(22.22f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  ck_assert_int_eq(s21_is_greater(number_1, number_2), !(22.22f > 22.22f));

  s21_from_float_to_decimal(23.23f, &number_1);
  s21_from_float_to_decimal(21.21f, &number_2);
  ck_assert_int_eq(s21_is_greater(number_1, number_2), !(23.23f > 21.21f));

  // s21_from_float_to_decimal(FLT_MAX - 21.21f, &number_1);
  // s21_from_float_to_decimal(FLT_MAX, &number_2);
  // ck_assert_int_eq(s21_is_greater(number_1, number_2),
  //                  !(FLT_MAX - 21.21f > FLT_MAX));

  // s21_from_float_to_decimal(FLT_MAX, &number_1);
  // s21_from_float_to_decimal(FLT_MAX, &number_2);
  // ck_assert_int_eq(s21_is_greater(number_1, number_2), !(FLT_MAX > FLT_MAX));

  // s21_from_float_to_decimal(FLT_MAX, &number_1);
  // s21_from_float_to_decimal(FLT_MAX - 21.21f, &number_2);
  // ck_assert_int_eq(s21_is_greater(number_1, number_2),
  //                  !(FLT_MAX > FLT_MAX - 21.21f));

  s21_from_float_to_decimal(FLT_MIN + 1, &number_1);
  s21_from_float_to_decimal(FLT_MIN + 1, &number_2);
  ck_assert_int_eq(s21_is_greater(number_1, number_2),
                   !(FLT_MIN + 1 > FLT_MIN + 1));
}
END_TEST

START_TEST(int_is_greater_or_equal) {
  // INT_IS_GREATER_OR_EQUAL

  s21_from_int_to_decimal(21, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  ck_assert_int_eq(s21_is_greater_or_equal(number_1, number_2), !(21 >= 22));

  s21_from_int_to_decimal(22, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  ck_assert_int_eq(s21_is_greater_or_equal(number_1, number_2), !(22 >= 22));

  s21_from_int_to_decimal(23, &number_1);
  s21_from_int_to_decimal(21, &number_2);
  ck_assert_int_eq(s21_is_greater_or_equal(number_1, number_2), !(23 >= 21));

  s21_from_int_to_decimal(INT_MAX - 1, &number_1);
  s21_from_int_to_decimal(INT_MAX, &number_2);
  ck_assert_int_eq(s21_is_greater_or_equal(number_1, number_2),
                   !(INT_MAX - 1 >= INT_MAX));

  s21_from_int_to_decimal(INT_MAX - 1, &number_1);
  s21_from_int_to_decimal(INT_MAX - 1, &number_2);
  ck_assert_int_eq(s21_is_greater_or_equal(number_1, number_2),
                   !(INT_MAX - 1 >= INT_MAX - 1));

  s21_from_int_to_decimal(INT_MAX, &number_1);
  s21_from_int_to_decimal(INT_MAX - 21, &number_2);
  ck_assert_int_eq(s21_is_greater_or_equal(number_1, number_2),
                   !(INT_MAX >= INT_MAX - 21));

  s21_from_int_to_decimal(INT_MAX, &number_1);
  s21_from_int_to_decimal(INT_MIN + 21, &number_2);
  ck_assert_int_eq(s21_is_greater_or_equal(number_1, number_2),
                   !(INT_MAX >= INT_MIN + 21));
}
END_TEST

START_TEST(float_is_greater_or_equal) {
  // FLOAT_IS_GREATER_OR_EQAL

  s21_from_float_to_decimal(21.21f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  ck_assert_int_eq(s21_is_greater_or_equal(number_1, number_2),
                   !(21.21f >= 22.22f));

  s21_from_float_to_decimal(22.22f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  ck_assert_int_eq(s21_is_greater_or_equal(number_1, number_2),
                   !(22.22f >= 22.22f));

  s21_from_float_to_decimal(23.23f, &number_1);
  s21_from_float_to_decimal(21.21f, &number_2);
  ck_assert_int_eq(s21_is_greater_or_equal(number_1, number_2),
                   !(23.23f >= 21.21f));

  s21_from_float_to_decimal(FLT_MAX, &number_1);
  s21_from_float_to_decimal(FLT_MAX - 21.21f, &number_2);
  ck_assert_int_eq(s21_is_greater_or_equal(number_1, number_2),
                   !(FLT_MAX >= FLT_MAX - 21.21f));

  s21_from_float_to_decimal(FLT_MIN, &number_1);
  s21_from_float_to_decimal(FLT_MIN + 21.21f, &number_2);
  ck_assert_int_eq(s21_is_greater_or_equal(number_1, number_2),
                   !(FLT_MIN >= FLT_MIN + 21.21f));

  // s21_from_float_to_decimal(FLT_MAX, &number_1);
  // s21_from_float_to_decimal(FLT_MAX, &number_2);
  // ck_assert_int_eq(s21_is_greater_or_equal(number_1, number_2),
  //                  !(FLT_MAX >= FLT_MAX));
}
END_TEST

START_TEST(int_is_equal) {
  // INT_IS_EQUAL

  s21_from_int_to_decimal(21, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  ck_assert_int_eq(s21_is_equal(number_1, number_2), 21 != 22);

  s21_from_int_to_decimal(22, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  ck_assert_int_eq(s21_is_equal(number_1, number_2), 22 != 22);

  s21_from_int_to_decimal(23, &number_1);
  s21_from_int_to_decimal(21, &number_2);
  ck_assert_int_eq(s21_is_equal(number_1, number_2), 23 != 21);

  s21_from_int_to_decimal(INT_MAX - 21, &number_1);
  s21_from_int_to_decimal(INT_MAX, &number_2);
  ck_assert_int_eq(s21_is_equal(number_1, number_2), INT_MAX - 21 != INT_MAX);

  s21_from_int_to_decimal(INT_MAX - 22, &number_1);
  s21_from_int_to_decimal(INT_MAX - 22, &number_2);
  ck_assert_int_eq(s21_is_equal(number_1, number_2),
                   INT_MAX - 22 != INT_MAX - 22);

  s21_from_int_to_decimal(INT_MAX - 21, &number_1);
  s21_from_int_to_decimal(INT_MAX - 23, &number_2);
  ck_assert_int_eq(s21_is_equal(number_1, number_2),
                   INT_MAX - 21 != INT_MAX - 23);
}
END_TEST

START_TEST(float_is_equal) {
  // FLOAT_IS_EQUAL

  s21_from_float_to_decimal(21.21f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  ck_assert_int_eq(s21_is_equal(number_1, number_2), 21.21f != 22.22f);

  s21_from_float_to_decimal(22.22f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  ck_assert_int_eq(s21_is_equal(number_1, number_2), 22.22f != 22.22f);

  s21_from_float_to_decimal(23.23f, &number_1);
  s21_from_float_to_decimal(21.21f, &number_2);
  ck_assert_int_eq(s21_is_equal(number_1, number_2), 23.23f != 21.21f);

  // s21_from_float_to_decimal(FLT_MAX - 21.21f, &number_1);
  // s21_from_float_to_decimal(FLT_MAX - 22.22f, &number_2);
  // ck_assert_int_eq(s21_is_equal(number_1, number_2),
  //                  FLT_MAX - 21.21f != FLT_MAX - 22.22f);

  // s21_from_float_to_decimal(FLT_MAX, &number_1);
  // s21_from_float_to_decimal(FLT_MAX, &number_2);
  // ck_assert_int_eq(s21_is_equal(number_1, number_2), FLT_MAX != FLT_MAX);

  // s21_from_float_to_decimal(FLT_MAX - 23.23f, &number_1);
  // s21_from_float_to_decimal(FLT_MAX - 21.21f, &number_2);
  // ck_assert_int_eq(s21_is_equal(number_1, number_2),
  //                  FLT_MAX - 23.23f != FLT_MAX - 21.21f);

  s21_from_float_to_decimal(FLT_MAX, &number_1);
  s21_from_float_to_decimal(FLT_MIN + 21.21f, &number_2);
  ck_assert_int_eq(s21_is_equal(number_1, number_2),
                   FLT_MAX != FLT_MIN + 21.21f);
}
END_TEST

START_TEST(int_is_not_equal) {
  // INT_IS_NOT_EQUAL
  s21_decimal inf1;
  s21_decimal inf2;
  inf1.value_type = s21_INFINITY;
  inf2.value_type = s21_NEGATIVE_INFINITY;
  ck_assert_int_eq(s21_is_not_equal(inf1, inf2), 0);

  s21_from_int_to_decimal(21, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  ck_assert_int_eq(s21_is_not_equal(number_1, number_2), 21 == 22);

  s21_from_int_to_decimal(22, &number_1);
  s21_from_int_to_decimal(22, &number_2);
  ck_assert_int_eq(s21_is_not_equal(number_1, number_2), 22 == 22);

  s21_from_int_to_decimal(23, &number_1);
  s21_from_int_to_decimal(21, &number_2);
  ck_assert_int_eq(s21_is_not_equal(number_1, number_2), 23 == 21);

  s21_from_int_to_decimal(INT_MAX - 21, &number_1);
  s21_from_int_to_decimal(INT_MAX, &number_2);
  ck_assert_int_eq(s21_is_not_equal(number_1, number_2),
                   INT_MAX - 21 == INT_MAX);

  s21_from_int_to_decimal(INT_MAX - 22, &number_1);
  s21_from_int_to_decimal(INT_MAX - 22, &number_2);
  ck_assert_int_eq(s21_is_not_equal(number_1, number_2),
                   INT_MAX - 22 == INT_MAX - 22);

  s21_from_int_to_decimal(INT_MAX - 21, &number_1);
  s21_from_int_to_decimal(INT_MAX - 23, &number_2);
  ck_assert_int_eq(s21_is_not_equal(number_1, number_2),
                   INT_MAX - 21 == INT_MAX - 23);
}
END_TEST

START_TEST(float_is_not_equal) {
  // FLOAT_IS_EQUAL

  s21_from_float_to_decimal(21.21f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  ck_assert_int_eq(s21_is_not_equal(number_1, number_2), 21.21f == 22.22f);

  s21_from_float_to_decimal(22.22f, &number_1);
  s21_from_float_to_decimal(22.22f, &number_2);
  ck_assert_int_eq(s21_is_not_equal(number_1, number_2), 22.22f == 22.22f);

  s21_from_float_to_decimal(23.23f, &number_1);
  s21_from_float_to_decimal(21.21f, &number_2);
  ck_assert_int_eq(s21_is_not_equal(number_1, number_2), 23.23f == 21.21f);
}
END_TEST

// CONVERTORS AND PARSERS

START_TEST(from_int_to_decimal_and_back) {
  s21_from_int_to_decimal(15, &transfer);
  s21_from_decimal_to_int(transfer, &int_dst);
  ck_assert_int_eq(int_dst, 15);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_int_to_decimal(-15, &transfer);
  s21_from_decimal_to_int(transfer, &int_dst);
  ck_assert_int_eq(int_dst, -15);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_int_to_decimal(0, &transfer);
  s21_from_decimal_to_int(transfer, &int_dst);
  ck_assert_int_eq(int_dst, 0);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_int_to_decimal(INT_MIN, &transfer);
  s21_from_decimal_to_int(transfer, &int_dst);
  ck_assert_int_eq(int_dst, INT_MIN);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_int_to_decimal(INT_MAX, &transfer);
  s21_from_decimal_to_int(transfer, &int_dst);
  ck_assert_int_eq(int_dst, INT_MAX);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);
}
END_TEST

START_TEST(from_float_to_decimal_and_back) {
  s21_from_float_to_decimal(15.15f, &transfer);
  s21_from_decimal_to_float(transfer, &flt_dst);
  ck_assert_float_eq(flt_dst, 15.15);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(-15.15f, &transfer);
  s21_from_decimal_to_float(transfer, &flt_dst);
  ck_assert_float_eq(flt_dst, -15.15);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(0.0f, &transfer);
  s21_from_decimal_to_float(transfer, &flt_dst);
  ck_assert_float_eq(flt_dst, 0.0);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(1e15f, &transfer);
  s21_from_decimal_to_float(transfer, &flt_dst);
  ck_assert_float_eq(flt_dst, 1e15f);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_decimal_to_float(DEC_MAX_BIT1, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 4.29497e+09, 10000);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_decimal new_dec = {{7, 0, 0, 0}, 0};
  set_scale(&new_dec, 28);
  s21_from_decimal_to_float(new_dec, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 7e-28, 0.000001);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);
}
END_TEST

// ANOTHER FUNCTIONS

START_TEST(floor_21) {
  s21_from_int_to_decimal(0, &transfer);
  dec_result = s21_floor(transfer);
  ck_assert_int_eq((int)dec_result.bits[0], 0);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(0.0f, &transfer);
  dec_result = s21_floor(transfer);
  ck_assert_int_eq((int)dec_result.bits[0], 0);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(123.456f, &transfer);
  dec_result = s21_floor(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 123);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(-123.456f, &transfer);
  dec_result = s21_floor(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -124);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(-123.000f, &transfer);
  dec_result = s21_floor(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -123);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);
}
END_TEST

START_TEST(round_21) {
  // Value_type в пути становится бесконечностью

  s21_from_float_to_decimal(123.0000000f, &transfer);
  dec_result = s21_round(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 123);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(123.456f, &transfer);
  dec_result = s21_round(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 123);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(123.500f, &transfer);
  dec_result = s21_round(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 124);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(123.656f, &transfer);
  dec_result = s21_round(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 124);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(-123.0000000f, &transfer);
  dec_result = s21_round(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -123);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(-123.456f, &transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -123);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(-123.500f, &transfer);
  dec_result = s21_round(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -124);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(-123.656f, &transfer);
  dec_result = s21_round(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -124);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);
}
END_TEST

START_TEST(truncate) {
  s21_from_float_to_decimal(123.456f, &transfer);
  dec_result = s21_truncate(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 123);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(123.656f, &transfer);
  dec_result = s21_truncate(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 123);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(-123.456f, &transfer);
  dec_result = s21_truncate(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -123);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(-123.656f, &transfer);
  dec_result = s21_truncate(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -123);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(-123.0000000f, &transfer);
  dec_result = s21_truncate(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -123);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);
}
END_TEST

START_TEST(negate) {
  s21_from_int_to_decimal(-15, &transfer);
  dec_result = s21_negate(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 15);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_int_to_decimal(0, &transfer);
  dec_result = s21_negate(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, 0);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_int_to_decimal(15, &transfer);
  dec_result = s21_negate(transfer);
  s21_from_decimal_to_int(dec_result, &int_dst);
  ck_assert_int_eq(int_dst, -15);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(-123.000f, &transfer);
  dec_result = s21_negate(transfer);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq(flt_dst, 123.000);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(123.4563f, &transfer);
  dec_result = s21_negate(transfer);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, -123.4563f, 0.00001f);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(123.4565f, &transfer);
  dec_result = s21_negate(transfer);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, -123.4565f, 0.0001f);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(123.656f, &transfer);
  dec_result = s21_negate(transfer);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, -123.656f, 0.00001f);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(-123.456f, &transfer);
  dec_result = s21_negate(transfer);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 123.456f, 0.0001f);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(-123.656f, &transfer);
  dec_result = s21_negate(transfer);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 123.656f, 0.0001f);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);

  s21_from_float_to_decimal(-123.0000000f, &transfer);
  dec_result = s21_negate(transfer);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq(flt_dst, 123.0000000f);
  ck_assert_int_eq(getbit(transfer, 96), 0);
  ck_assert_int_eq(transfer.value_type, 0);
}
END_TEST

START_TEST(extremum) {
  dec_result = s21_add(DEC_MAX_VALUE, DEC_1);
  int value_type = dec_result.value_type;
  ck_assert_int_eq(value_type, 1);
  ck_assert_int_eq(getbit(dec_result, 96), 0);

  dec_result = s21_add(DEC_MAX_VALUE, DEC_MIN_VALUE);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_float_eq_tol(flt_dst, 0.0, 0.00001);
  ck_assert_int_eq(getbit(dec_result, 96), 0);

  dec_result = s21_sub(DEC_MAX_VALUE, DEC_MIN_VALUE);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_int_eq(dec_result.value_type, 1);
  ck_assert_int_eq(getbit(dec_result, 96), 0);

  dec_result = s21_add(DEC_MIN_VALUE, DEC_MIN_VALUE);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_int_eq(dec_result.value_type, 2);
  ck_assert_int_eq(getbit(dec_result, 96), 0);

  dec_result = s21_div(DEC_MAX_VALUE, DEC_MAX_BIT1);
  s21_from_decimal_to_float(dec_result, &flt_dst);
  ck_assert_int_eq(dec_result.bits[0], 1);
  ck_assert_int_eq(dec_result.bits[1], 1);
  ck_assert_int_eq(dec_result.bits[2], 1);
  ck_assert_int_eq(getbit(dec_result, 96), 0);

  dec_result = s21_mul(DEC_MAX_VALUE, DEC_MAX_VALUE);
  ck_assert_int_eq(dec_result.value_type, 1);
  ck_assert_int_eq(getbit(dec_result, 96), 0);

  dec_result = s21_mul(DEC_MAX_VALUE, DEC_MIN_VALUE);
  ck_assert_int_eq(dec_result.value_type, 2);
  ck_assert_int_eq(getbit(dec_result, 96), 0);
}
END_TEST

START_TEST(non_valid_values) {
  dec_result = s21_add(DEC_1, DEC_INF);
  ck_assert_int_eq(dec_result.value_type, 1);

  dec_result = s21_add(DEC_1, DEC_INF_NEG);
  ck_assert_int_eq(dec_result.value_type, 2);

  dec_result = s21_add(DEC_INF, DEC_1);
  ck_assert_int_eq(dec_result.value_type, 1);

  dec_result = s21_add(DEC_INF_NEG, DEC_1);
  ck_assert_int_eq(dec_result.value_type, 2);

  dec_result = s21_add(DEC_INF, DEC_INF_NEG);
  ck_assert_int_eq(dec_result.value_type, 3);

  dec_result = s21_add(DEC_INF, DEC_INF);
  ck_assert_int_eq(dec_result.value_type, 1);

  dec_result = s21_add(DEC_NAN, DEC_INF);
  ck_assert_int_eq(dec_result.value_type, 3);

  dec_result = s21_sub(DEC_INF, DEC_INF);
  ck_assert_int_eq(dec_result.value_type, 3);

  dec_result = s21_sub(DEC_NAN, DEC_INF);
  ck_assert_int_eq(dec_result.value_type, 3);

  dec_result = s21_sub(DEC_INF_NEG, DEC_INF);
  ck_assert_int_eq(dec_result.value_type, 2);

  dec_result = s21_sub(DEC_INF, NORM_VAL);
  ck_assert_int_eq(dec_result.value_type, 1);

  dec_result = s21_sub(DEC_INF_NEG, NORM_VAL);
  ck_assert_int_eq(dec_result.value_type, 2);

  dec_result = s21_mul(DEC_INF, DEC_INF);
  ck_assert_int_eq(dec_result.value_type, 1);

  dec_result = s21_mul(DEC_NAN, DEC_INF);
  ck_assert_int_eq(dec_result.value_type, 3);

  dec_result = s21_mul(DEC_INF_NEG, DEC_1);
  ck_assert_int_eq(dec_result.value_type, 2);

  dec_result = s21_mul(DEC_INF_NEG, DEC_INF);
  ck_assert_int_eq(dec_result.value_type, 3);

  dec_result = s21_mul(DEC_INF, NORM_VAL);
  ck_assert_int_eq(dec_result.value_type, 1);

  dec_result = s21_div(DEC_INF, DEC_INF);
  ck_assert_int_eq(dec_result.value_type, 3);

  dec_result = s21_div(DEC_INF, NORM_VAL);
  ck_assert_int_eq(dec_result.value_type, 1);

  dec_result = s21_div(DEC_NAN, DEC_INF);
  ck_assert_int_eq(dec_result.value_type, 3);

  dec_result = s21_div(DEC_INF_NEG, DEC_1);
  ck_assert_int_eq(dec_result.value_type, 2);

  dec_result = s21_div(DEC_INF_NEG, DEC_INF_NEG);
  ck_assert_int_eq(dec_result.value_type, 3);

  dec_result = s21_div(DEC_1, DEC_0);
  ck_assert_int_eq(dec_result.value_type, 1);

  dec_result = s21_div(s21_negate(DEC_1), DEC_0);
  ck_assert_int_eq(dec_result.value_type, 2);

  int comp_conv_result;
  comp_conv_result = s21_is_less(DEC_INF, DEC_INF);
  ck_assert_int_eq(comp_conv_result, 1);

  comp_conv_result = s21_is_less(DEC_INF_NEG, DEC_INF);
  ck_assert_int_eq(comp_conv_result, 0);

  comp_conv_result = s21_is_less(DEC_NAN, DEC_INF_NEG);
  ck_assert_int_eq(comp_conv_result, 1);

  comp_conv_result = s21_is_less(DEC_NEG_1, DEC_1);
  ck_assert_int_eq(comp_conv_result, 0);

  comp_conv_result = s21_is_less_or_equal(DEC_INF, DEC_INF);
  ck_assert_int_eq(comp_conv_result, 1);

  comp_conv_result = s21_is_less_or_equal(DEC_INF, DEC_INF_NEG);
  ck_assert_int_eq(comp_conv_result, 1);

  comp_conv_result = s21_is_less_or_equal(DEC_INF_NEG, DEC_INF);
  ck_assert_int_eq(comp_conv_result, 0);

  comp_conv_result = s21_is_less_or_equal(DEC_NAN, DEC_INF_NEG);
  ck_assert_int_eq(comp_conv_result, 1);

  comp_conv_result = s21_is_greater(DEC_INF, DEC_INF);
  ck_assert_int_eq(comp_conv_result, 1);

  comp_conv_result = s21_is_greater(DEC_INF, DEC_INF_NEG);
  ck_assert_int_eq(comp_conv_result, 0);

  comp_conv_result = s21_is_greater(DEC_NAN, DEC_INF_NEG);
  ck_assert_int_eq(comp_conv_result, 1);

  comp_conv_result = s21_is_greater_or_equal(DEC_INF, DEC_INF);
  ck_assert_int_eq(comp_conv_result, 1);

  comp_conv_result = s21_is_greater_or_equal(DEC_INF, DEC_INF_NEG);
  ck_assert_int_eq(comp_conv_result, 0);

  comp_conv_result = s21_is_greater_or_equal(DEC_NAN, DEC_INF_NEG);
  ck_assert_int_eq(comp_conv_result, 1);

  comp_conv_result = s21_is_equal(DEC_INF, DEC_INF);
  ck_assert_int_eq(comp_conv_result, 1);

  comp_conv_result = s21_is_equal(DEC_INF, DEC_INF_NEG);
  ck_assert_int_eq(comp_conv_result, 1);

  comp_conv_result = s21_is_equal(DEC_NAN, DEC_INF_NEG);
  ck_assert_int_eq(comp_conv_result, 1);

  comp_conv_result = s21_is_not_equal(DEC_INF, DEC_INF);
  ck_assert_int_eq(comp_conv_result, 0);

  comp_conv_result = s21_is_not_equal(DEC_INF, DEC_INF_NEG);
  ck_assert_int_eq(comp_conv_result, 0);

  comp_conv_result = s21_is_not_equal(DEC_NAN, DEC_INF_NEG);
  ck_assert_int_eq(comp_conv_result, 0);

  comp_conv_result = s21_is_not_equal(NORM_VAL, DEC_INF);
  ck_assert_int_eq(comp_conv_result, 0);

  comp_conv_result = s21_is_not_equal(NORM_VAL, DEC_NAN);
  ck_assert_int_eq(comp_conv_result, 0);

  comp_conv_result = s21_is_not_equal(DEC_INF_NEG, NORM_VAL);
  ck_assert_int_eq(comp_conv_result, 0);

  comp_conv_result = s21_is_not_equal(DEC_INF, DEC_INF_NEG);
  ck_assert_int_eq(comp_conv_result, 0);

  comp_conv_result = s21_is_not_equal(DEC_INF_NEG, DEC_INF);
  ck_assert_int_eq(comp_conv_result, 0);

  comp_conv_result = s21_from_decimal_to_int(DEC_INF, &int_dst);
  ck_assert_int_eq(comp_conv_result, 1);

  comp_conv_result = s21_from_decimal_to_int(DEC_INF_NEG, &int_dst);
  ck_assert_int_eq(comp_conv_result, 1);

  comp_conv_result = s21_from_decimal_to_int(DEC_NAN, &int_dst);
  ck_assert_int_eq(comp_conv_result, 1);

  comp_conv_result = s21_from_decimal_to_float(DEC_INF, &flt_dst);
  ck_assert_int_eq(comp_conv_result, 1);

  comp_conv_result = s21_from_decimal_to_float(DEC_INF_NEG, &flt_dst);
  ck_assert_int_eq(comp_conv_result, 1);

  comp_conv_result = s21_from_decimal_to_float(DEC_NAN, &flt_dst);
  ck_assert_int_eq(comp_conv_result, 1);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, int_add);
  tcase_add_test(tc1_1, float_add);
  tcase_add_test(tc1_1, int_sub);
  tcase_add_test(tc1_1, float_sub);
  tcase_add_test(tc1_1, int_mul);
  tcase_add_test(tc1_1, float_mul);
  tcase_add_test(tc1_1, int_div);
  tcase_add_test(tc1_1, int_mul_and_div);
  tcase_add_test(tc1_1, float_div);
  tcase_add_test(tc1_1, mod);
  tcase_add_test(tc1_1, int_is_less);
  tcase_add_test(tc1_1, float_is_less);
  tcase_add_test(tc1_1, int_is_less_or_equal);
  tcase_add_test(tc1_1, float_is_less_or_equal);
  tcase_add_test(tc1_1, int_is_greater);
  tcase_add_test(tc1_1, float_is_greater);
  tcase_add_test(tc1_1, int_is_greater_or_equal);
  tcase_add_test(tc1_1, float_is_greater_or_equal);
  tcase_add_test(tc1_1, int_is_equal);
  tcase_add_test(tc1_1, float_is_equal);
  tcase_add_test(tc1_1, int_is_not_equal);
  tcase_add_test(tc1_1, float_is_not_equal);
  tcase_add_test(tc1_1, from_int_to_decimal_and_back);
  tcase_add_test(tc1_1, from_float_to_decimal_and_back);
  tcase_add_test(tc1_1, floor_21);
  tcase_add_test(tc1_1, round_21);
  tcase_add_test(tc1_1, truncate);
  tcase_add_test(tc1_1, negate);
  tcase_add_test(tc1_1, extremum);
  tcase_add_test(tc1_1, non_valid_values);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
