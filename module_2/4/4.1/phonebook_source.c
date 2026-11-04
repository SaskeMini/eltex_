#include "phonebook_header.h"

void print_book(list *book){
    if (!book){return;}
    int counter = 0;
    list *p = book;
    while(1){
        printf("Index: %d, Name: %s, Surname: %s, Second name: %s, Work place: %s, Work stat: %s, Phone number: %s, Email: %s, Links: %s\n", counter, p->elem->name,
                p->elem->surname, p->elem->second_name, p->elem->work_place, p->elem->work_stat,
                p->elem->phone_number, p->elem->email, p->elem->links);
        if (!p->next){
            break;
        }
        counter++;
        p = p->next;
    }
}

list* add_list(list *head, info* elem){
    list *curr = malloc(sizeof(list));
    curr->elem = elem;
    curr->prev = NULL;
    curr->next = NULL;
    if (!head || strcmp(elem->surname, head->elem->surname) <= 0) {
        curr->next = head;
        if (head) head->prev = curr;
        return curr;
    }
    list *p = head;
    while (p->next && strcmp(p->next->elem->surname, elem->surname) < 0) {p = p->next;}

    curr->next = p->next;
    curr->prev = p;
    if (p->next) p->next->prev = curr;
    p->next = curr;

    return head;
}

list* edit_list(list *head, int idx, info *new_elem){
    if (!head || idx < 0) return head;
    list *p = head;
    for (int i = 0; i < idx; i++){
        if (!p->next) return head;
        p = p->next;
    }

    free_memory(p->elem);
    *p->elem = *new_elem;

    if (p->prev) p->prev->next = p->next;
    else head = p->next;
    if (p->next) p->next->prev = p->prev;
    p->prev = p->next = NULL;

    if (!head || strcmp(p->elem->surname, head->elem->surname) <= 0){
        p->next = head;
        if (head) head->prev = p;
        return p;
    }
    list *q = head;
    while (q->next && strcmp(q->next->elem->surname, p->elem->surname) < 0) { q = q->next; }
    p->next = q->next;
    p->prev = q;
    if (q->next) q->next->prev = p;
    q->next = p;
    return head;
}

list* del_list(list *head, int idx){
    if (!head || idx < 0) return head;
    list *p = head;
    for (int i = 0; i < idx; i++){
        if (!p->next) return head;
        p = p->next;
    }
    if (p->prev) p->prev->next = p->next;
    else head = p->next;
    if (p->next) p->next->prev = p->prev;
    free_memory(p->elem);
    free(p->elem);
    free(p);
    return head;
}



void new_memory_for_elem(info *elem){
    elem->name = malloc(sizeof(char) * 16);
    elem->len_name = 16;

    elem->surname = malloc(sizeof(char) * 16);
    elem->len_surname = 16;

    elem->second_name = malloc(sizeof(char) * 16);
    elem->len_second_name = 16;

    elem->work_place = malloc(sizeof(char) * 16);
    elem->len_work_place = 16;

    elem->work_stat = malloc(sizeof(char) * 16);
    elem->len_work_stat = 16;

    elem->phone_number = malloc(sizeof(char) * 16);
    elem->len_phone_number = 16;

    elem->email = malloc(sizeof(char) * 16);
    elem->len_email = 16;

    elem->links = malloc(sizeof(char) * 16);
    elem->len_links = 16;
}



void free_memory(info *elem){
    free(elem->name);
    elem->name = NULL;

    free(elem->surname);
    elem->surname = NULL;

    free(elem->second_name);
    elem->second_name = NULL;

    free(elem->work_place);
    elem->work_place = NULL;

    free(elem->work_stat);
    elem->work_stat = NULL;
    
    free(elem->phone_number);
    elem->phone_number = NULL;

    free(elem->email);
    elem->email = NULL;

    free(elem->links);
    elem->links = NULL;
}