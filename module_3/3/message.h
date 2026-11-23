#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <mqueue.h>

#define RIGHTS 0666
#define NORMAL_PRIO 1
#define EXIT_PRIO 67

void read_and_write(mqd_t mq1, mqd_t mq2);
void handle_signal(int sig);