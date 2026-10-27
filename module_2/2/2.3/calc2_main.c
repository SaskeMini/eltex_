#include "calc2.h"

int main(){
    oper all[4] = {{'+', add}, {'-', sub}, {'*', mult}, {'/', dev}};
    printf("Input $ to exit\n");
    char check_break = 1;
    double a;
    printf("Input 1 number:\n");
    a = input_num();
    if (isnan(a)){ check_break = 0; }
    getchar();
    while (check_break){
        double b;
        printf("Input action:\n");
        func op = NULL;
        char action = getchar();
        if (action == '$'){ break; }
        for (int i = 0; i < NUM_OF_OPER; i++){
            if (all[i].arif == action){ op = all[i].function; }
        }
        if (op){
            printf("Input 2 number:\n");
            b = input_num();
            double res;
            isnan(b) ? check_break = 0 : isnan(res = op(a, b)) ? printf("\n") : printf("Res: %lf\n", res);
            a = res;
            getchar();
        }
        else{
            printf("Incorrect action\n");
            clear_stdin();
        }
    }
    printf("End\n");
    return 0;
}