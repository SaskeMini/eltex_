#include "calc.h"

int main(){
    printf("Input $ to exit\n");
    char check_break = 1;
    while (check_break){
        double a, b;
        printf("Input 1 number:\n");
        a = input_num();
        if (isnan(a)){ break; }
        printf("Input action:\n");
        getchar();
        char action = getchar();
        while (action != '+' && action != '-' && action != '*' && action != '/' && action != '$'){
            printf("Incorrect action. Input action:\n");
            clear_stdin();
            action = getchar();
        }
        if (action == '+'){
            printf("Input 2 number:\n");
            b = input_num();
            isnan(b) ? check_break = 0 : printf("Res: %lf\n", add(a, b));
        }
        else if (action == '-'){
            printf("Input 2 number:\n");
            b = input_num();
            isnan(b) ? check_break = 0 : printf("Res: %lf\n", sub(a, b));
        }
        else if (action == '*'){
            printf("Input 2 number:\n");
            b = input_num();
            isnan(b) ? check_break = 0 : printf("Res: %lf\n", mult(a, b));
        }
        else if (action == '/'){
            printf("Input 2 number:\n");
            b = input_num();
            double res;
            isnan(b) ? check_break = 0 : isnan(res = dev(a, b)) ? printf("\n") : printf("Res: %lf\n", res);
        }
        if (action == '$'){ check_break = 0; }
    }
    printf("End\n");
    return 0;
}