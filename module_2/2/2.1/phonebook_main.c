#include "phonebook_header.h"

int main(){
    info *book = malloc(sizeof(info) * 4);
    int len_book_for_memory = 4;
    int index_last_elem = 0;

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
            index_last_elem++;
            if (index_last_elem == len_book_for_memory){
                new_memory_for_book(&book, &len_book_for_memory);
            }
            new_memory_for_elem(&book[index_last_elem - 1]);
            add(&book[index_last_elem - 1]);
        }
        else if (input == '2'){
            getchar();
            if (index_last_elem == 0){
                printf("Phonebook is empty\n");
                continue;
            }
            printf("Input index: ");
            int idx = -1;
            if (scanf("%d", &idx) != 1){
                while (getchar() != '\n'){}
                printf("Incorrect index\n");
                continue;
            }
            while (getchar() != '\n'){}
            if (idx < 0 || idx >= index_last_elem){
                printf("Incorrect index\n");
                continue;
            }
            edit(&book[idx]);
        }
        else if (input == '3'){
            getchar();
            if (index_last_elem == 0){
                printf("Phonebook is empty\n");
                continue;
            }
            printf("Input index: ");
            int idx = -1;
            if (scanf("%d", &idx) != 1){
                while (getchar() != '\n'){}
                printf("Incorrect index\n");
                continue;
            }
            while (getchar() != '\n'){}
            if (idx < 0 || idx >= index_last_elem){
                printf("Incorrect index\n");
                continue;
            }
            free_memory(&book[idx]);
            for (int i = idx; i < index_last_elem - 1; i++){
                book[i] = book[i + 1];
            }
            index_last_elem--;
        }
        else if (input == '4'){
            print_book(book, index_last_elem);
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

    for (int i = 0; i < index_last_elem; i++){
        free_memory(&book[i]);
    }
    free(book);
    book = NULL;
    return 0;
}