#include <stdio.h>
#include <stdlib.h> 
#include <sys/stat.h>
#include <sys/stat.h>

void bits_rights(int argc, char *argv[], char all[]);
void file_rights(int argc, char *argv[], char all[]);
void modificate_rights(int argc, char *argv[], char all[]);

typedef struct rights{
    char sym[4];
    char bits[4];
} R;