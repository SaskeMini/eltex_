#include <stdio.h>
#include <math.h>
#define NUM_OF_OPER 4

typedef double (*func)(double, double);

typedef struct {
    char arif;
    func function;
} oper;


double add(double, double);
double sub(double, double);
double mult(double, double);
double dev(double, double);
double input_num();
void clear_stdin();