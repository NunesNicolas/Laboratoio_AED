#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct
{
    long comparacoes;
    long trocas;
} Metrics;

void bubbleOptimized(int arr[], int n, Metrics *metrica);
void bubbleSort(int v[], int n, Metrics *metrica);
void bucketSort(int V[], int N, Metrics *metrica);

void insertionSort(int arr[], int n, Metrics *metrica);
#endif