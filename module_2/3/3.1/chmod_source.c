#include "chmod.h"

int bits_rights(char buff[]){
    int rights = 0;
    if (buff[1] == '-' || buff[0] == '-'){
        printf("000 000 000\n");
        return rights;
    }
    int temp_rights = 0;
    int start = buff[0] == '+' ? 1 : 2;
    for (size_t i = start; i < strlen(buff); i++){
        if (buff[i] == 'r'){
            temp_rights += 4;
        }
        else if (buff[i] == 'w'){
            temp_rights += 2;
        }
        else if (buff[i] == 'x'){
            temp_rights += 1;
        }
        else{
            printf("Incorrect\n");
            return rights;
        }
    }
    if (buff[0] == '+' || buff[0] == 'a'){
        rights += temp_rights * 100;
        rights += temp_rights * 10;
        rights += temp_rights;
    }
    else if (buff[0] == 'u'){
        rights += temp_rights * 100;
    }
    else if (buff[0] == 'g'){
        rights += temp_rights * 10;
    }
    else if (buff[0] == 'o'){
        rights = temp_rights;
    }
    else{
        printf("Incorrect\n");
        return rights;
    }
    return rights;
}

int file_rights(char buff[]){
    struct stat file_info;

    if (stat(buff, &file_info) != 0) {
        printf("Incorrect file");
        return 0;
    }
    return file_info.st_mode & 0777;
}

int modificate_rights(char buff[], int rights){
    int start = buff[0] == '+' || buff[0] == '-' ? 1 : 2;
    int temp_rights = 0;
    for (size_t i = start; i < strlen(buff); i++){
        if (buff[i] == 'r'){
            if (buff[0] == '-'){
                if (rights / 100 >= 4){ temp_rights -= 400; }
                if (rights / 10 % 10 >= 4){ temp_rights -= 40; }
                if (rights % 10 >= 4){ temp_rights -= 4; }
            }
            else if (buff[1] == '-'){
                if (buff[0] == 'u'){
                    if (rights / 100 >= 4){ temp_rights -= 400; }
                }
                if (buff[0] == 'g'){
                    if (rights / 10 % 10 >= 4){ temp_rights -= 40; }
                }
                if (buff[0] == 'o'){
                    if (rights % 10 >= 4){ temp_rights -= 4; }
                }
            }
            else if (buff[0] == '+'){
                if (rights / 100 < 4){ temp_rights += 400; }
                if (rights / 10 % 10 < 4){ temp_rights += 40; }
                if (rights % 10 < 4){ temp_rights += 4; }
            }
            else if (buff[1] == '+'){
                if (buff[0] == 'u'){
                    if (rights / 100 < 4){ temp_rights += 400; }
                }
                if (buff[0] == 'g'){
                    if (rights / 10 % 10 < 4){ temp_rights += 40; }
                }
                if (buff[0] == 'o'){
                    if (rights % 10 < 4){ temp_rights += 4; }
                }
            }
        }
        else if (buff[i] == 'w'){
            if (buff[0] == '-'){
                if (rights / 100 == 2 || rights / 100 == 3 || rights / 100 == 6 || rights / 100 == 7){ temp_rights -= 200; }
                if (rights / 10 % 10 == 2 || rights / 10 % 10 == 3 || rights / 10 % 10 == 6 || rights / 10 % 10 == 7){ temp_rights -= 20; }
                if (rights % 10 == 2 || rights % 10 == 3 || rights % 10 == 6 || rights % 10 == 7){ temp_rights -= 2; }
            }
            else if (buff[1] == '-'){
                if (buff[0] == 'u'){
                    if (rights / 100 == 2 || rights / 100 == 3 || rights / 100 == 6 || rights / 100 == 7){ temp_rights -= 200; }
                }
                if (buff[0] == 'g'){
                    if (rights / 10 % 10 == 2 || rights / 10 % 10 == 3 || rights / 10 % 10 == 6 || rights / 10 % 10 == 7){ temp_rights -= 20; }
                }
                if (buff[0] == 'o'){
                    if (rights % 10 == 2 || rights % 10 == 3 || rights % 10 == 6 || rights % 10 == 7){ temp_rights -= 2; }
                }
            }
            else if (buff[0] == '+'){
                if (rights / 100 != 2 && rights / 100 != 3 && rights / 100 != 6 && rights / 100 != 7){ temp_rights += 200; }
                if (rights / 10 % 10 != 2 && rights / 10 % 10 != 3 && rights / 10 % 10 != 6 && rights / 10 % 10 != 7){ temp_rights += 20; }
                if (rights % 10 != 2 && rights % 10 != 3 && rights % 10 != 6 && rights % 10 != 7){ temp_rights += 2; }
            }
            else if (buff[1] == '+'){
                if (buff[0] == 'u'){
                    if (rights / 100 != 2 && rights / 100 != 3 && rights / 100 != 6 && rights / 100 != 7){ temp_rights += 200; }
                }
                if (buff[0] == 'g'){
                    if (rights / 10 % 10 != 2 && rights / 10 % 10 != 3 && rights / 10 % 10 != 6 && rights / 10 % 10 != 7){ temp_rights += 20; }
                }
                if (buff[0] == 'o'){
                    if (rights % 10 != 2 && rights % 10 != 3 && rights % 10 != 6 && rights % 10 != 7){ temp_rights += 2; }
                }
            }
        }
        else if (buff[i] == 'x'){
            if (buff[0] == '-'){
                if (rights / 100 % 2 == 1){ temp_rights -= 100; }
                if (rights / 10 % 10 % 2 == 1){ temp_rights -= 10; }
                if (rights % 10 % 2 == 1){ temp_rights -= 1; }
            }
            else if (buff[1] == '-'){
                if (buff[0] == 'u'){
                    if (rights / 100 % 2 == 1){ temp_rights -= 100; }
                }
                if (buff[0] == 'g'){
                    if (rights / 10 % 10 % 2 == 1){ temp_rights -= 10; }
                }
                if (buff[0] == 'o'){
                    if (rights % 10 % 2 == 1){ temp_rights -= 1; }
                }
            }
            else if (buff[0] == '+'){
                if (rights / 100 % 2 == 0){ temp_rights += 100; }
                if (rights / 10 % 10 % 2 == 0){ temp_rights += 10; }
                if (rights % 10 % 2 == 0){ temp_rights += 1; }
            }
            else if (buff[1] == '+'){
                if (buff[0] == 'u'){
                    if (rights / 100 % 2 == 0){ temp_rights += 100; }
                }
                if (buff[0] == 'g'){
                    if (rights / 10 % 10 % 2 == 0){ temp_rights += 10; }
                }
                if (buff[0] == 'o'){
                    if (rights % 10 % 2 == 0){ temp_rights += 1; }
                }
            }
        }
        else{
            printf("Incorrect\n");
            return rights;
        }
    }
    return rights + temp_rights;
}