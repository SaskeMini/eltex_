#include "queue.h"

int main(){
    queue* head = NULL;
    while (1){
        printf("1 - add\n");
        printf("2 - del first\n");
        printf("3 - del with priority\n");
        printf("4 - del more than priority\n");
        printf("5 - exit\n");
        printf("6 - show queue\n");
        printf("enter command:\n");
        char input = getchar();
        if (input == '1'){
            getchar();
            int pr = 0;
            printf("Input priority: ");
            if (scanf("%d", &pr) != 1){
                while (getchar() != '\n'){}
                printf("Incorrect index\n");
                continue;
            }
            while (getchar() != '\n'){}

            if (pr < 0 || pr > 255){
                printf("Priority out of range\n");
                continue;
            }
            head = add(pr, head);
        }
        else if (input == '2'){
            getchar();
            int res = 0;
            head = del_first(head, &res);
            printf("Delete with priority: %d\n", res);
        }
        else if (input == '3'){
            getchar();
            int pr = 0;
            printf("Input priority: ");
            if (scanf("%d", &pr) != 1){
                while (getchar() != '\n'){}
                printf("Incorrect index\n");
                continue;
            }
            while (getchar() != '\n'){}

            if (pr < 0 || pr > 255){
                printf("Priority out of range\n");
                continue;
            }

            int res = 0;
            head = del(pr, head, &res, 0);
            printf("Delete with priority: %d\n", res);
        }
        else if (input == '4'){
            getchar();
            int pr = 0;
            printf("Input priority: ");
            if (scanf("%d", &pr) != 1){
                while (getchar() != '\n'){}
                printf("Incorrect index\n");
                continue;
            }
            while (getchar() != '\n'){}

            if (pr < 0 || pr > 255){
                printf("Priority out of range\n");
                continue;
            }
            int res = 0;
            head = del(pr, head, &res, 1);
            printf("Delete with priority: %d\n", res);
        }
        else if (input == '5'){
            getchar();
            break;
        }
        else if (input == '6'){
            queue* temp = head;
            while (temp){
                printf("%d ", temp->pr);
                temp = temp->next;
            }
            printf("\n");
            getchar();
        }
        else{
            getchar();
            printf("Incorrect input, enter correct command:\n");
        }
    }
    while (head){
        queue* next = head->next;
        free(head);
        head = next;
    }
    return 0;
}