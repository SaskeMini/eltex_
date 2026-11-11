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

int modificate_rights(char buff[], int rights) {
    int u = 0, g = 0, o = 0;
    size_t i = 0;
    while (buff[i] != '\0' && buff[i] != '+' && buff[i] != '-') {
        if (buff[i] == 'u') u = 1;
        else if (buff[i] == 'g') g = 1;
        else if (buff[i] == 'o') o = 1;
        else if (buff[i] == 'a') u = g = o = 1;
        else {
            printf("Incorrect\n");
            return rights;
        }
        i++;
    }
    if (buff[i] == '\0' || buff[i + 1] == '\0') {
        printf("Incorrect\n");
        return rights;
    }
    if (i == 0) { u = g = o = 1; }

    char op = buff[i];
    int temp_rights = 0;

    for (size_t j = i + 1; j < strlen(buff); j++) {
        if (buff[j] == 'r') {
            if (op == '-') {
                if (u && rights / 100 >= 4) temp_rights -= 400;
                if (g && rights / 10 % 10 >= 4) temp_rights -= 40;
                if (o && rights % 10 >= 4) temp_rights -= 4;
            } else if (op == '+') {
                if (u && rights / 100 < 4) temp_rights += 400;
                if (g && rights / 10 % 10 < 4) temp_rights += 40;
                if (o && rights % 10 < 4) temp_rights += 4;
            }
        } else if (buff[j] == 'w') {
            if (op == '-') {
                if (u && (rights / 100 == 2 || rights / 100 == 3 || rights / 100 == 6 || rights / 100 == 7)) temp_rights -= 200;
                if (g && (rights / 10 % 10 == 2 || rights / 10 % 10 == 3 || rights / 10 % 10 == 6 || rights / 10 % 10 == 7)) temp_rights -= 20;
                if (o && (rights % 10 == 2 || rights % 10 == 3 || rights % 10 == 6 || rights % 10 == 7)) temp_rights -= 2;
            } else if (op == '+') {
                if (u && (rights / 100 != 2 && rights / 100 != 3 && rights / 100 != 6 && rights / 100 != 7)) temp_rights += 200;
                if (g && (rights / 10 % 10 != 2 && rights / 10 % 10 != 3 && rights / 10 % 10 != 6 && rights / 10 % 10 != 7)) temp_rights += 20;
                if (o && (rights % 10 != 2 && rights % 10 != 3 && rights % 10 != 6 && rights % 10 != 7)) temp_rights += 2;
            }
        } else if (buff[j] == 'x') {
            if (op == '-') {
                if (u && rights / 100 % 2 == 1) temp_rights -= 100;
                if (g && rights / 10 % 10 % 2 == 1) temp_rights -= 10;
                if (o && rights % 10 % 2 == 1) temp_rights -= 1;
            } else if (op == '+') {
                if (u && rights / 100 % 2 == 0) temp_rights += 100;
                if (g && rights / 10 % 10 % 2 == 0) temp_rights += 10;
                if (o && rights % 10 % 2 == 0) temp_rights += 1;
            }
        } else {
            printf("Incorrect\n");
            return rights;
        }
    }

    return rights + temp_rights;
}