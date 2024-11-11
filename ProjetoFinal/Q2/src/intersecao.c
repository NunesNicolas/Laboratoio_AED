#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void intersecao(struct Node** head, int arrayA[], int arrayB[], size_t sizeA, size_t sizeB) {
    size_t i = 0, j = 0; // Use size_t for indices

    while (i < sizeA && j < sizeB) {
        if (arrayA[i] < arrayB[j]) {
            insertAtBeginning(head, arrayA[i]);
            i++;
        } else if (arrayA[i] > arrayB[j]) {
            insertAtBeginning(head, arrayB[j]);
            j++;
        } else {
            // If they are equal, insert only once
            insertAtBeginning(head, arrayA[i]);
            i++;
            j++;
        }
    }

    printList(*head);
}