#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dlfcn.h>
#define NUM_OF_OPER 4

typedef double (*func)(double, double);

typedef struct {
    char arif;
    func function;
} oper;

double input_num();
void clear_stdin();