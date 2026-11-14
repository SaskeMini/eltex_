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
    pipe_name ? process_fifo(argv, pipe_name, argc) : process_pipe(argv, argc);
    return 0;
}

