#include "net.h"

int main(int argc, char* argv[]){
    srand(time(NULL));
    if (argc != 4){
        printf("Incorrect args\n");
        return 0;
    }
    int n = atoi(argv[3]);
    long long int gateway = check_ip(argv[1]), mask = check_ip(argv[2]);
    if (n <= 0 || gateway == -1 || mask == -1){
        printf("Incorrect args\n");
        return 0;
    }
    long long int main_adress = gateway & mask;
    double res = 0;
    for (int i = 0; i < n; i++){
        long long int new_adress = new_random() & mask;
        if (new_adress == main_adress){ res++; }
    }
    printf("To local network: %.0lf %.2lf%%\n", res, (res)/n*100);
    printf("To other networks: %.0lf %.2lf%%\n", (n - res), ((n - res)/n)*100);
    return 0;
}