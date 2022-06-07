#include "s21_decimal.h"

#include <check.h>

typedef struct {
    s21_decimal op1;
    s21_decimal op2;
    s21_decimal wait;
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
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000},
     {0x00000001, 0x00000000, 0x00000000, 0x00000000},
     {0x00000002, 0x00000000, 0x00000000, 0x00000000}},
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
    {{0x00000008, 0x00000000, 0x00000000, 0x00000000},
     {0x00000003, 0x00000000, 0x00000000, 0x00000000},
     {0x00000005, 0x00000000, 0x00000000, 0x00000000}},

    {{0x00000fff, 0x00000000, 0x00000000, 0x00000000},
     {0x00000794, 0x00000000, 0x00000000, 0x00000000},
     {0x0000086b, 0x00000000, 0x00000000, 0x00000000}},

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

    {{0xffffffff, 0xffffffff, 0x00ffffff, 0x80000000},
     {0x87654234, 0x00000567, 0x00000000, 0x00000000},
     {0x87654233, 0x00000567, 0x01000000, 0x80000000}},

    {{0xffffffff, 0xffffffff, 0x00ffffff, 0x00000000},
     {0x87654234, 0x00000567, 0x00000000, 0x00000000},
     {0x789abdcb, 0xfffffa98, 0x00ffffff, 0x00000000}},
};

START_TEST(test_sub) {
    s21_decimal result;
    s21_sub(test_pack_sub[_i].op1, test_pack_sub[_i].op2, &result);
    ck_assert_mem_eq(&result, &test_pack_sub[_i].wait, sizeof(s21_decimal));
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
    ck_assert_int_eq(
        s21_is_less(test_pack_comparison[_i].op1, test_pack_comparison[_i].op2),
        test_pack_comparison[_i].result_less);
}
END_TEST

// Меньше или равно <=
START_TEST(test_less_or_equal) {
    ck_assert_int_eq(s21_is_less_or_equal(test_pack_comparison[_i].op1,
                                          test_pack_comparison[_i].op2),
                     test_pack_comparison[_i].result_less_or_equal);
}
END_TEST

// Больше >
START_TEST(test_greater) {
    ck_assert_int_eq(s21_is_greater(test_pack_comparison[_i].op1,
                                    test_pack_comparison[_i].op2),
                     test_pack_comparison[_i].result_greater);
}
END_TEST

// Больше или равно >=
START_TEST(test_greater_or_equal) {
    ck_assert_int_eq(s21_is_greater_or_equal(test_pack_comparison[_i].op1,
                                             test_pack_comparison[_i].op2),
                     test_pack_comparison[_i].result_greater_or_equal);
}
END_TEST

// Равно ==
START_TEST(test_equal) {
    ck_assert_int_eq(s21_is_equal(test_pack_comparison[_i].op1,
                                  test_pack_comparison[_i].op2),
                     test_pack_comparison[_i].result_equal);
}
END_TEST

// Не равно !=
START_TEST(test_not_equal) {
    ck_assert_int_eq(s21_is_not_equal(test_pack_comparison[_i].op1,
                                      test_pack_comparison[_i].op2),
                     test_pack_comparison[_i].result_not_equal);
}
END_TEST

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

    // Меньше <
    int test_pack_size_less =
        sizeof(test_pack_comparison) / sizeof(test_struct_ddi);
    tcase_add_loop_test(tc, test_less, 0, test_pack_size_less);

    // Меньше или равно <=
    int test_pack_size_less_or_equal =
        sizeof(test_pack_comparison) / sizeof(test_struct_ddi);
    tcase_add_loop_test(tc, test_less_or_equal, 0,
                        test_pack_size_less_or_equal);

    // Больше >
    int test_pack_size_greater =
        sizeof(test_pack_comparison) / sizeof(test_struct_ddi);
    tcase_add_loop_test(tc, test_greater, 0, test_pack_size_greater);

    // Больше или равно >=
    int test_pack_size_greater_or_equal =
        sizeof(test_pack_comparison) / sizeof(test_struct_ddi);
    tcase_add_loop_test(tc, test_greater_or_equal, 0,
                        test_pack_size_greater_or_equal);

    // Равно ==
    int test_pack_size_equal =
        sizeof(test_pack_comparison) / sizeof(test_struct_ddi);
    tcase_add_loop_test(tc, test_equal, 0, test_pack_size_equal);

    // Не равно !=
    int test_pack_size_not_equal =
        sizeof(test_pack_comparison) / sizeof(test_struct_ddi);
    tcase_add_loop_test(tc, test_not_equal, 0, test_pack_size_not_equal);

    srunner_run_all(sr, CK_ENV);
    srunner_free(sr);
    return 0;
}
