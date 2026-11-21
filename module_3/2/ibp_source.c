#include "ibp.h"

volatile sig_atomic_t is_running = 1;

void check_handle(ssize_t handl, char messg[]) {
    if (handl == -1) {
        perror(messg);
        exit(EXIT_FAILURE);
    }
}

void handle_shutdown(int sig) {
    (void)sig;
    is_running = 0;
}

void shutdown_broker(int msqid, themes *subs, int len_subs, pid_t *publs, int len_publs) {
    for (int i = 0; i < len_subs; i++) {
        if (subs[i].pid > 0) kill(subs[i].pid, SIGINT);
    }
    for (int i = 0; i < len_publs; i++) {
        if (publs[i] > 0) kill(publs[i], SIGINT);
    }

    struct msqid_ds q_stat;
    for (int sec = 0; sec < 5; sec++) {
        if (msgctl(msqid, IPC_STAT, &q_stat) == -1 || q_stat.msg_qnum == 0) {
            break;
        }
        sleep(1);
    }

    msgctl(msqid, IPC_RMID, NULL);
}
void Broker() {
    int fd_init = open("key.txt", O_WRONLY | O_CREAT, RIGHTS);
    check_handle(fd_init, OPEN_H);
    close(fd_init);

    key_t key = ftok("key.txt", 'E');
    check_handle((ssize_t)key, "ftok");

    int msqid;
    check_handle(msqid = msgget(key, IPC_CREAT | RIGHTS), MSGGET_H);

    ssize_t h, w;
    check_handle(h = open("key.txt", O_WRONLY | O_TRUNC, RIGHTS), OPEN_H);
    check_handle(w = write(h, &key, sizeof(key_t)), WRITE_H);
    close(h);

    struct sigaction sa = {0};
    sa.sa_handler = handle_shutdown;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    int len_subs = 0, len_publs = 0;
    themes subs[100];
    pid_t publs[100];

    while (is_running) {
        struct msg_buffer message;
        ssize_t bytes_read = msgrcv(msqid, &message, sizeof(message.mtext), 1, 0);
        if (bytes_read == -1) {
            if (errno == EINTR) continue;
            perror("msgrcv");
            break;
        }

        char action[MSGG_SIZE / 4] = {0};
        char topic[MSGG_SIZE / 2] = {0};
        char payload[MSGG_SIZE] = {0};
        long pid_val = 0;

        char *newline = strchr(message.mtext, '\n');
        if (newline != NULL) {
            *newline = '\0';
            strncpy(payload, newline + 1, sizeof(payload) - 1);
        }

        if (sscanf(message.mtext, "%31[^,],%ld,%63s", action, &pid_val, topic) < 2) {
            continue;
        }
        pid_t sender_pid = (pid_t)pid_val;

        if (strcmp(action, "send") == 0) {
            int known_pub = 0;
            for (int i = 0; i < len_publs; i++) {
                if (publs[i] == sender_pid) {
                    known_pub = 1;
                    break;
                }
            }
            if (!known_pub && len_publs < 100) {
                publs[len_publs++] = sender_pid;
            }

            for (int i = 0; i < len_subs; i++) {
                if (strcmp(subs[i].theme, topic) == 0) {
                    struct msg_buffer out_msg;
                    out_msg.mtype = subs[i].pid;
                    snprintf(out_msg.mtext, MSGG_SIZE, "[%s]: %.55s", topic, payload);
                    if (msgsnd(msqid, &out_msg, strlen(out_msg.mtext) + 1, 0) == -1) {
                        perror("msgsnd to sub");
                    }
                }
            }

        } else if (strcmp(action, "subscribe") == 0) {
            if (len_subs < 100) {
                subs[len_subs].pid = sender_pid;
                strncpy(subs[len_subs].theme, topic, sizeof(subs[len_subs].theme) - 1);
                subs[len_subs].theme[sizeof(subs[len_subs].theme) - 1] = '\0';
                len_subs++;
            }

        } else if (strcmp(action, "unsubscribe") == 0) {
            int write_idx = 0;
            for (int read_idx = 0; read_idx < len_subs; read_idx++) {
                if (subs[read_idx].pid != sender_pid) {
                    subs[write_idx++] = subs[read_idx];
                }
            }
            len_subs = write_idx;
        }
    }

    shutdown_broker(msqid, subs, len_subs, publs, len_publs);
}

void Publisher(char *argv[]) {
    srand((unsigned int)(time(NULL) ^ getpid()));
    key_t key;
    ssize_t h, r;
    check_handle(h = open("key.txt", O_RDONLY), OPEN_H);
    check_handle(r = read(h, &key, sizeof(key_t)), READ_H);
    close(h);

    int msqid;
    check_handle(msqid = msgget(key, 0), MSGGET_H);

    struct sigaction sa = {0};
    sa.sa_handler = handle_shutdown;
    sigaction(SIGINT, &sa, NULL);

    while (is_running) {
        struct msg_buffer message;
        message.mtype = 1;

        int offset = snprintf(message.mtext, MSGG_SIZE, "send,%lld,%s\n", (long long)getpid(), argv[optind]);
        int limit = MSGG_SIZE / 4;
        for (int i = offset; i < limit && i < MSGG_SIZE - 1; i++) {
            message.mtext[i] = 'a' + (rand() % 26);
        }
        message.mtext[(limit < MSGG_SIZE) ? limit : MSGG_SIZE - 1] = '\0';

        if (msgsnd(msqid, &message, strlen(message.mtext) + 1, 0) == -1) {
            if (errno == EINTR) break;
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
        sleep(15);
    }
}

void Subscriber(int argc, char *argv[]) {
    key_t key;
    ssize_t h, r;
    check_handle(h = open("key.txt", O_RDONLY), OPEN_H);
    check_handle(r = read(h, &key, sizeof(key_t)), READ_H);
    close(h);

    int msqid;
    check_handle(msqid = msgget(key, 0), MSGGET_H);

    struct sigaction sa = {0};
    sa.sa_handler = handle_shutdown;
    sigaction(SIGINT, &sa, NULL);

    pid_t my_pid = getpid();

    for (int i = optind; i < argc; i++) {
        struct msg_buffer sub_msg;
        sub_msg.mtype = 1;
        snprintf(sub_msg.mtext, MSGG_SIZE, "subscribe,%lld,%s\n", (long long)my_pid, argv[i]);
        if (msgsnd(msqid, &sub_msg, strlen(sub_msg.mtext) + 1, 0) == -1) {
            perror("msgsnd subscribe");
            exit(EXIT_FAILURE);
        }
    }

    while (is_running) {
        struct msg_buffer in_msg;
        if (msgrcv(msqid, &in_msg, sizeof(in_msg.mtext), my_pid, 0) == -1) {
            if (errno == EINTR) {
                break;
            }
            perror("msgrcv subscriber");
            break;
        }
        printf("Subscriber %lld: %s\n", (long long)my_pid, in_msg.mtext);
    }

    struct msg_buffer unsub_msg;
    unsub_msg.mtype = 1;
    snprintf(unsub_msg.mtext, MSGG_SIZE, "unsubscribe,%lld,all\n", (long long)my_pid);
    msgsnd(msqid, &unsub_msg, strlen(unsub_msg.mtext) + 1, 0);

    exit(EXIT_SUCCESS);
}
