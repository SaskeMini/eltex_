#include "net.h"

long long int check_ip(char* str){
    if (strlen(str) < 7){
        return -1;
    }
    long long int res = 0;
    int check_len = 0, number_of_part = 3;
    int part_of_ip[4] = {0, 0, 0};
    for (size_t i = 0; i < strlen(str); i++){
        if ((str[i] == '.' && check_len <= 3) || (i == strlen(str) - 1 && 
        check_len < 3 && str[i] >= '0' && str[i] <= '9')){
            if (i == strlen(str) - 1 && check_len < 3 && str[i] >= '0' && str[i] <= '9'){
                part_of_ip[check_len] = (int)(str[i] - 48);
                check_len++;
            }
            long long int temp;
            if (check_len == 3){
                temp = part_of_ip[0] * 100 + part_of_ip[1] * 10 + part_of_ip[2];
            }
            else if (check_len == 2){
                temp = part_of_ip[0] * 10 + part_of_ip[1];
            }
            else if (check_len == 1){
                temp = part_of_ip[0];
            }
            else{
                res = -1;
                break;
            }
            if (temp > 255){
                res = -1;
                break;
            } 
            for (int j = 0; j < number_of_part; j++){
                temp *= 256;
            }
            number_of_part--;
            res += temp;
            part_of_ip[0] = 0; part_of_ip[1] = 0; part_of_ip[2] = 0;
            check_len = 0;
        }
        else if (str[i] >= '0' && str[i] <= '9' && check_len != 3){
            part_of_ip[check_len] = (int)(str[i] - 48);
            check_len++;
        }
        else{
            res = -1;
            break;
        }
    }
    return res;
}

long long int new_random(){
    long long int res = 0;
    for (int i = 0; i < 4; i++){
        long long int random_num = (rand() % 256) * (long long int)pow(256, i);
        res += random_num;
    }
    return res;
}