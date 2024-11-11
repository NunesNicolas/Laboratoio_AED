#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int elmA[5] = {12, 34, 44, 75, 99};
int elmB[5] = {25, 27, 41, 88, 92};


struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int option = 0;
printf("você possui dois conjuntos de números, como deseja manipulá-los \n");
for (size_t  i = 0; i < sizeof(elmA) / sizeof(elmA[0]); i++)
{
printf("[%d]",elmA[i]);
}
printf("\n");

for (size_t  i = 0; i < sizeof(elmA) / sizeof(elmA[0]); i++)
{
printf("[%d]",elmB[i]);
}
    do{

printf("\n 1-unir    9-finalizar \n");
scanf("%d", &option);

switch (option)
{
case 1:
   uniao(&head, elmA, sizeof(elmA) / sizeof(elmA[0]),elmB, sizeof(elmA) / sizeof(elmA[0]));
    break;

case 9:
printf("finalizando...");
    break;

default:
    break;
}
  } while (option != 9);  
 
    
    return 0;
}

