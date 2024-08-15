#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct
{
    long comparacoes;
    long trocas;
} Metrics;

void bubbleOptimized(int arr[], int n, Metrics *metrica);
void bubbleSort(int v[], int n, Metrics *metrica);

#endif