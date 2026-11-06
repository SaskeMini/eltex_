#include "calc2.h"

int main(){
    void *handle1, *handle2;
    handle1 = dlopen("sumsub.so", RTLD_LAZY);
    if (!handle1){
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(1);
    }
    handle2 = dlopen("multdiv.so", RTLD_LAZY);
    if (!handle2){
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(1);
    }
    func mult, sum, sub, div;
    mult = (func) dlsym(handle2, "mult");
    sum = (func) dlsym(handle1, "sum");
    sub = (func) dlsym(handle1, "sub");
    div = (func) dlsym(handle2, "div");
    if (!mult || !sum || !sub || !div){
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle1);
        dlclose(handle2);
        exit(1);
    }
    oper all[4] = {{'+', sum}, {'-', sub}, {'*', mult}, {'/', div}};
    printf("Input $ to exit\n");
    double a;
    printf("Input 1 number:\n");
    a = input_num();
    if (isnan(a)){                 
        dlclose(handle1);
        dlclose(handle2);
        return 0; 
    }
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
            if (isnan(b)){ 
                dlclose(handle1);
                dlclose(handle2);
                break;
            }
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

double input_num(){
    char check_exit;
    double res;
    for (;;){
        check_exit = getchar();
        if (check_exit == '$'){ return NAN; }
        ungetc(check_exit, stdin);
        if (scanf("%lf", &res) < 1) { 
            printf("Incorrect number. Input number:\n");
            clear_stdin();
        }
        else { return res; }
    }
}

void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n') {}
}