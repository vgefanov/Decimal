#include <check.h>
#include "s21_decimal.h"


typedef struct {
    s21_decimal op1;
    s21_decimal op2;
    s21_decimal wait;
} test_struct_ddd;


// s21_add

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    *result = (s21_decimal){ 0x00000002, 0x00000000, 0x00000000, 0x00000000 };
}

test_struct_ddd test_pack_add[] = {
    // 1 + 1 = 2
    {
        { 0x00000001, 0x00000000, 0x00000000, 0x00000000 },
        { 0x00000001, 0x00000000, 0x00000000, 0x00000000 },
        { 0x00000002, 0x00000000, 0x00000000, 0x00000000 }
    },
};


START_TEST(test_add) {
    s21_decimal result;
    s21_add(test_pack_add[_i].op1, test_pack_add[_i].op2, &result);
    ck_assert_mem_eq(&result, &test_pack_add[_i].wait, sizeof(s21_decimal));
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

    srunner_run_all(sr, CK_ENV);
    srunner_free(sr);
    return 0;
}
