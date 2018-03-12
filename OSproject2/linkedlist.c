//
// Created by Ethan Zeigler on 3/11/18.
//

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "linkedlist.h"
#include "csvparser.h"



int linkedlist_contains_str(struct Node* head, char* val) {
    struct Node* curr = head;
    while (curr) {
        if (strcmp(val, curr->val) == 0) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void linkedlist_append(struct Node* head, void* val) {
    struct Node* curr = head;
    if (curr->val == NULL && curr->next == NULL) {
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = malloc(sizeof(struct Node));
        curr->next->val = val;
    } else {
        curr = malloc(sizeof(struct Node));
        curr->val = val;
        curr->next = NULL;
    }
}

void linkedlist_append_char(struct Node* head, char* val) {
    struct Node* curr = head;
    if (curr != NULL) {
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = malloc(sizeof(struct Node));
        curr->next->val = strdup(val);
    } else {
        curr = malloc(sizeof(struct Node));
        curr->val = strdup(val);
        curr->next = NULL;
    }
}

void linkedlist_destroy(struct Node* head) {
    //free(head);
}

void linkedlist_init(struct Node* head) {
    head->next = NULL;
    head->val = NULL;
}
