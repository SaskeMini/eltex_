#include "phonebook_header.h"

int main(){
    list *book = NULL;

    char input = 0;
    while (1){
        printf("1 - add\n");
        printf("2 - edit\n");
        printf("3 - del\n");
        printf("4 - show phonebook\n");
        printf("5 - exit\n");
        printf("enter command:\n");
        input = getchar();
        if (input == '1'){
            getchar();
            info *elem = malloc(sizeof(info));
            new_memory_for_elem(elem);
            add(elem);
            book = add_list(book, elem);
        }
        else if (input == '2'){
            getchar();
            printf("Input index: ");
            int idx = -1;
            if (scanf("%d", &idx) != 1){
                while (getchar() != '\n'){}
                printf("Incorrect index\n");
                continue;
            }
            while (getchar() != '\n'){}

            if (idx < 0 || !book){
                printf("Index out of range\n");
                continue;
            }
            list *p = book;
            for (int i = 0; i < idx; i++){
                if (!p->next){ p = NULL; break; }
                p = p->next;
            }
            if (!p){
                printf("Index out of range\n");
                continue;
            }

            info tmp;
            new_memory_for_elem(&tmp);
            strcpy(tmp.name, p->elem->name); tmp.len_name = p->elem->len_name;
            strcpy(tmp.surname, p->elem->surname); tmp.len_surname = p->elem->len_surname;
            strcpy(tmp.second_name, p->elem->second_name); tmp.len_second_name = p->elem->len_second_name;
            strcpy(tmp.work_place, p->elem->work_place); tmp.len_work_place = p->elem->len_work_place;
            strcpy(tmp.work_stat, p->elem->work_stat); tmp.len_work_stat = p->elem->len_work_stat;
            strcpy(tmp.phone_number, p->elem->phone_number); tmp.len_phone_number = p->elem->len_phone_number;
            strcpy(tmp.email, p->elem->email); tmp.len_email = p->elem->len_email;
            strcpy(tmp.links, p->elem->links); tmp.len_links = p->elem->len_links;
            edit(&tmp);
            book = edit_list(book, idx, &tmp);
        }
        else if (input == '3'){
            getchar();
            printf("Input index: ");
            int idx = -1;
            if (scanf("%d", &idx) != 1){
                while (getchar() != '\n'){}
                printf("Incorrect index\n");
                continue;
            }
            while (getchar() != '\n'){}
            book = del_list(book, idx);
        }
        else if (input == '4'){
            print_book(book);
            getchar();
        }
        else if (input == '5'){
            getchar();
            break;
        }
        else{
            getchar();
            printf("incorrect input, enter correct command:\n");
        }
    }
    while(book){
        book = del_list(book, 0);
    }
    free(book);
    book = NULL;
    return 0;
}