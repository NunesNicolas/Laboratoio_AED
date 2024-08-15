#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

#define NUM_VETORES 10
#define RODADAS 10
#define MAX_TAMANHO 10000

void gerarVetorAleatorio(int v[], int n)
{
    for (int i = 0; i < n; i++)
    {
        v[i] = rand() % 1000;
    }
};

void medirTempoExecucao(int arr[], int n, void (*sortFunc)(int[], int, Metrics *), Metrics *metrica)
{
    clock_t start, end;
    start = clock();
    sortFunc(arr, n, metrica);
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo: %f segundos\n", time_taken);
}

void copiarVetor(int dest[], int src[], int n)
{
    for (int i = 0; i < n; i++)
    {
        dest[i] = src[i];
    }
}

void printArray(int v[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
};

int main()
{
    srand(time(NULL));
    int tamanhos[] = {10, 100, 1000, 10000};
    int i, t, j;
    int escolha = 1;
    int vetores[NUM_VETORES][MAX_TAMANHO];
    int copia[MAX_TAMANHO];

    for (t = 0; t < 4; t++)
    {
        int n = tamanhos[t];
        for (i = 0; i < NUM_VETORES; i++)
        {
            gerarVetorAleatorio(vetores[i], n);
        }
    }

    do
    {
        printf("Qual método deseja utilizar? \n 1-Bubble padrão \n 2-Bubble otimizado \n");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:

            for (t = 0; t < 4; t++)
            {
                int n = tamanhos[t];
                printf("Tamanho do vetor: %d\n", n);

                for (i = 0; i < NUM_VETORES; i++)
                {
                    double total_time = 0.0;
                    double min_time = __DBL_MAX__;
                    double max_time = 0.0;
                    Metrics metrica_total = {0, 0};

                    for (j = 0; j < RODADAS; j++)
                    {
                        Metrics metrica = {0, 0};

                        copiarVetor(copia, vetores[i], n);

                        clock_t start, end;
                        start = clock();
                        bubbleSort(copia, n, &metrica);
                        end = clock();

                        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
                        total_time += time_taken;

                        if (time_taken < min_time)
                            min_time = time_taken;
                        if (time_taken > max_time)
                            max_time = time_taken;

                        metrica_total.comparacoes += metrica.comparacoes;
                        metrica_total.trocas += metrica.trocas;
                    }

                    printf("Vetor %d:\n", i + 1);
                    printf("Tempo médio: %f segundos\n", total_time / RODADAS);
                    printf("Diferença entre maior e menor tempo: %f segundos\n", max_time - min_time);
                    printf("Média de comparações: %ld\n", metrica_total.comparacoes / RODADAS);
                    printf("Média de trocas: %ld\n", metrica_total.trocas / RODADAS);
                    printf("\n");
                }
            }
            break;

        case 2:
            for (t = 0; t < 4; t++)
            {
                int n = tamanhos[t];
                printf("Tamanho do vetor: %d\n", n);

                for (i = 0; i < NUM_VETORES; i++)
                {
                    double total_time = 0.0;
                    double min_time = __DBL_MAX__;
                    double max_time = 0.0;
                    Metrics metrica_total = {0, 0};

                    for (j = 0; j < RODADAS; j++)
                    {
                        Metrics metrica = {0, 0};

                        copiarVetor(copia, vetores[i], n);

                        clock_t start, end;
                        start = clock();
                        bubbleOptimized(copia, n, &metrica);
                        end = clock();

                        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
                        total_time += time_taken;

                        if (time_taken < min_time)
                            min_time = time_taken;
                        if (time_taken > max_time)
                            max_time = time_taken;

                        metrica_total.comparacoes += metrica.comparacoes;
                        metrica_total.trocas += metrica.trocas;
                    }

                    printf("Vetor %d:\n", i + 1);
                    printf("Tempo médio: %f segundos\n", total_time / RODADAS);
                    printf("Diferença entre maior e menor tempo: %f segundos\n", max_time - min_time);
                    printf("Média de comparações: %ld\n", metrica_total.comparacoes / RODADAS);
                    printf("Média de trocas: %ld\n", metrica_total.trocas / RODADAS);
                    printf("\n");
                }
            }
            break;

        default:
            break;
        }
    } while (escolha != 0);
    return 0;
}
