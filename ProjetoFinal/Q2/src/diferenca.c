#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void diferenca(struct Node** head, int arrayA[], int arrayB[], size_t sizeA, size_t sizeB) {
    int contador;
    for (size_t i = 0; i < sizeA; i++) {
    contador = 0;
    for (size_t j = 0; j < sizeB; j++) {
        if ( arrayA[i] == arrayB[j])
        {
           contador += 1;
        }
    }
    if (contador == 0)
    {
      insertAtBeginning(head, arrayA[i]);
    }
    }
    printList(*head);
}