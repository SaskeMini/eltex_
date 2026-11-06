#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "phonebook_header.h"

static info make_info(const char *name, const char *surname, const char *phone){
    info e;
    new_memory_for_elem(&e);
    strcpy(e.name, name);
    strcpy(e.surname, surname);
    strcpy(e.phone_number, phone);
    return e;
}

static void free_list(list *head){
    while (head){
        head = del_list(head, 0);
    }
}

static int list_len(list *head){
    int n = 0;
    for (list *p = head; p; p = p->next) n++;
    return n;
}

static int is_sorted(list *head){
    for (list *p = head; p && p->next; p = p->next){
        if (strcmp(p->elem->surname, p->next->elem->surname) > 0) return 0;
    }
    return 1;
}

static int links_ok(list *head){
    if (!head) return 1;
    if (head->prev) return 0;
    for (list *p = head; p; p = p->next){
        if (p->next && p->next->prev != p) return 0;
    }
    return 1;
}

START_TEST(add_list_empty)
{
    list *book = NULL;
    info *a = malloc(sizeof(info));
    *a = make_info("Ivan", "Ivanov", "111");
    book = add_list(book, a);
    ck_assert_ptr_nonnull(book);
    ck_assert_ptr_null(book->prev);
    ck_assert_ptr_null(book->next);
    ck_assert_str_eq(book->elem->surname, "Ivanov");
    free_list(book);
}
END_TEST

START_TEST(add_list_sorted_insert)
{
    list *book = NULL;
    info *a = malloc(sizeof(info)); *a = make_info("A", "C", "1");
    info *b = malloc(sizeof(info)); *b = make_info("B", "A", "2");
    info *c = malloc(sizeof(info)); *c = make_info("C", "B", "3");
    info *d = malloc(sizeof(info)); *d = make_info("D", "D", "4");

    book = add_list(book, a);
    book = add_list(book, b);
    book = add_list(book, c);
    book = add_list(book, d);

    ck_assert_int_eq(list_len(book), 4);
    ck_assert(is_sorted(book));
    ck_assert(links_ok(book));
    ck_assert_str_eq(book->elem->surname, "A");
    ck_assert_str_eq(book->next->elem->surname, "B");
    ck_assert_str_eq(book->next->next->elem->surname, "C");
    ck_assert_str_eq(book->next->next->next->elem->surname, "D");
    ck_assert_ptr_null(book->next->next->next->next);
    free_list(book);
}
END_TEST

START_TEST(add_list_insert_head)
{
    list *book = NULL;
    info *a = malloc(sizeof(info)); *a = make_info("A", "M", "1");
    info *b = malloc(sizeof(info)); *b = make_info("B", "A", "2");
    book = add_list(book, a);
    list *old_head = book;
    book = add_list(book, b);
    ck_assert_ptr_ne(book, old_head);
    ck_assert_ptr_eq(book->next, old_head);
    ck_assert_ptr_eq(old_head->prev, book);
    ck_assert_str_eq(book->elem->surname, "A");
    free_list(book);
}
END_TEST

START_TEST(add_list_insert_middle_and_tail)
{
    list *book = NULL;
    info *a = malloc(sizeof(info)); *a = make_info("A", "A", "1");
    info *c = malloc(sizeof(info)); *c = make_info("C", "C", "3");
    info *b = malloc(sizeof(info)); *b = make_info("B", "B", "2");
    info *d = malloc(sizeof(info)); *d = make_info("D", "D", "4");
    book = add_list(book, a);
    book = add_list(book, c);
    book = add_list(book, b);
    book = add_list(book, d);
    ck_assert(is_sorted(book));
    ck_assert(links_ok(book));
    ck_assert_int_eq(list_len(book), 4);
    free_list(book);
}
END_TEST

START_TEST(del_list_null)
{
    list *book = NULL;
    book = del_list(book, 0);
    ck_assert_ptr_null(book);
}
END_TEST

START_TEST(del_list_single)
{
    list *book = NULL;
    info *a = malloc(sizeof(info)); *a = make_info("A", "A", "1");
    book = add_list(book, a);
    book = del_list(book, 0);
    ck_assert_ptr_null(book);
}
END_TEST

START_TEST(del_list_head)
{
    list *book = NULL;
    info *a = malloc(sizeof(info)); *a = make_info("A", "A", "1");
    info *b = malloc(sizeof(info)); *b = make_info("B", "B", "2");
    info *c = malloc(sizeof(info)); *c = make_info("C", "C", "3");
    book = add_list(book, a);
    book = add_list(book, b);
    book = add_list(book, c);
    book = del_list(book, 0);
    ck_assert_int_eq(list_len(book), 2);
    ck_assert_str_eq(book->elem->surname, "B");
    ck_assert_ptr_null(book->prev);
    ck_assert(links_ok(book));
    free_list(book);
}
END_TEST

START_TEST(del_list_tail)
{
    list *book = NULL;
    info *a = malloc(sizeof(info)); *a = make_info("A", "A", "1");
    info *b = malloc(sizeof(info)); *b = make_info("B", "B", "2");
    info *c = malloc(sizeof(info)); *c = make_info("C", "C", "3");
    book = add_list(book, a);
    book = add_list(book, b);
    book = add_list(book, c);
    book = del_list(book, 2);
    ck_assert_int_eq(list_len(book), 2);
    ck_assert_ptr_null(book->next->next);
    ck_assert(links_ok(book));
    free_list(book);
}
END_TEST

START_TEST(del_list_middle)
{
    list *book = NULL;
    info *a = malloc(sizeof(info)); *a = make_info("A", "A", "1");
    info *b = malloc(sizeof(info)); *b = make_info("B", "B", "2");
    info *c = malloc(sizeof(info)); *c = make_info("C", "C", "3");
    book = add_list(book, a);
    book = add_list(book, b);
    book = add_list(book, c);
    book = del_list(book, 1);
    ck_assert_int_eq(list_len(book), 2);
    ck_assert_str_eq(book->elem->surname, "A");
    ck_assert_str_eq(book->next->elem->surname, "C");
    ck_assert(links_ok(book));
    free_list(book);
}
END_TEST

START_TEST(del_list_out_of_range)
{
    list *book = NULL;
    info *a = malloc(sizeof(info)); *a = make_info("A", "A", "1");
    book = add_list(book, a);
    book = del_list(book, 5);
    ck_assert_int_eq(list_len(book), 1);
    book = del_list(book, -1);
    ck_assert_int_eq(list_len(book), 1);
    free_list(book);
}
END_TEST

START_TEST(del_list_all)
{
    list *book = NULL;
    info *a = malloc(sizeof(info)); *a = make_info("A", "A", "1");
    info *b = malloc(sizeof(info)); *b = make_info("B", "B", "2");
    book = add_list(book, a);
    book = add_list(book, b);
    book = del_list(book, 0);
    book = del_list(book, 0);
    ck_assert_ptr_null(book);
}
END_TEST

START_TEST(edit_list_same_surname_keeps_order)
{
    list *book = NULL;
    info *a = malloc(sizeof(info)); *a = make_info("A", "A", "1");
    info *b = malloc(sizeof(info)); *b = make_info("B", "B", "2");
    info *c = malloc(sizeof(info)); *c = make_info("C", "C", "3");
    book = add_list(book, a);
    book = add_list(book, b);
    book = add_list(book, c);

    info *n = malloc(sizeof(info));
    *n = make_info("B2", "B", "22");
    book = edit_list(book, 1, n);

    ck_assert_int_eq(list_len(book), 3);
    ck_assert_str_eq(book->elem->surname, "A");
    ck_assert_str_eq(book->next->elem->surname, "B");
    ck_assert_str_eq(book->next->elem->name, "B2");
    ck_assert_str_eq(book->next->elem->phone_number, "22");
    ck_assert(is_sorted(book));
    ck_assert(links_ok(book));
    free_list(book);
}
END_TEST

START_TEST(edit_list_surname_moves_to_head)
{
    list *book = NULL;
    info *a = malloc(sizeof(info)); *a = make_info("A", "B", "1");
    info *b = malloc(sizeof(info)); *b = make_info("B", "C", "2");
    book = add_list(book, a);
    book = add_list(book, b);

    info *n = malloc(sizeof(info));
    *n = make_info("B2", "A", "22");
    book = edit_list(book, 1, n);

    ck_assert_str_eq(book->elem->surname, "A");
    ck_assert_str_eq(book->next->elem->surname, "B");
    ck_assert(is_sorted(book));
    ck_assert(links_ok(book));
    free_list(book);
}
END_TEST

START_TEST(edit_list_surname_moves_to_tail)
{
    list *book = NULL;
    info *a = malloc(sizeof(info)); *a = make_info("A", "A", "1");
    info *b = malloc(sizeof(info)); *b = make_info("B", "B", "2");
    info *c = malloc(sizeof(info)); *c = make_info("C", "C", "3");
    book = add_list(book, a);
    book = add_list(book, b);
    book = add_list(book, c);

    info *n = malloc(sizeof(info));
    *n = make_info("A2", "Z", "11");
    book = edit_list(book, 0, n);

    ck_assert_str_eq(book->elem->surname, "B");
    ck_assert_str_eq(book->next->elem->surname, "C");
    ck_assert_str_eq(book->next->next->elem->surname, "Z");
    ck_assert(is_sorted(book));
    ck_assert(links_ok(book));
    free_list(book);
}
END_TEST

START_TEST(edit_list_surname_moves_to_middle)
{
    list *book = NULL;
    info *a = malloc(sizeof(info)); *a = make_info("A", "A", "1");
    info *b = malloc(sizeof(info)); *b = make_info("B", "B", "2");
    info *c = malloc(sizeof(info)); *c = make_info("C", "C", "3");
    book = add_list(book, a);
    book = add_list(book, b);
    book = add_list(book, c);

    info *n = malloc(sizeof(info));
    *n = make_info("C2", "B", "33");
    book = edit_list(book, 2, n);

    ck_assert(is_sorted(book));
    ck_assert(links_ok(book));
    ck_assert_int_eq(list_len(book), 3);
    ck_assert_str_eq(book->elem->surname, "A");
    ck_assert_str_eq(book->next->elem->surname, "B");
    free_list(book);
}
END_TEST

START_TEST(edit_list_first_elem_changes_head)
{
    list *book = NULL;
    info *a = malloc(sizeof(info)); *a = make_info("A", "A", "1");
    info *b = malloc(sizeof(info)); *b = make_info("B", "B", "2");
    book = add_list(book, a);
    book = add_list(book, b);

    info *n = malloc(sizeof(info));
    *n = make_info("A2", "Z", "11");
    book = edit_list(book, 0, n);

    ck_assert_str_eq(book->elem->surname, "B");
    ck_assert_ptr_null(book->prev);
    ck_assert(is_sorted(book));
    ck_assert(links_ok(book));
    free_list(book);
}
END_TEST

START_TEST(edit_list_out_of_range)
{
    list *book = NULL;
    info *a = malloc(sizeof(info)); *a = make_info("A", "A", "1");
    book = add_list(book, a);

    info *n = malloc(sizeof(info));
    *n = make_info("X", "X", "9");
    book = edit_list(book, 5, n);

    ck_assert_int_eq(list_len(book), 1);
    ck_assert_str_eq(book->elem->surname, "A");
    ck_assert_str_eq(book->elem->name, "A");
    free_list(book);
    free_memory(n);
    free(n);
}
END_TEST

START_TEST(print_book_smoke)
{
    list *book = NULL;
    info *a = malloc(sizeof(info)); *a = make_info("Ivan", "Ivanov", "111");
    info *b = malloc(sizeof(info)); *b = make_info("Petr", "Petrov", "222");
    book = add_list(book, a);
    book = add_list(book, b);

    FILE *out = freopen("test_print.txt", "w", stdout);
    ck_assert_ptr_nonnull(out);
    print_book(book);
    fflush(stdout);
    freopen("/dev/null", "w", stdout);

    FILE *f = fopen("test_print.txt", "r");
    ck_assert_ptr_nonnull(f);
    char buf[1024];
    ck_assert_ptr_nonnull(fgets(buf, sizeof buf, f));
    ck_assert(strstr(buf, "Ivanov") != NULL);
    fgets(buf, sizeof buf, f);
    ck_assert(strstr(buf, "Petrov") != NULL);
    fclose(f);

    free_list(book);
}
END_TEST

Suite *list_suite(void)
{
    Suite *s = suite_create("List");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, add_list_empty);
    tcase_add_test(tc, add_list_sorted_insert);
    tcase_add_test(tc, add_list_insert_head);
    tcase_add_test(tc, add_list_insert_middle_and_tail);

    tcase_add_test(tc, del_list_null);
    tcase_add_test(tc, del_list_single);
    tcase_add_test(tc, del_list_head);
    tcase_add_test(tc, del_list_tail);
    tcase_add_test(tc, del_list_middle);
    tcase_add_test(tc, del_list_out_of_range);
    tcase_add_test(tc, del_list_all);

    tcase_add_test(tc, edit_list_same_surname_keeps_order);
    tcase_add_test(tc, edit_list_surname_moves_to_head);
    tcase_add_test(tc, edit_list_surname_moves_to_tail);
    tcase_add_test(tc, edit_list_surname_moves_to_middle);
    tcase_add_test(tc, edit_list_first_elem_changes_head);
    tcase_add_test(tc, edit_list_out_of_range);

    tcase_add_test(tc, print_book_smoke);

    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    SRunner *sr = srunner_create(list_suite());
    srunner_run_all(sr, CK_NORMAL);
    srunner_free(sr);
    return 0;
}