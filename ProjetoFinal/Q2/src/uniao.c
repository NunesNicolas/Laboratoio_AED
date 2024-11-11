#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void uniao(struct Node** head, int arrayA[], size_t sizeA, int arrayB[], size_t sizeB) {
    for (size_t i = 0; i < sizeA; i++) {
        insertAtBeginning(head, arrayA[i]);
    }
    for (size_t i = 0; i < sizeB; i++) {
        insertAtBeginning(head, arrayB[i]);
    }
    printList(*head);  // Dereference head to get the actual pointer
}