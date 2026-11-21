#include "ibp.h"

int main(int argc, char *argv[]) {
    int opt;
    char option = 0;
    int flag_count = 0;

    while ((opt = getopt(argc, argv, "bps")) != -1) {
        switch (opt) {
            case 'b':
            case 'p':
            case 's':
                option = opt;
                flag_count++;
                break;
            case '?':
                fprintf(stderr, "Incorrect args");
                return EXIT_FAILURE;
        }
    }

    if (!option || flag_count != 1) {
        fprintf(stderr, "Incorrect args\n");
        return EXIT_FAILURE;
    }

    int topics_count = argc - optind;

    if (option == 'b' && topics_count > 0) {
        fprintf(stderr, "Incorrect args\n");
        return EXIT_FAILURE;
    }
    if (option == 'p' && topics_count != 1) {
        fprintf(stderr, "Incorrect args\n");
        return EXIT_FAILURE;
    }
    if (option == 's' && topics_count < 1) {
        fprintf(stderr, "Incorrect args\n");
        return EXIT_FAILURE;
    }

    for (int i = optind; i < argc; i++) {
        if (strlen(argv[i]) >= sizeof(((themes *)0)->theme)) {
            fprintf(stderr, "Error: topic '%s' is too long (max 63 chars)\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    switch (option) {
        case 'b':
            Broker();
            break;
        case 'p':
            Publisher(argv);
            break;
        case 's':
            Subscriber(argc, argv);
            break;
    }

    return EXIT_SUCCESS;
}
