#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct {
    int data;
    struct Node* next;
} Node;

void insertAtBeginning(struct Node** head, int data);
void printList(struct Node* head);
void uniao(struct Node** head, int arrayA[], size_t sizeA, int arrayB[], size_t sizeB);
void intersecao(struct Node** head, int arrayA[], int arrayB[], size_t lengthA, size_t lengthB);
#endif