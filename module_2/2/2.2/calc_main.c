#include "calc.h"

int main(){
    printf("Input $ to exit\n");
    while (1){
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
        printf("Input 2 number:\n");
        b = input_num();
        if (isnan(b)){ break; }
        if (action == '+'){
            printf("Res: %lf\n", sum(a, b));
        }
        else if (action == '-'){
            printf("Res: %lf\n", sub(a, b));
        }
        else if (action == '*'){
            printf("Res: %lf\n", mult(a, b));
        }
        else if (action == '/'){
            if (b == 0){ printf("Div by zero\n"); }
            else { printf("Res: %lf\n", div(a, b)); }
        }
        if (action == '$'){ break; }
    }
    printf("End\n");
    return 0;
}