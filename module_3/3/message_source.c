#include "message.h"

volatile sig_atomic_t stop_flag = 0;

void handle_signal(int sig) {
    if (sig == SIGINT) {
        stop_flag = 1;
    } else if (sig == SIGUSR1) {
        stop_flag = 2;
    }
}

void read_and_write(mqd_t mq_read, mqd_t mq_write) {
    struct mq_attr attr;
    if (mq_getattr(mq_read, &attr) == -1) {
        perror("mq_getattr");
        return;
    }

    char buf[attr.mq_msgsize];

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_signal;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        signal(SIGINT, SIG_IGN);

        while (1) {
            unsigned int prio;
            ssize_t bytes = mq_receive(mq_read, buf, attr.mq_msgsize, &prio);
            if (bytes >= 0) {
                if (prio == EXIT_PRIO) {
                    printf("\nEXIT\n");
                    kill(getppid(), SIGUSR1);
                    break;
                }
                printf("Other: %s\n", buf);
            } else {
                if (errno == EINTR) continue;
                perror("mq_receive");
                break;
            }
        }
        exit(0);
    } else {
        while (!stop_flag) {
            if (fgets(buf, attr.mq_msgsize, stdin) != NULL) {
                buf[strlen(buf) - 1] = '\0';
                if (mq_send(mq_write, buf, strlen(buf) + 1, NORMAL_PRIO) == -1) {
                    perror("mq_send");
                    break;
                }
            } else {
                if (errno == EINTR && stop_flag) {
                    break;
                }
                if (feof(stdin)) {
                    stop_flag = 1;
                    break;
                }
            }
        }

        if (stop_flag == 1) {
            const char *bye = "EXIT";
            mq_send(mq_write, bye, strlen(bye) + 1, EXIT_PRIO);
            printf("\nEXIT\n");
        }

        kill(pid, SIGTERM);
        waitpid(pid, NULL, 0);
    }
}