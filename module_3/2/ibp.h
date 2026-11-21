#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define OPEN_H "open"
#define CLOSE_H "close"
#define READ_H "read"
#define WRITE_H "write"
#define MSGGET_H "msgget"
#define RIGHTS 0666
#define MSGG_SIZE 128

typedef struct pid_and_theme_for_sub {
    pid_t pid;
    char theme[64];
} themes;

struct msg_buffer {
    long mtype;
    char mtext[MSGG_SIZE];
};

extern volatile sig_atomic_t is_running;

void handle_shutdown(int sig);
void shutdown_broker(int msqid, themes *subs, int len_subs, pid_t *publs, int len_publs);
void check_handle(ssize_t handl, char messg[]);
void Broker();
void Publisher(char *argv[]);
void Subscriber(int argc, char *argv[]);
