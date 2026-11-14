#include "copy_files.h"

int main(int argc, char *argv[]){
    int opt;
    char *pipe_name = NULL;
    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt) {
            case 'p':
                pipe_name = optarg;
                break;
            case '?':
                fprintf(stderr, "Incorrect input\n");
                return 0;
        }
    }
    // pipe_name ? process_fifo(argv, pipe_name, argc) : process_pipe(argv, argc);
    process_fifo(argv, pipe_name, argc);
    return 0;
}

void process_fifo(char* argv[], char* pipename, int argc){
    mkfifo(pipename, 0666);
    pid_t pid;
    switch(pid = fork()) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);

        case 0: {
            int fd2 = open(pipename, O_WRONLY);
            if (fd2 == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            ssize_t check = write(fd2, "Ready\n", strlen("Ready\n"));
            if (check != strlen("Ready\n")){
                perror("write");
                exit(EXIT_FAILURE);
            }
            close(fd2);
            int fd = open(pipename, O_RDONLY);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            char buffer[128];
            char name[128];
            char out_name[160];
            long long size;
            int out_fd;

            while (1) {
                ssize_t hlen = 0;
                while (hlen < (ssize_t)sizeof(buffer) - 1) {
                    ssize_t r = read(fd, buffer + hlen, 1);
                    if (r == -1) { perror("read"); exit(EXIT_FAILURE); }
                    if (r == 0) { close(fd); _exit(EXIT_SUCCESS); }   // EOF
                    if (buffer[hlen++] == '\n') break;
                }
                buffer[hlen] = '\0';

                if (strncmp(buffer, "Close", 5) == 0) {
                    close(fd);
                    _exit(EXIT_SUCCESS);
                }

                if (sscanf(buffer, "%127s %lld", name, &size) != 2) {
                    fprintf(stderr, "bad header\n");
                    _exit(EXIT_FAILURE);
                }

                snprintf(out_name, sizeof(out_name), "%s.copy", name);
                out_fd = open(out_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (out_fd == -1) { perror("open"); _exit(EXIT_FAILURE); }

                long long left = size;
                while (left > 0) {
                    ssize_t want = left < (long long)sizeof(buffer) ? (ssize_t)left : (ssize_t)sizeof(buffer);
                    ssize_t r = read(fd, buffer, want);
                    if (r == -1) { perror("read"); _exit(EXIT_FAILURE); }
                    if (r == 0) break;
                    ssize_t w = 0;
                    while (w < r) {
                        ssize_t k = write(out_fd, buffer + w, r - w);
                        if (k == -1) { perror("write"); _exit(EXIT_FAILURE); }
                        w += k;
                    }
                    left -= r;
                }
                close(out_fd);
            }
        }

        default: {
            char buffer[128];
            ssize_t check;
            int fd = open(pipename, O_RDONLY);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }

            while ((check = read(fd, buffer, 128)) > 0) {}
            if (check == -1){
                perror("read");
                exit(EXIT_FAILURE);
            }
            close(fd);

            int fd2 = open(pipename, O_WRONLY);
            if (fd2 == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }

            if (optind < argc) {
                for (int i = optind; i < argc; i++) {
                    struct stat st;
                    int fdf = open(argv[i], O_RDONLY);
                    if (fdf == -1) {
                        fprintf(stderr, "Incorrect file\n");
                        continue;
                    }

                    fstat(fdf, &st);
                    int len_first_msg = sprintf(buffer, "%s %lld\n", argv[i], (long long)st.st_size);
                    check = write(fd2, buffer, len_first_msg);
                    if (check != len_first_msg){
                        perror("write");
                        exit(EXIT_FAILURE);
                    }
                    char buf[128];
                    ssize_t n;
                    while ((n = read(fdf, buf, sizeof(buf))) > 0) {
                        ssize_t nn = write(fd2, buf, n);
                        if (nn == -1){
                            perror("write");
                            exit(EXIT_FAILURE);
                        }
                    }
                    if (n == -1){
                        perror("read");
                        exit(EXIT_FAILURE);
                    }
                    close(fdf);
                }
            }
            ssize_t nn = write(fd2, "Close\n", strlen("Close\n"));
            if (nn == -1){
                perror("write");
                exit(EXIT_FAILURE);
            }
            close(fd2);
            wait(NULL);
            exit(EXIT_SUCCESS);
        }
    }
}

// void process_pipe(char* argv[], int argc){

// }