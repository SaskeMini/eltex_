#include "chmod.h"

int main(){
    R all_flags[8] = {{"---", "000"}, {"--x", "001"}, {"-w-", "010"},
    {"-wx", "011"},{"r--", "100"},{"r-x", "101"},
    {"rw-", "110"},{"rwx", "111"},};
    while (1){
        printf("Enter the command:\n");
        printf("1 - bits\n");
        printf("2 - file stats\n");
        printf("3 - change rights\n");
        printf("4 - exit\n");
        int comm = 0;
        scanf("%d", &comm);
        while (!(comm > 0 && comm < 5)){
            printf("Incorrect\n");
            scanf("%d", &comm);
        }
        if (comm == 4){
            break;
        }
        if (comm == 1){
            char buff[20];
            scanf("%s", &buff);
            if (atoi(buff) == 0 && buff[0] != 0){
                bits_rights(buff, all_flags);
            }
            else if (atoi(buff) != 0){
                printf("%s %s %s\n", all_flags[atoi(buff) / 100].bits, all_flags[atoi(buff) / 10 % 10].bits, all_flags[atoi(buff) % 10].bits);
            }
        }
    }
    return 0;
}

void bits_rights(char buff[], R all[]){
    int rights1 = 0, rights2 = 0, rights3 = 0;
    if (buff[1] == '-'){
        printf("000 000 000\n");
        return;
    }
    int temp_rights = 0;
    int start = buff[0] == '+' ? 1 : 0;
    for (int i = start; i < strlen(buff); i++){
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
            return;
        }
    }
    if (buff[0] == '+' || buff[0] == 'a'){
        rights1 = temp_rights;
        rights2 = temp_rights;
        rights3 = temp_rights;
    }
    else if (buff[0] == 'u'){
        rights1 = temp_rights;
    }
    else if (buff[0] == 'g'){
        rights2 = temp_rights;
    }
    else if (buff[0] == 'o'){
        rights3 = temp_rights;
    }
    else{
        printf("Incorrect\n");
        return;
    }
    printf("%s %s %s\n", all[rights1].bits, all[rights1].bits, all[rights1].bits);
}

void file_rights(int argc, char *argv[], char all[]){

}

void modificate_rights(int argc, char *argv[], char all[]){

}