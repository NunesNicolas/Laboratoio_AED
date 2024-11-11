#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int elmA[] = {12, 24, 34, 44, 75, 99};
int elmB[] = {24, 25, 27, 44, 88, 92};


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

printf("\n 1-unir  2-intersecao  3-diferenca de A para B  9-finalizar \n");
scanf("%d", &option);

switch (option)
{
case 1:
   uniao(&head, elmA, sizeof(elmA) / sizeof(elmA[0]),elmB, sizeof(elmB) / sizeof(elmB[0]));
    break;

case 2:
 intersecao(&head, elmA, elmB, sizeof(elmA) / sizeof(elmA[0]), sizeof(elmB) / sizeof(elmB[0]));
break;

case 3:
 diferenca(&head, elmA, elmB, sizeof(elmA) / sizeof(elmA[0]), sizeof(elmB) / sizeof(elmB[0]));
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

