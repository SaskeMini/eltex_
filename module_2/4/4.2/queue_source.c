#include "queue.h"

queue* add(int pr, queue* head){
    queue *curr = malloc(sizeof(queue));
    curr->next = NULL;
    curr->pr = pr;
    if (!head){return curr;}
    if (pr >= head->pr){
        curr->next = head;
        return curr;
    }
    queue *p = head;
    while (p->next){
        if (p->next->pr <= curr->pr){
            break;
        }
        p = p->next; 
    }
    curr->next = p->next;
    p->next = curr;
    return head;
}

queue* del_first(queue* head, int* res){
    if (!head){return head;}
    *res = head->pr;
    queue* p = head;
    head = p->next;
    free(p);
    return head;
}

queue* del(int pr, queue* head, int* res, char more_than){
    if (!head){return head;}
    if (more_than == 1 && head->pr >= pr){ return del_first(head, res); }
    else if (more_than == 0 && head->pr == pr){ return del_first(head, res); }

    queue *p = head;
    while (p->next){
        if (more_than == 1 && p->next->pr >= pr){
            break;
        }
        if (more_than == 0 && p->next->pr == pr){
            break;
        }
        p = p->next; 
    }
    if (p->next){
        *res = p->next->pr;
        queue *temp = p->next;
        p->next = p->next->next;
        free(temp);
    }
    return head;
}