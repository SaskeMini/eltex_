#include <stdio.h>
#include <stdlib.h>

typedef struct queue queue;

struct queue{
    int pr;
    queue *next;
};

queue* add(int pr, queue* head);
queue* del_first(queue* head, int* res);
queue* del(int pr, queue* head, int* res, char more_than);