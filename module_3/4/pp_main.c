#include "pp.h"

int main() {
    key_t key = ftok(".", 67);
    if (key == -1) { perror("ftok"); return 0; }

    int check = 0;
    int shm_key = shmget(key, SHM_SIZE, RIGHTS);
    if (shm_key == -1) {
        if (errno == ENOENT) {
            shm_key = shmget(key, SHM_SIZE, RIGHTS | IPC_CREAT);
            check = 1;
        } else {
            perror("shmget");
            return 0;
        }
    }

    int semaf = semget(key, 1, RIGHTS | IPC_CREAT);
    if (semaf == -1) { perror("semget"); return 0; }

    char *shm_addr = (char *)shmat(shm_key, NULL, 0);
    if (shm_addr == (char *)(-1)) { perror("shmat"); return 0; }

    if (check == 1){
        memset(shm_addr, 0, SHM_SIZE);

        union semun arg;
        arg.val = 1;
        semctl(semaf, 0, SETVAL, arg);

        srand(time(NULL));
        int used_memory = 0;
        while(used_memory != SHM_SIZE){
            sem_change(semaf, -1);

            int count_of_elem = 1 + rand() % (MAX_LEN_OF_MASS);
            if ((used_memory + (2 + count_of_elem) * sizeof(int)) > SHM_SIZE){
                count_of_elem = ((SHM_SIZE - used_memory) - 2 * sizeof(int)) / sizeof(int);
            }

            int next_addr = used_memory + (2 + count_of_elem) * sizeof(int);
            int *to_write = (int *)(shm_addr + used_memory);

            used_memory = next_addr;
            if (SHM_SIZE - used_memory <= (int)(3 * sizeof(int))){
                next_addr = 0;
                used_memory = SHM_SIZE;
            }

            to_write[0] = count_of_elem;
            to_write[1] = next_addr;
            for (int i = 0; i < count_of_elem; i++){
                to_write[2 + i] = rand();
            }

            sem_change(semaf, 1);
            sleep(1);
        }

        while (1) {
            sem_change(semaf, -1);
            int all_done = 1;
            int addr = 0;
            while (1) {
                int *check_child = (int *)(shm_addr + addr);
                if (check_child[0] != 0){
                    all_done = 0;
                    break;
                }
                if (check_child[1] == 0) break;
                addr = check_child[1];
            }
            sem_change(semaf, 1);
            if (all_done) break;
            sleep(1);
        }
        shmdt(shm_addr);
        shmctl(shm_key, IPC_RMID, NULL);
        semctl(semaf, 0, IPC_RMID);
    }
    else{
        while(1){
            if (sem_change(semaf, -1) == -1) break;
            int current_addr = 0;

            while (1){
                int *to_read = (int *)(shm_addr + current_addr);
                int count_of_elem = to_read[0];
                int next_data = to_read[1];

                if (count_of_elem > 0){
                    int min = to_read[2], max = to_read[2];
                    for (int i = 0; i < count_of_elem; i++){
                        if (min > to_read[2 + i]) min = to_read[2 + i]; 
                        else if (max < to_read[2 + i]) max = to_read[2 + i];
                    }
                    printf("Min: %d Max: %d\n", min, max);
                    to_read[0] = 0;
                    break;
                }

                if (next_data == 0) break;
                current_addr = next_data;
            }
            sem_change(semaf, 1);
            sleep(2);
        }
        shmdt(shm_addr);
    }
    return 0;
}