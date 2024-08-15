#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

void bubbleOptimized(int arr[], int n, Metrics *metrica)
{
    int i, j;
    _Bool swapped = 0;
    int temp;

    for (i = 0; i < n - 1; i++)
    {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++)
        {
            metrica->comparacoes++;
            if (arr[j] > arr[j + 1])
            {
                // Troca os elementos arr[j] e arr[j+1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
                metrica->trocas++;
            }
        }
        // Se não houve trocas na passada atual, o array já está ordenado
        if (!swapped)
        {
            break;
        }
    }
};