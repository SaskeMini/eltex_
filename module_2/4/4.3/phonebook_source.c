#include "phonebook_header.h"

void print_tree_rec(tree *book, int count) {
    if (!book) return;
    print_tree_rec(book->left, count + 1);
    for (int i = 0; i < count; i++) printf("    ");
    printf("%s\n", book->elem->surname);
    print_tree_rec(book->right, count + 1);
}

void print_book(tree *book) {
    if (!book) { return; }
    print_tree_rec(book, 0);
}


tree* add_tree(tree *head, info* elem){
    tree *p = head;
    tree *curr = malloc(sizeof(tree));
    curr->elem = elem;
    curr->left = NULL;
    curr->right = NULL;
    if (!head){ return curr; }
    while (p){
        if (strcmp(elem->surname, p->elem->surname) < 0){
            if (p->left){ p = p->left; }
            else {
                p->left = curr;
                break;
            }
        }
        else if (strcmp(elem->surname, p->elem->surname) > 0){
            if (p->right){ p = p->right; }
            else{
                p->right = curr; 
                break;
            }
        }
        else{
            free_memory(elem);
            free(elem);
            free(curr);
            break;
        }
    }
    return head;
}

tree* edit_tree(tree *head, char sur[], info *new_elem){
    if (!head || !sur || !new_elem) return head;
    tree *p = head;
    while (p && strcmp(p->elem->surname, sur) != 0){
        p = (strcmp(sur, p->elem->surname) < 0) ? p->left : p->right;
    }
    if (!p){
        free_memory(new_elem);
        free(new_elem);
        return head;
    }

    p = head;
    while (p){
        if (strcmp(new_elem->surname, p->elem->surname) == 0){
            free_memory(new_elem);
            free(new_elem);
            return head;
        }
        p = (strcmp(new_elem->surname, p->elem->surname) < 0) ? p->left : p->right;
    }

    head = del_tree(head, sur);
    head = add_tree(head, new_elem);
    return head;
}

tree* del_tree(tree *head, char sur[]){
    if (!head || !sur) return head;
    tree *past = NULL;
    tree *p = head;
    while (p && strcmp(p->elem->surname, sur) != 0){
        past = p;
        p = (strcmp(sur, p->elem->surname) < 0) ? p->left : p->right;
    }
    if (!p) return head;

    if (p->left && p->right){
        tree *p2 = p;
        tree *rig = p->right;
        while (rig->left){ 
            p2 = rig; 
            rig = rig->left;
        }
        free_memory(p->elem);
        free(p->elem);
        p->elem = rig->elem;

        if (p2->left == rig) { 
            p2->left = rig->right; 
        }
        else { p2->right = rig->right; }
        free(rig);
    }
    else{
        tree *new_el = p->left ? p->left : p->right;
        if (!past){ 
            head = new_el;
        }
        else if (past->left == p) { 
            past->left = new_el;
        }
        else { 
            past->right = new_el;
        }
        free_memory(p->elem);
        free(p->elem);
        free(p);
    }
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