#include "calc2.h"

double sum(double a, double b){
    return a + b;
}

double sub(double a, double b){
    return a - b;
}

double mult(double a, double b){
    return a * b;
}

double div(double a, double b){
    return a / b;
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