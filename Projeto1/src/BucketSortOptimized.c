#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

#define TAM 10000

struct balde
{
    int qtd;
    int *valores;
};

void bucketOptimized(int V[], int N, Metrics *metrica)
{
    int i, j, maior, menor, nroBaldes, pos;
    struct balde *bd;

    // Acha maior e menor valor
    maior = menor = V[0];
    for (i = 1; i < N; i++)
    {
        metrica->comparacoes++;
        if (V[i] > maior)
            maior = V[i];
        if (V[i] < menor)
            menor = V[i];
    }

    // Inicializa baldes com tamanho dinâmico
    nroBaldes = (maior - menor) / TAM + 1;
    bd = (struct balde *)malloc(nroBaldes * sizeof(struct balde));
    for (i = 0; i < nroBaldes; i++)
    {
        bd[i].qtd = 0;
        bd[i].valores = (int *)malloc(TAM * sizeof(int)); // Alocação dinâmica para cada balde
    }

    // Distribui os valores nos baldes
    for (i = 0; i < N; i++)
    {
        metrica->comparacoes++;
        pos = (V[i] - menor) / TAM;
        bd[pos].valores[bd[pos].qtd++] = V[i];
    }

    // Ordena baldes e coloca no array
    pos = 0;
    for (i = 0; i < nroBaldes; i++)
    {
        if (bd[i].qtd > 0)
        {
            insertionSort(bd[i].valores, bd[i].qtd, metrica);
            for (j = 0; j < bd[i].qtd; j++)
            {
                V[pos++] = bd[i].valores[j];
            }
        }
        free(bd[i].valores); // Libera memória dos baldes após o uso
    }

    free(bd);
}
