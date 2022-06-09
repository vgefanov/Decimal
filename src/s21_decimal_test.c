#include "s21_decimal.h"

#include <check.h>
#include <limits.h>

typedef struct {
    s21_decimal op1;
    int op2;
} test_struct_di;

typedef struct {
    s21_decimal op1;
    float op2;
    int result_code;
} test_struct_df;

typedef struct {
    s21_decimal op;
    s21_decimal wait;
} test_struct_dd;

typedef struct {
    s21_decimal op1;
    s21_decimal op2;
    s21_decimal wait;
    int result_code;
} test_struct_ddd;

typedef struct {
    s21_decimal op1;
    s21_decimal op2;
    int result_less;
    int result_less_or_equal;
    int result_greater;
    int result_greater_or_equal;
    int result_equal;
    int result_not_equal;
} test_struct_ddi;

// s21_add

test_struct_ddd test_pack_add[] = {
    // 1 + 1 = 2
    { {0x82e25aed, 0xf9e825ad, 0xb03ef094, 0x800e0000},
      {0x481b1f98, 0xfbfd896d, 0x00046d77, 0x80220000},
      {0xb629b5da, 0xf9ea0c7f, 0xb03ef094, 0x800e0000},
      RESULT_SUCCESS },

    { {0x00000001, 0x00000000, 0x00000000, 0x00000000},
      {0x00000001, 0x00000000, 0x00000000, 0x00000000},
      {0x00000002, 0x00000000, 0x00000000, 0x00000000},
      RESULT_SUCCESS },

    // {{0x00000555, 0x00000000, 0x00000000, 0x80000000},
    //  {0x00099999, 0x00000000, 0x00000000, 0x80000000},
    //  {0x00099EEE, 0x00000000, 0x00000000, 0x80000000}},

    // {{0xAAAAAAAA, 0x00000000, 0x00000000, 0x00000000},
    //  {0x00999999, 0x00000000, 0x00000000, 0x00000000},
    //  {0xAB444443, 0x00000000, 0x00000000, 0x00000000}},

    // {{0x00000010, 0x00000000, 0x00000000, 0x00000000},
    //  {0x00000010, 0x00000000, 0x00000000, 0x00000000},
    //  {0x00000020, 0x00000000, 0x00000000, 0x00000000}},

    // {{0x7f7f7f7f, 0x00007f7f, 0x00000000, 0x00040000},
    //  {0x7f7f7f7f, 0x007f7f7f, 0x00000000, 0x00040000},
    //  {0xfefefefe, 0x007ffefe, 0x00000000, 0x00040000}},

    // {{0xffffffff, 0xffffffff, 0x00000000, 0x00000000},
    //  {0xffffffff, 0xffffffff, 0x00000000, 0x00000000},
    //  {0xfffffffe, 0xffffffff, 0x00000001, 0x00000000}},

    // {{0x7f7f7f7f, 0x00007f7f, 0x00000000, 0x00000000},
    //  {0x7f7f7f7f, 0x007f7f7f, 0x00000000, 0x80000000},
    //  {0x00000000, 0x007f0000, 0x00000000, 0x80000000}},

    // {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000},
    //  {0xffffffff, 0xffffffff, 0x00000000, 0x00000000},
    //  {0x00000000, 0x00000000, 0xffffffff, 0x80000000}},
};

START_TEST(test_add) {
    s21_decimal result;
    s21_add(test_pack_add[_i].op1, test_pack_add[_i].op2, &result);
    ck_assert_mem_eq(&result, &test_pack_add[_i].wait, sizeof(s21_decimal));
}
END_TEST

// s21_sub

test_struct_ddd test_pack_sub[] = {
    // 1 + 1 = 2
    { {0x00000008, 0x00000000, 0x00000000, 0x00000000},
      {0x00000003, 0x00000000, 0x00000000, 0x00000000},
      {0x00000005, 0x00000000, 0x00000000, 0x00000000},
      RESULT_SUCCESS },

    {{0x00000fff, 0x00000000, 0x00000000, 0x00000000},
     {0x00000794, 0x00000000, 0x00000000, 0x00000000},
     {0x0000086b, 0x00000000, 0x00000000, 0x00000000},
      RESULT_SUCCESS },

    {{0xffffffff, 0xffffffff, 0x00ffffff, 0x80000000},
     {0x87654234, 0x00000567, 0x00000000, 0x00000000},
     {0x87654233, 0x00000567, 0x01000000, 0x80000000},
      RESULT_SUCCESS },

    {{0xffffffff, 0xffffffff, 0x00ffffff, 0x00000000},
     {0x87654234, 0x00000567, 0x00000000, 0x00000000},
     {0x789abdcb, 0xfffffa98, 0x00ffffff, 0x00000000},
      RESULT_SUCCESS },
};

START_TEST(test_sub) {
    s21_decimal result;
    s21_sub(test_pack_sub[_i].op1, test_pack_sub[_i].op2, &result);
    ck_assert_mem_eq(&result, &test_pack_sub[_i].wait, sizeof(s21_decimal));
}
END_TEST

// s21_mul

test_struct_ddd test_pack_mul[] = {
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000},
     {0x00000001, 0x00000000, 0x00000000, 0x00000000},
     {0x00000001, 0x00000000, 0x00000000, 0x00000000},
      RESULT_SUCCESS },

    {{0x00000002, 0x00000000, 0x00000000, 0x00000000},
     {0x00000002, 0x00000000, 0x00000000, 0x00000000},
     {0x00000004, 0x00000000, 0x00000000, 0x00000000},
      RESULT_SUCCESS },

    {{0xffffffff, 0x00000000, 0x00000000, 0x00030000},
     {0xcccc1234, 0xaaaaaabb, 0x00000000, 0x00080000},
     {0x3333edcc, 0x22216778, 0xaaaaaabb, 0x000b0000},
      RESULT_SUCCESS },

    {{0x00000000, 0x00000000, 0x00000000, 0x00000000},
     {0x00000000, 0x00000000, 0x00000000, 0x00000000},
     {0x00000000, 0x00000000, 0x00000000, 0x00000000},
      RESULT_SUCCESS },
};

START_TEST(test_mul) {
    s21_decimal result;
    s21_mul(test_pack_mul[_i].op1, test_pack_mul[_i].op2, &result);
    ck_assert_mem_eq(&result, &test_pack_mul[_i].wait, sizeof(s21_decimal));
}
END_TEST

// s21_div

test_struct_ddd test_pack_div[] = {
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000},
     {0x00000001, 0x00000000, 0x00000000, 0x00000000},
     {0x00000001, 0x00000000, 0x00000000, 0x00000000},
      RESULT_SUCCESS },

    {{0x000186A0, 0x00000000, 0x00000000, 0x00000000},
     {0x0000000a, 0x00000000, 0x00000000, 0x00000000},
     {0x00002710, 0x00000000, 0x00000000, 0x00000000},
      RESULT_SUCCESS },

    {{0x00000004, 0x00000000, 0x00000000, 0x00000000},
     {0x00000002, 0x00000000, 0x00000000, 0x00000000},
     {0x00000002, 0x00000000, 0x00000000, 0x00000000},
      RESULT_SUCCESS },

    {{0x3333edcc, 0x22216778, 0xaaaaaabb, 0x00000000},
     {0xffffffff, 0x00000000, 0x00000000, 0x00000000},
     {0xcccc1234, 0xaaaaaabb, 0x00000000, 0x00000000},
      RESULT_SUCCESS },

    {{0x499602D2, 0x00000000, 0x00000000, 0x00000000},
     {0x00000005, 0x00000000, 0x00000000, 0x00000000},
     {0x0eb79a2a, 0x00000000, 0x00000000, 0x00000000},
      RESULT_SUCCESS },

    {{0x00000369, 0x00000000, 0x00000000, 0x00020000},
     {0x00000003, 0x00000000, 0x00000000, 0x00000000},
     {0x00000123, 0x00000000, 0x00000000, 0x00020000},
      RESULT_SUCCESS },
    // 1 / 0
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000},
     {0x00000000, 0x00000000, 0x00000000, 0x00000000},
     {0x00000000, 0x00000000, 0x00000000, 0x00000000},
      DIVBYZERO_ERROR },
    // 0 / 0
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000},
     {0x00000000, 0x00000000, 0x00000000, 0x00000000},
     {0x00000000, 0x00000000, 0x00000000, 0x00000000},
      DIVBYZERO_ERROR },
};

START_TEST(test_div) {
    s21_decimal result;
    int result_code = s21_div(test_pack_div[_i].op1, test_pack_div[_i].op2, &result);
    ck_assert_int_eq(result_code, test_pack_div[_i].result_code);
    if (result_code == RESULT_SUCCESS) {
        ck_assert_mem_eq(&result, &test_pack_div[_i].wait, sizeof(s21_decimal));
    }
}
END_TEST

// s21_mod

test_struct_ddd test_pack_mod[] = {
    {{0x00000011, 0x00000000, 0x00000000, 0x00010000},
     {0x00000007, 0x00000000, 0x00000000, 0x00010000},
     {0x00000003, 0x00000000, 0x00000000, 0x00010000},
      RESULT_SUCCESS },

    {{0x00002810, 0x00000000, 0x00000000, 0x00030000},
     {0x0000000b, 0x00000000, 0x00000000, 0x00010000},
     {0x00000164, 0x00000000, 0x00000000, 0x00030000},
      RESULT_SUCCESS },

};

START_TEST(test_mod) {
    s21_decimal result;
    s21_mod(test_pack_mod[_i].op1, test_pack_mod[_i].op2, &result);
    ck_assert_mem_eq(&result, &test_pack_mod[_i].wait, sizeof(s21_decimal));
}
END_TEST

// s21_is_comparison

test_struct_ddi test_pack_comparison[] = {
    // -5 <, <=, >, >=, ==, != +3
    {{0x00000005, 0x00000005, 0x00000005, 0x80200000},
     {0x00000003, 0x00000003, 0x00000003, 0x00090000},
     TRUE,
     TRUE,
     FALSE,
     FALSE,
     FALSE,
     TRUE},

    // -3 <, <=, >, >=, ==, != +5
    {{0x00000003, 0x00000003, 0x00000003, 0x80200000},
     {0x00000005, 0x00000005, 0x00000005, 0x00090000},
     TRUE,
     TRUE,
     FALSE,
     FALSE,
     FALSE,
     TRUE},

    // -3 <, <=, >, >=, ==, != +3
    {{0x00000003, 0x00000003, 0x00000003, 0x80200000},
     {0x00000003, 0x00000003, 0x00000003, 0x00200000},
     TRUE,
     TRUE,
     FALSE,
     FALSE,
     FALSE,
     TRUE},

    // -0 <, <=, >, >=, ==, != +0
    {{0x00000000, 0x00000000, 0x00000000, 0x80000000},
     {0x00000000, 0x00000000, 0x00000000, 0x00000000},
     FALSE,
     TRUE,
     FALSE,
     TRUE,
     TRUE,
     FALSE},

    // +5 <, <=, >, >=, ==, != -3
    {{0x00000005, 0x00000005, 0x00000005, 0x00200000},
     {0x00000003, 0x00000003, 0x00000003, 0x80090000},
     FALSE,
     FALSE,
     TRUE,
     TRUE,
     FALSE,
     TRUE},

    // +3 <, <=, >, >=, ==, != -5
    {{0x00000003, 0x00000003, 0x00000003, 0x00200000},
     {0x00000005, 0x00000005, 0x00000005, 0x80090000},
     FALSE,
     FALSE,
     TRUE,
     TRUE,
     FALSE,
     TRUE},

    // +3 <, <=, >, >=, ==, != -3
    {{0x00000003, 0x00000003, 0x00000003, 0x00200000},
     {0x00000003, 0x00000003, 0x00000003, 0x80090000},
     FALSE,
     FALSE,
     TRUE,
     TRUE,
     FALSE,
     TRUE},

    // +0 <, <=, >, >=, ==, != -0
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000},
     {0x00000000, 0x00000000, 0x00000000, 0x80090000},
     FALSE,
     TRUE,
     FALSE,
     TRUE,
     TRUE,
     FALSE},

    // -5 <, <=, >, >=, ==, != -3
    {{0x00000005, 0x00000005, 0x00000005, 0x80090000},
     {0x00000003, 0x00000003, 0x00000003, 0x80090000},
     TRUE,
     TRUE,
     FALSE,
     FALSE,
     FALSE,
     TRUE},

    // -3 <, <=, >, >=, ==, != -5
    {{0x00000003, 0x00000003, 0x00000003, 0x80200000},
     {0x00000005, 0x00000005, 0x00000005, 0x80200000},
     FALSE,
     FALSE,
     TRUE,
     TRUE,
     FALSE,
     TRUE},

    // -3 <, <=, >, >=, ==, != -3
    {{0x00000003, 0x00000003, 0x00000003, 0x80200000},
     {0x00000003, 0x00000003, 0x00000003, 0x80200000},
     FALSE,
     TRUE,
     FALSE,
     TRUE,
     TRUE,
     FALSE},

    // -0 <, <=, >, >=, ==, != -0
    {{0x00000000, 0x00000000, 0x00000000, 0x80200000},
     {0x00000000, 0x00000000, 0x00000000, 0x80090000},
     FALSE,
     TRUE,
     FALSE,
     TRUE,
     TRUE,
     FALSE},

    // +5 <, <=, >, >=, ==, != +3
    {{0x00000005, 0x00000005, 0x00000005, 0x00200000},
     {0x00000003, 0x00000003, 0x00000003, 0x00200000},
     FALSE,
     FALSE,
     TRUE,
     TRUE,
     FALSE,
     TRUE},

    // +3 <, <=, >, >=, ==, != +5
    {{0x00000003, 0x00000003, 0x00000003, 0x00200000},
     {0x00000005, 0x00000005, 0x00000005, 0x00200000},
     TRUE,
     TRUE,
     FALSE,
     FALSE,
     FALSE,
     TRUE},

    // +3 <, <=, >, >=, ==, != +3
    {{0x00000003, 0x00000003, 0x00000003, 0x00200000},
     {0x00000003, 0x00000003, 0x00000003, 0x00200000},
     FALSE,
     TRUE,
     FALSE,
     TRUE,
     TRUE,
     FALSE},

    // +0 <, <=, >, >=, ==, != +0
    {{0x00000000, 0x00000000, 0x00000000, 0x00200000},
     {0x00000000, 0x00000000, 0x00000000, 0x00090000},
     FALSE,
     TRUE,
     FALSE,
     TRUE,
     TRUE,
     FALSE},
};

// Меньше <
START_TEST(test_less) {
    ck_assert_int_eq(s21_is_less(test_pack_comparison[_i].op1, test_pack_comparison[_i].op2),
                     test_pack_comparison[_i].result_less);
}
END_TEST

// Меньше или равно <=
START_TEST(test_less_or_equal) {
    ck_assert_int_eq(s21_is_less_or_equal(test_pack_comparison[_i].op1, test_pack_comparison[_i].op2),
                     test_pack_comparison[_i].result_less_or_equal);
}
END_TEST

// Больше >
START_TEST(test_greater) {
    ck_assert_int_eq(s21_is_greater(test_pack_comparison[_i].op1, test_pack_comparison[_i].op2),
                     test_pack_comparison[_i].result_greater);
}
END_TEST

// Больше или равно >=
START_TEST(test_greater_or_equal) {
    ck_assert_int_eq(s21_is_greater_or_equal(test_pack_comparison[_i].op1, test_pack_comparison[_i].op2),
                     test_pack_comparison[_i].result_greater_or_equal);
}
END_TEST

// Равно ==
START_TEST(test_equal) {
    ck_assert_int_eq(s21_is_equal(test_pack_comparison[_i].op1, test_pack_comparison[_i].op2),
                     test_pack_comparison[_i].result_equal);
}
END_TEST

// Не равно !=
START_TEST(test_not_equal) {
    ck_assert_int_eq(s21_is_not_equal(test_pack_comparison[_i].op1, test_pack_comparison[_i].op2),
                     test_pack_comparison[_i].result_not_equal);
}
END_TEST

// s21_from_decimal_to_int

test_struct_di test_pack_fdti[] = {
    { { 10000, 0x00000000, 0x00000000, 0x00000000 }, 10000},
    { { INT_MAX, 0x00000000, 0x00000000, 0x00000000 }, INT_MAX },
    { {(unsigned)INT_MAX + 1, 0x00000000, 0x00000000, 0x80000000}, INT_MIN },
    { { (unsigned)INT_MAX + 1, 0x00000000, 0x00000000, 0x00000000}, 0 },
    { { (unsigned)INT_MAX + 2, 0x00000000, 0x00000000, 0x80000000}, 0 },
    { { 0x173c1c7, 0, 0, 0x80070000 }, -2 },

};

START_TEST(test_fdti) {
    int result = 0;
    s21_from_decimal_to_int(test_pack_fdti[_i].op1, &result);
    ck_assert_int_eq(result, test_pack_fdti[_i].op2);
}
END_TEST

// s21_from_float_to_decimal

test_struct_df test_pack_fftd[] = {
    { { 0x0000fe65, 0x00000000, 0x00000000, 0x80030000 }, -65.125, RESULT_SUCCESS },
    // s21_from_float_to_decimal_1
    { { 3, 0, 0, 0x00020000 }, 0.03F, RESULT_SUCCESS },
    { { 1271234, 0, 0, 0x00040000 }, 127.1234F, RESULT_SUCCESS },
    // s21_from_float_to_decimal_3
    { { 1020000000, 0, 0, 0 }, 1.02E+09F, RESULT_SUCCESS },
    // s21_from_float_to_decimal_4
    { { 0, 0, 0, 0 }, 1.0F / 0.0F, RESULT_ERROR },
    // s21_from_float_to_decimal_5
    { { 0, 0, 0, 0 }, -1.0F / 0.0F, RESULT_ERROR },
    // s21_from_float_to_decimal_6
    { { 0, 0, 0, 0 }, NAN, RESULT_ERROR },
};

START_TEST(test_fftd) {
    s21_decimal result;
    int result_code = s21_from_float_to_decimal(test_pack_fftd[_i].op2, &result);
    ck_assert_int_eq(result_code, test_pack_fftd[_i].result_code);
    if (result_code == RESULT_SUCCESS) {
        ck_assert_mem_eq(&result, &test_pack_fftd[_i].op1, sizeof(s21_decimal));
    }
}
END_TEST

// s21_from_decimal_to_float

test_struct_df test_pack_fdtf[] = {
    { { 0x0000fe65, 0x00000000, 0x00000000, 0x80030000 }, -65.125, RESULT_SUCCESS },
    { { 3, 0, 0, 0x00020000 }, 0.03F, RESULT_SUCCESS },
    { { 1271234, 0, 0, 0x00040000 }, 127.1234F, RESULT_SUCCESS },
    { { 1020000000, 0, 0, 0 }, 1.02E+09F, RESULT_SUCCESS },
    // dec_to_float_20 -123458677.98765434567898765435 = -1.234587E+08 (-856982897)
    { { 0xb901187b, 0x6e9896ec, 0x27e44332, 0x80140000 }, -1.234587E+08 },
};

START_TEST(test_fdtf) {
    float result = 0;
    s21_from_decimal_to_float(test_pack_fdtf[_i].op1, &result);
    ck_assert_float_eq(result, test_pack_fdtf[_i].op2);
}
END_TEST

// s21_round

test_struct_ddd test_pack_round[] = {
    {{0x00000011, 0x00000000, 0x00000000, 0x00010000}, {0x00000002, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000010, 0x00000000, 0x00000000, 0x00010000}, {0x00000002, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00002810, 0x00000000, 0x00000000, 0x00030000}, {0x0000000a, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000010, 0x00000000, 0x00000000, 0x80010000}, {0x00000002, 0x00000000, 0x00000000, 0x80000000}},
    {{0x0000000f, 0x00000000, 0x00000000, 0x80010000}, {0x00000002, 0x00000000, 0x00000000, 0x80000000}},
    {{0x00000095, 0x00000000, 0x00000000, 0x80020000}, {0x00000001, 0x00000000, 0x00000000, 0x80000000}},
};

START_TEST(test_round) {
    s21_decimal result;
    s21_round(test_pack_round[_i].op1, &result);
    ck_assert_mem_eq(&result, &test_pack_round[_i].op2, sizeof(s21_decimal));
}
END_TEST

// s21_truncate

test_struct_dd test_pack_truncate[] = {
    // 2.1234 = 2
    { { 0x0052f2, 0, 0, 0x040000 }, {2, 0, 0, 0} },
};

START_TEST(test_truncate) {
    s21_decimal result;
    s21_truncate(test_pack_truncate[_i].op, &result);
    ck_assert_mem_eq(&result, &test_pack_truncate[_i].wait, sizeof(s21_decimal));
}
END_TEST

// main

int main() {
    Suite *s = suite_create("s21_decimal test");
    SRunner *sr = srunner_create(s);
    srunner_set_fork_status(sr, CK_NOFORK);
    TCase *tc = tcase_create("s21_decimal case");
    suite_add_tcase(s, tc);
    tcase_set_timeout(tc, 10);

    int test_pack_size = sizeof(test_pack_add) / sizeof(test_struct_ddd);
    tcase_add_loop_test(tc, test_add, 0, test_pack_size);

    test_pack_size = sizeof(test_pack_sub) / sizeof(test_struct_ddd);
    tcase_add_loop_test(tc, test_sub, 0, test_pack_size);

    test_pack_size = sizeof(test_pack_mul) / sizeof(test_struct_ddd);
    tcase_add_loop_test(tc, test_mul, 0, test_pack_size);

    test_pack_size = sizeof(test_pack_div) / sizeof(test_struct_ddd);
    tcase_add_loop_test(tc, test_div, 0, test_pack_size);

    test_pack_size = sizeof(test_pack_mod) / sizeof(test_struct_ddd);
    tcase_add_loop_test(tc, test_mod, 0, test_pack_size);

    // Меньше <
    int test_pack_size_less = sizeof(test_pack_comparison) / sizeof(test_struct_ddi);
    tcase_add_loop_test(tc, test_less, 0, test_pack_size_less);

    // Меньше или равно <=
    int test_pack_size_less_or_equal = sizeof(test_pack_comparison) / sizeof(test_struct_ddi);
    tcase_add_loop_test(tc, test_less_or_equal, 0, test_pack_size_less_or_equal);

    // Больше >
    int test_pack_size_greater = sizeof(test_pack_comparison) / sizeof(test_struct_ddi);
    tcase_add_loop_test(tc, test_greater, 0, test_pack_size_greater);

    // Больше или равно >=
    int test_pack_size_greater_or_equal = sizeof(test_pack_comparison) / sizeof(test_struct_ddi);
    tcase_add_loop_test(tc, test_greater_or_equal, 0, test_pack_size_greater_or_equal);

    // Равно ==
    int test_pack_size_equal = sizeof(test_pack_comparison) / sizeof(test_struct_ddi);
    tcase_add_loop_test(tc, test_equal, 0, test_pack_size_equal);

    // Не равно !=
    int test_pack_size_not_equal = sizeof(test_pack_comparison) / sizeof(test_struct_ddi);
    tcase_add_loop_test(tc, test_not_equal, 0, test_pack_size_not_equal);

    // s21_from_decimal_to_int
    int test_pack_size_fdti = sizeof(test_pack_fdti) / sizeof(test_struct_di);
    tcase_add_loop_test(tc, test_fdti, 0, test_pack_size_fdti);

    // s21_from_float_to_decimal
    int test_pack_size_fftd = sizeof(test_pack_fftd) / sizeof(test_struct_df);
    tcase_add_loop_test(tc, test_fftd, 0, test_pack_size_fftd);

    // s21_from_decimal_to_float
    int test_pack_size_fdtf = sizeof(test_pack_fdtf) / sizeof(test_struct_df);
    tcase_add_loop_test(tc, test_fdtf, 0, test_pack_size_fdtf);

    // round
    test_pack_size = sizeof(test_pack_round) / sizeof(test_struct_ddd);
    tcase_add_loop_test(tc, test_round, 0, test_pack_size);

    // truncate
    test_pack_size = sizeof(test_pack_truncate) / sizeof(test_struct_dd);
    tcase_add_loop_test(tc, test_truncate, 0, test_pack_size);

    srunner_run_all(sr, CK_ENV);
    srunner_free(sr);
    return 0;
}
