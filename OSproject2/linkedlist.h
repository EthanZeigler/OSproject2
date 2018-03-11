//
// Created by Ethan Zeigler on 3/11/18.
//

#ifndef OSPROJECT2_LINKEDLIST_H
#define OSPROJECT2_LINKEDLIST_H

struct Node {
    struct Node* next;
    void* val;
};

void linkedlist_append_char(struct Node* head, char* val);
int linkedlist_contains_str(struct Node* head, char* val);
void linkedlist_destroy(struct Node* head);
void linkedlist_append(struct Node* head, void* val);
void linkedlist_init(struct Node* head);

#endif //OSPROJECT2_LINKEDLIST_H
