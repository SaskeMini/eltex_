#include "phonebook_header.h"

void add(info *elem){
    printf("Enter to skip\n");
    printf("Input name: ");
    default_input_plus(&elem->name, &elem->len_name);
    printf("Input surname: ");
    default_input_plus(&elem->surname, &elem->len_surname);
    printf("Input second name: ");
    default_input(&elem->second_name, &elem->len_second_name);
    printf("Input work place: ");
    default_input(&elem->work_place, &elem->len_work_place);
    printf("Input work stat: ");
    default_input(&elem->work_stat, &elem->len_work_stat);
    printf("Input phone number: ");
    input_phone(&elem->phone_number, &elem->len_phone_number, 0);
    printf("Input email: ");
    default_input(&elem->email, &elem->len_email);
    printf("Input links: ");
    default_input(&elem->links, &elem->len_links);
}

void input_phone(char **elem, int *len, int iterations){
    char sym = getchar();
    if (sym == '\n'){
        (*elem)[0] = '\0';
        return;
    }
    (*elem)[0] = sym;
    int counter = 1;
    while (sym != '\n'){
        if (counter == *len - 1){
            new_memory_for_info(elem, len);
        }
        sym = getchar();
        if (sym != '\n'){
            (*elem)[counter] = sym;
            counter++;
        }
    }
    (*elem)[counter] = '\0';
    char check_number = 1;
    if (!((*elem)[0] == '+' || ((*elem)[0] >= '0' && (*elem)[0] <= '9'))){
        check_number = 0;
    }
    if ((*elem)[0] == '+' && counter == 1){
        check_number = 0;
    }
    for (int i = 1; i < counter && check_number; i++){
        if (!((*elem)[i] >= '0' && (*elem)[i] <= '9')){
            check_number = 0;
        }
    }
    if (!check_number && iterations < 2){
        iterations++;
        (*elem)[0] = '\0';
        printf("---Incorrect phone number---\n");
        printf("Input phone number: ");
        input_phone(elem, len, iterations);
    }
    else if (!check_number && iterations >= 2){
        (*elem)[0] = '\0';
        printf("Too many attempts. Skip phone number...\n");
        return;
    }
}

void default_input(char **elem, int *len){
    char sym = getchar();
    if (sym == '\n'){
        (*elem)[0] = '\0';
        return;
    }
    (*elem)[0] = sym;
    int counter = 1;
    while (sym != '\n'){
        if (counter == *len - 1){
            new_memory_for_info(elem, len);
        }
        sym = getchar();
        if (sym != '\n'){
            (*elem)[counter] = sym;
            counter++;
        }
    }
    (*elem)[counter] = '\0';
}

void default_input_plus(char **elem, int *len){
    char sym = getchar();
    while (sym == '\n'){
        printf("---Required field---\n");
        printf("Input name: ");
        sym = getchar();
    }
    (*elem)[0] = sym;
    int counter = 1;
    while (sym != '\n'){
        if (counter == *len - 1){
            new_memory_for_info(elem, len);
        }
        sym = getchar();
        if (sym != '\n'){
            (*elem)[counter] = sym;
            counter++;
        }
    }
    (*elem)[counter] = '\0';
}

void edit(info *elem){
    printf("Enter to skip\n");
    printf("Input new name: ");
    default_edit(&elem->name, &elem->len_name);
    printf("Input new surname: ");
    default_edit(&elem->surname, &elem->len_surname);
    printf("Input new second name: ");
    default_edit(&elem->second_name, &elem->len_second_name);
    printf("Input new work place: ");
    default_edit(&elem->work_place, &elem->len_work_place);
    printf("Input new work stat: ");
    default_edit(&elem->work_stat, &elem->len_work_stat);
    printf("Input new phone number: ");
    edit_phone(&elem->phone_number, &elem->len_phone_number);
    printf("Input new email: ");
    default_edit(&elem->email, &elem->len_email);
    printf("Input new links: ");
    default_edit(&elem->links, &elem->len_links);
}

void default_edit(char **elem, int *len){
    char sym = getchar();
    if (sym == '\n'){
        return;
    }
    (*elem)[0] = sym;
    int counter = 1;
    while (sym != '\n'){
        if (counter == *len - 1){
            new_memory_for_info(elem, len);
        }
        sym = getchar();
        if (sym != '\n'){
            (*elem)[counter] = sym;
            counter++;
        }
    }
    (*elem)[counter] = '\0';
}

void edit_phone(char **elem, int *len){
    char sym = getchar();
    if (sym == '\n'){
        return;
    }
    int old_len = strlen(*elem) + 1;
    char old_elem[old_len];
    strcpy(old_elem, *elem);
    (*elem)[0] = sym;
    int counter = 1;
    while (sym != '\n'){
        if (counter == *len - 1){
            new_memory_for_info(elem, len);
        }
        sym = getchar();
        if (sym != '\n'){
            (*elem)[counter] = sym;
            counter++;
        }
    }
    (*elem)[counter] = '\0';
    char check_number = 1;
    if (!((*elem)[0] == '+' || ((*elem)[0] >= '0' && (*elem)[0] <= '9'))){
        check_number = 0;
    }
    if ((*elem)[0] == '+' && counter == 1){
        check_number = 0;
    }
    for (int i = 1; i < counter && check_number; i++){
        if (!((*elem)[i] >= '0' && (*elem)[i] <= '9')){
            check_number = 0;
        }
    }
    if (!check_number){
        printf("---Incorrect phone number---\n");
        strcpy(*elem, old_elem);
    }
}

void new_memory_for_info(char **elem, int *len){
    *len = *len * 2;
    int temp_len = *len;
    *elem = realloc(*elem, (temp_len * sizeof(char)));
}