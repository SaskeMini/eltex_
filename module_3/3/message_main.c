#include "message.h"

int main(int argc, char *argv[]) {

    if (argc != 2){
        perror("argv");
        return 0;
    }

    char mq1_name[strlen(argv[1]) + 4], mq2_name[strlen(argv[1]) + 4];
    snprintf(mq1_name, sizeof(mq1_name), "%s%s%s", "/", argv[1], "_1");
    snprintf(mq2_name, sizeof(mq2_name), "%s%s%s", "/", argv[1], "_2");

    int check = 0;
    mqd_t mq1 = mq_open(mq1_name, O_WRONLY);
    if (mq1 == (mqd_t)-1) {
        check++;
        if (errno == ENOENT) {
            mq1 = mq_open(mq1_name, O_CREAT | O_RDONLY, RIGHTS, NULL);
            if (mq1 == (mqd_t)-1) {
                perror("mq_open");
                return 0;
            }
        }
        else{
            perror("mq_open");
            return 0;
        }
    }

    mqd_t mq2 = mq_open(mq2_name, O_RDONLY);
    if (mq2 == (mqd_t)-1) {
        check++;
        if (errno == ENOENT) {
            mq2 = mq_open(mq2_name, O_CREAT | O_WRONLY, RIGHTS, NULL);
            if (mq2 == (mqd_t)-1) {
                perror("mq_open");
                return 0;
            }
            if (check == 2){
                read_and_write(mq1, mq2);
                mq_close(mq1);
                mq_close(mq2);
                mq_unlink(mq1_name);
                mq_unlink(mq2_name);
            }
        }
        else{
            perror("mq_open");
            return 0;
        }
    }

    if (check == 0){ 
        read_and_write(mq2, mq1); 
        mq_close(mq1);
        mq_close(mq2);
    }
    else if (check == 1){
        perror("mq_unlink/close_error");
        mq_close(mq1);
        mq_close(mq2);
    }
    return 0;
}

