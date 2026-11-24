#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>

#define RIGHTS 0666
#define SHM_SIZE 256
#define MAX_LEN_OF_MASS 8

#define SHM_NAME "/my_posix_shm"
#define SEM_NAME "/my_posix_sem"