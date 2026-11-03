#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/stat.h>

int bits_rights(char buff[]);
int file_rights(char buff[]);
int modificate_rights(char buff[], int rights);

typedef struct rights{
    char sym[4];
    char bits[4];
} R;