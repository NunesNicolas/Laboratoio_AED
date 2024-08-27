#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

#define TAM 10000 // Tamanho do balde

struct balde
{
    int qtd;
    int valores[TAM];
};

void insertionSort(int arr[], int n, Metrics *metrica)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            metrica->comparacoes++;
            arr[j + 1] = arr[j];
            j = j - 1;
            metrica->trocas++;
        }
        arr[j + 1] = key;
    }
};

void bucketSort(int V[], int N, Metrics *metrica) {
    int i, j, maior, menor, nroBaldes, pos;
    struct balde *bd;

    maior = menor = V[0];
    for (i = 1; i < N; i++) {
        metrica->comparacoes++;
        if (V[i] > maior) maior = V[i];
        if (V[i] < menor) menor = V[i];
    }

    nroBaldes = (maior - menor) / TAM + 1;
    bd = (struct balde *) malloc(nroBaldes * sizeof(struct balde));
    for (i = 0; i < nroBaldes; i++) {
        bd[i].qtd = 0;
    }

    for (i = 0; i < N; i++) {
        metrica->comparacoes++;
        pos = (V[i] - menor) / TAM;
        bd[pos].valores[bd[pos].qtd] = V[i];
        bd[pos].qtd++;
    }


    pos = 0;
    for (i = 0; i < nroBaldes; i++) {
        insertionSort(bd[i].valores, bd[i].qtd, metrica);
        for (j = 0; j < bd[i].qtd; j++) {
            V[pos] = bd[i].valores[j];
            pos++;
        }
    }

    free(bd);
}