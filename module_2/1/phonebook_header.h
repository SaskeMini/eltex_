#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person_info{
    char *name;
    int len_name;
    char *surname;
    int len_surname;
    char *second_name;
    int len_second_name;
    char *work_place;
    int len_work_place;
    char *work_stat;
    int len_work_stat;
    char *phone_number;
    int len_phone_number;
    char *email;
    int len_email;
    char *links;
    int len_links;
} info;

void default_input(char **, int *);
void default_edit(char **, int *);
void edit_phone(char **, int *);
void default_input_plus(char **, int *);
void input_phone(char **, int *, int);
void new_memory_for_elem(info *);
void new_memory_for_info(char **, int *);
void new_memory_for_book(info **, int *);
void free_memory(info *);
void add(info *elem);
void edit(info *elem);
void print_book(info *book, int);