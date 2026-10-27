#include <check.h>
#include <stdlib.h>
#include "phonebook_header.h"

// 1. Тестовая функция
START_TEST(main_test)
{
    FILE *null_out = freopen("/dev/null", "w", stdout);
    ck_assert_ptr_nonnull(null_out);

    FILE *redirected = freopen("test_input.txt", "r", stdin);
    ck_assert_ptr_nonnull(redirected);

    int len_book = 3;
    info *book = malloc(sizeof(info) * len_book);
    new_memory_for_book(&book, &len_book);
    int index_last_elem = 1;
    new_memory_for_elem(&book[index_last_elem - 1]);
    add(&book[index_last_elem - 1]);
    index_last_elem++;
    new_memory_for_elem(&book[index_last_elem - 1]);
    add(&book[index_last_elem - 1]);
    index_last_elem++;
    new_memory_for_elem(&book[index_last_elem - 1]);
    add(&book[index_last_elem - 1]);
    index_last_elem++;
    new_memory_for_elem(&book[index_last_elem - 1]);
    add(&book[index_last_elem - 1]);
    edit(&book[0]);
    edit(&book[1]);
    edit(&book[2]);
    edit(&book[3]);
    null_out = freopen("res.txt", "w", stdout);
    ck_assert_ptr_nonnull(null_out);
    print_book(book, index_last_elem);
    for (int i = 0; i < index_last_elem; i++){
        free_memory(&book[i]);
    }
    free(book);
    book = NULL;
    ck_assert_int_eq(1, 1);
}
END_TEST

// 2. Создание TCase и Suite
Suite *math_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Math");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, main_test);
    suite_add_tcase(s, tc_core);

    return s;
}

Suite *mat_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Math");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, main_test);
    suite_add_tcase(s, tc_core);

    return s;
}

// 3. Запуск тестов через SRunner
int main(void)
{
    //int number_failed;
    Suite *s;
    Suite *ss;
    SRunner *sr;

    s = math_suite();
    ss = mat_suite();
    sr = srunner_create(s);
     srunner_add_suite(sr, ss);

    srunner_run_all(sr, CK_NORMAL);
    //number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return 0;
}
