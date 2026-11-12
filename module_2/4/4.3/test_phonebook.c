#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "phonebook_header.h"

START_TEST(add_tree_all_branches)
{
    tree *book = NULL;
    info *m = malloc(sizeof(info)); new_memory_for_elem(m); strcpy(m->surname, "M");
    info *a = malloc(sizeof(info)); new_memory_for_elem(a); strcpy(a->surname, "A");
    info *z = malloc(sizeof(info)); new_memory_for_elem(z); strcpy(z->surname, "Z");
    info *dup = malloc(sizeof(info)); new_memory_for_elem(dup); strcpy(dup->surname, "M");

    book = add_tree(book, m);
    ck_assert_ptr_nonnull(book);
    ck_assert_ptr_null(book->left);
    ck_assert_ptr_null(book->right);

    book = add_tree(book, a);
    book = add_tree(book, z);
    ck_assert_str_eq(book->left->elem->surname, "A");
    ck_assert_str_eq(book->right->elem->surname, "Z");

    book = add_tree(book, dup);
    ck_assert_int_eq(book->left->elem->surname[0], 'A');
    ck_assert_ptr_null(book->left->left);
    ck_assert_ptr_null(book->left->right);
    ck_assert_str_eq(book->right->elem->surname, "Z");
    ck_assert_ptr_null(book->right->left);
    ck_assert_ptr_null(book->right->right);

    while (book) book = del_tree(book, book->elem->surname);
}
END_TEST

START_TEST(del_tree_all_branches)
{
    tree *book = NULL;
    ck_assert_ptr_null(del_tree(book, "X"));
    ck_assert_ptr_null(del_tree(book, NULL));

    info *b = malloc(sizeof(info)); new_memory_for_elem(b); strcpy(b->surname, "B");
    info *a = malloc(sizeof(info)); new_memory_for_elem(a); strcpy(a->surname, "A");
    info *c = malloc(sizeof(info)); new_memory_for_elem(c); strcpy(c->surname, "C");
    info *d = malloc(sizeof(info)); new_memory_for_elem(d); strcpy(d->surname, "D");
    book = add_tree(book, b);
    book = add_tree(book, a);
    book = add_tree(book, c);
    book = add_tree(book, d);

    book = del_tree(book, "Zzz");
    ck_assert_str_eq(book->elem->surname, "B");
    ck_assert_str_eq(book->left->elem->surname, "A");
    ck_assert_str_eq(book->right->elem->surname, "C");
    ck_assert_str_eq(book->right->right->elem->surname, "D");

    book = del_tree(book, "D");
    ck_assert_str_eq(book->right->elem->surname, "C");
    ck_assert_ptr_null(book->right->right);

    book = del_tree(book, "A");
    ck_assert_str_eq(book->elem->surname, "B");
    ck_assert_ptr_null(book->left);

    book = del_tree(book, "B");
    ck_assert_str_eq(book->elem->surname, "C");
    ck_assert_ptr_null(book->left);
    ck_assert_ptr_null(book->right);

    book = del_tree(book, "C");
    ck_assert_ptr_null(book);

    info *m = malloc(sizeof(info)); new_memory_for_elem(m); strcpy(m->surname, "M");
    info *l = malloc(sizeof(info)); new_memory_for_elem(l); strcpy(l->surname, "L");
    info *r = malloc(sizeof(info)); new_memory_for_elem(r); strcpy(r->surname, "R");
    book = add_tree(book, m);
    book = add_tree(book, l);
    book = add_tree(book, r);
    book = del_tree(book, "M");
    ck_assert_str_eq(book->elem->surname, "R");
    ck_assert_str_eq(book->left->elem->surname, "L");
    ck_assert_ptr_null(book->right);

    while (book) book = del_tree(book, book->elem->surname);
}
END_TEST

START_TEST(edit_tree_all_branches)
{
    info *tmp = malloc(sizeof(info)); new_memory_for_elem(tmp); strcpy(tmp->surname, "X");
    ck_assert_ptr_null(edit_tree(NULL, "X", tmp));

    tree *book = NULL;
    info *a = malloc(sizeof(info)); new_memory_for_elem(a); strcpy(a->surname, "A");
    book = add_tree(book, a);

    book = edit_tree(book, NULL, tmp);
    ck_assert_str_eq(book->elem->surname, "A");
    ck_assert_ptr_null(book->left);
    ck_assert_ptr_null(book->right);

    book = edit_tree(book, "A", NULL);
    ck_assert_str_eq(book->elem->surname, "A");
    ck_assert_ptr_null(book->left);
    ck_assert_ptr_null(book->right);

    info *miss = malloc(sizeof(info)); new_memory_for_elem(miss); strcpy(miss->surname, "Q");
    book = edit_tree(book, "Zzz", miss);
    ck_assert_str_eq(book->elem->surname, "A");
    ck_assert_ptr_null(book->left);
    ck_assert_ptr_null(book->right);

    info *n = malloc(sizeof(info)); new_memory_for_elem(n); strcpy(n->surname, "B");
    book = edit_tree(book, "A", n);
    ck_assert_str_eq(book->elem->surname, "B");
    ck_assert_ptr_null(book->left);
    ck_assert_ptr_null(book->right);

    while (book) book = del_tree(book, book->elem->surname);
    free_memory(tmp); free(tmp);
}
END_TEST

START_TEST(print_book_all_branches)
{
    tree *empty = NULL;
    FILE *out = freopen("test_empty.txt", "w", stdout);
    ck_assert_ptr_nonnull(out);
    print_book(empty);
    fflush(stdout);
    freopen("/dev/null", "w", stdout);
    FILE *f = fopen("test_empty.txt", "r");
    ck_assert_ptr_nonnull(f);
    ck_assert_int_eq(fgetc(f), EOF);
    fclose(f);

    info *a = malloc(sizeof(info)); new_memory_for_elem(a); strcpy(a->surname, "A");
    info *b = malloc(sizeof(info)); new_memory_for_elem(b); strcpy(b->surname, "B");
    tree *book = add_tree(NULL, b);
    book = add_tree(book, a);

    out = freopen("test_print.txt", "w", stdout);
    ck_assert_ptr_nonnull(out);
    print_book(book);
    fflush(stdout);
    freopen("/dev/null", "w", stdout);

    f = fopen("test_print.txt", "r");
    ck_assert_ptr_nonnull(f);
    char buf[256];
    ck_assert_ptr_nonnull(fgets(buf, sizeof buf, f));
    ck_assert(strstr(buf, "A") != NULL);
    ck_assert_ptr_nonnull(fgets(buf, sizeof buf, f));
    ck_assert(strstr(buf, "B") != NULL);
    fclose(f);

    while (book) book = del_tree(book, book->elem->surname);
}
END_TEST

Suite *tree_suite(void)
{
    Suite *s = suite_create("tree");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, add_tree_all_branches);
    tcase_add_test(tc, del_tree_all_branches);
    tcase_add_test(tc, edit_tree_all_branches);
    tcase_add_test(tc, print_book_all_branches);

    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    SRunner *sr = srunner_create(tree_suite());
    srunner_run_all(sr, CK_NORMAL);
    srunner_free(sr);
    return 0;
}