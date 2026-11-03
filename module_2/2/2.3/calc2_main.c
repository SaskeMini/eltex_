#include "calc2.h"

int main(){
    oper all[4] = {{'+', sum}, {'-', sub}, {'*', mult}, {'/', div}};
    printf("Input $ to exit\n");
    double a;
    printf("Input 1 number:\n");
    a = input_num();
    if (isnan(a)){ return 0; }
    getchar();
    while (1){
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
            if (isnan(b)){ break; }
            if (b == 0 && op == div){ printf("Div by zero\n"); clear_stdin();}
            else{
                a = op(a, b);
                printf("Res: %lf\n", a);
                getchar();
            }
        }
        else{
            printf("Incorrect action\n");
            clear_stdin();
        }
    }
    printf("End\n");
    return 0;
}