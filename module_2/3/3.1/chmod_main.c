#include "chmod.h"

int main(){
    R all_flags[8] = {{"---", "000"}, {"--x", "001"}, {"-w-", "010"},
    {"-wx", "011"},{"r--", "100"},{"r-x", "101"},
    {"rw-", "110"},{"rwx", "111"}};
    int rights = 0;
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
        else if (comm == 1){
            char buff[20];
            scanf("%s", buff);
            if (atoi(buff) == 0 && buff[0] != 0){
                rights = bits_rights(buff);
                printf("%s %s %s\n", all_flags[rights / 100].bits, all_flags[rights / 10 % 10].bits, all_flags[rights % 10].bits);
            }
            else if (atoi(buff) != 0){
                rights = atoi(buff);
                printf("%s %s %s\n", all_flags[atoi(buff) / 100].bits, all_flags[atoi(buff) / 10 % 10].bits, all_flags[atoi(buff) % 10].bits);
            }
        }
        else if (comm == 2){
            char buff[50];
            scanf("%s", buff);
            rights = file_rights(buff);
            printf("%s %s %s\n", all_flags[rights / 100].bits, all_flags[rights / 10 % 10].bits, all_flags[rights % 10].bits);
        }
        else if (comm == 3){
            printf("Current rights: %d\n", rights);
            char buff[20];
            scanf("%s", buff);
            if (atoi(buff) == 0 && buff[0] != 0){
                rights = modificate_rights(buff, rights);
                printf("%s %s %s\n", all_flags[rights / 100].bits, all_flags[rights / 10 % 10].bits, all_flags[rights % 10].bits);
            }
            else if (atoi(buff) != 0){
                rights = atoi(buff);
                printf("%s %s %s\n", all_flags[atoi(buff) / 100].bits, all_flags[atoi(buff) / 10 % 10].bits, all_flags[atoi(buff) % 10].bits);
            }
        }

    }
    return 0;
}

