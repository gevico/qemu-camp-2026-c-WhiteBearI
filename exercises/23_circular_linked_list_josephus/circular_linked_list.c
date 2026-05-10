#include "circular_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Node* create_circular_list(int n) {
    if (n <= 0) return NULL;

    Node *head = malloc(sizeof(Node));
    head->id = 1;
    head->next = NULL;

    Node *prev = head;
    for (int i = 2; i <= n; i++) {
        Node *node = malloc(sizeof(Node));
        node->id = i;
        node->next = NULL;
        prev->next = node;
        prev = node;
    }
    prev->next = head; // 成环

    return head;
}

void free_list(Node* head) {
    if (!head) return;
    Node *p = head;
    do {
        Node *next = p->next;
        free(p);
        p = next;
    } while (p != head);
}
