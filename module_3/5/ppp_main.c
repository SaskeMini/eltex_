#include "ppp.h"

int main() {
    int check = 0;

    int fd = shm_open(SHM_NAME, O_RDWR, RIGHTS);
    if (fd == -1) {
        if (errno == ENOENT) {
            fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, RIGHTS);
            if (fd == -1) { perror("shm_open"); return 0; }
            check = 1;
        } else {
            perror("shm_open");
            return 0;
        }
    }

    sem_t *semaf = sem_open(SEM_NAME, O_CREAT, RIGHTS, 1);
    if (semaf == SEM_FAILED) { perror("sem_open"); close(fd); return 0; }

    if (check == 1) {
        ftruncate(fd, sizeof(int) + SHM_SIZE);

        srand(time(NULL));
        int used_memory = 0;

        while (used_memory != SHM_SIZE) {
            sem_wait(semaf);

            int count_of_elem = 1 + rand() % (MAX_LEN_OF_MASS);
            if ((used_memory + (2 + count_of_elem) * sizeof(int)) > SHM_SIZE) {
                count_of_elem = ((SHM_SIZE - used_memory) - 2 * sizeof(int)) / sizeof(int);
            }

            int next_addr = used_memory + (2 + count_of_elem) * sizeof(int);
            int write_pos = used_memory;

            used_memory = next_addr;
            if (SHM_SIZE - used_memory <= (int)(3 * sizeof(int))) {
                next_addr = 0;
                used_memory = SHM_SIZE;
            }

            int block[2 + MAX_LEN_OF_MASS];
            block[0] = count_of_elem;
            block[1] = next_addr;
            for (int i = 0; i < count_of_elem; i++) {
                block[2 + i] = rand();
            }

            pwrite(fd, block, (2 + count_of_elem) * sizeof(int), sizeof(int) + write_pos);

            sem_post(semaf);
            sleep(1);
        }

        while (1) {
            sem_wait(semaf);
            int all_done = 1;
            int addr = 0;

            while (1) {
                int header[2];
                pread(fd, header, sizeof(header), sizeof(int) + addr);

                if (header[0] != 0) {
                    all_done = 0;
                    break;
                }
                if (header[1] == 0) break;
                addr = header[1];
            }

            if (all_done) {
                int finished = 1;
                pwrite(fd, &finished, sizeof(int), 0);
                sem_post(semaf);
                break;
            }

            sem_post(semaf);
            sleep(1);
        }
        shm_unlink(SHM_NAME);
        sem_unlink(SEM_NAME);
    }
    else {
        while (1) {
            sem_wait(semaf);

            int finished = 0;
            if (pread(fd, &finished, sizeof(int), 0) <= 0 || finished == 1) {
                sem_post(semaf);
                break;
            }

            int current_addr = 0;
            while (1) {
                int header[2];
                pread(fd, header, sizeof(header), sizeof(int) + current_addr);

                int count_of_elem = header[0];
                int next_data = header[1];

                if (count_of_elem > 0) {
                    int nums[MAX_LEN_OF_MASS];
                    pread(fd, nums, count_of_elem * sizeof(int), sizeof(int) + current_addr + sizeof(header));

                    int min = nums[0], max = nums[0];
                    for (int i = 0; i < count_of_elem; i++) {
                        if (min > nums[i]) min = nums[i];
                        if (max < nums[i]) max = nums[i];
                    }
                    printf("Min: %d Max: %d\n", min, max);

                    int zero = 0;
                    pwrite(fd, &zero, sizeof(int), sizeof(int) + current_addr);
                    break;
                }

                if (next_data == 0) break;
                current_addr = next_data;
            }

            sem_post(semaf);
            sleep(2);
        }
    }
    close(fd);
    sem_close(semaf);
    return 0;
}