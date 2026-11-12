#include "phonebook_header.h"

int main(){
    tree *book = NULL;

    char line[256];
    while (1){
        printf("1 - add\n");
        printf("2 - edit\n");
        printf("3 - del\n");
        printf("4 - show phonebook\n");
        printf("5 - exit\n");
        printf("enter command:\n");
        if (!fgets(line, sizeof line, stdin)) break;
        char input = line[0];

        if (input == '1'){
            info *elem = malloc(sizeof(info));
            new_memory_for_elem(elem);
            add(elem);
            book = add_tree(book, elem);
        }
        else if (input == '2'){
            printf("Input surname: ");
            char search_surname[256];
            if (!fgets(search_surname, sizeof search_surname, stdin)) continue;
            search_surname[strcspn(search_surname, "\n")] = '\0';

            if (!book){
                printf("Phonebook is empty\n");
                continue;
            }

            tree *p = book;
            while (p){
                int cmp = strcmp(search_surname, p->elem->surname);
                if (cmp == 0) break;
                p = (cmp < 0) ? p->left : p->right;
            }
            if (!p){
                printf("Person with surname '%s' not found\n", search_surname);
                continue;
            }

            info *tmp = malloc(sizeof(info));
            new_memory_for_elem(tmp);
            strcpy(tmp->name, p->elem->name); tmp->len_name = p->elem->len_name;
            strcpy(tmp->surname, p->elem->surname); tmp->len_surname = p->elem->len_surname;
            strcpy(tmp->second_name, p->elem->second_name); tmp->len_second_name = p->elem->len_second_name;
            strcpy(tmp->work_place, p->elem->work_place); tmp->len_work_place = p->elem->len_work_place;
            strcpy(tmp->work_stat, p->elem->work_stat); tmp->len_work_stat = p->elem->len_work_stat;
            strcpy(tmp->phone_number, p->elem->phone_number); tmp->len_phone_number = p->elem->len_phone_number;
            strcpy(tmp->email, p->elem->email); tmp->len_email = p->elem->len_email;
            strcpy(tmp->links, p->elem->links); tmp->len_links = p->elem->len_links;
            edit(tmp);
            book = edit_tree(book, search_surname, tmp);
        }
        else if (input == '3'){
            printf("Input surname: ");
            char search_surname[256];
            if (!fgets(search_surname, sizeof search_surname, stdin)) continue;
            search_surname[strcspn(search_surname, "\n")] = '\0';
            book = del_tree(book, search_surname);
        }
        else if (input == '4'){
            printf("----------------------------\n");
            print_book(book);
            printf("----------------------------\n");
        }
        else if (input == '5'){
            break;
        }
        else{
            printf("incorrect input, enter correct command:\n");
        }
    }
    while (book){
        book = del_tree(book, book->elem->surname);
    }
    return 0;
}