#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define RIGHTS 0666
#define SHM_SIZE 256
#define MAX_LEN_OF_MASS 8
#define MSG_COUNT 3  

#define SEM_WRITE 0
#define SEM_READ  1

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int sem_change(int, int);