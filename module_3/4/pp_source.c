#include "pp.h"

int sem_change(int semaf, int op) {
    struct sembuf sb = {0, op, 0};
    if (semop(semaf, &sb, 1) == -1) {
        if (errno == EIDRM || errno == EINVAL) {
            return -1;
        }
        perror("semop");
        exit(1);
    }
    return 0;
}