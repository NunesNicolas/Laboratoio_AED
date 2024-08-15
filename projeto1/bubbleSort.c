#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_VETORES 10
#define RODADAS 10

typedef struct
{
    long comparacoes;
    long trocas;
} Metrics;

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

void basicCod(int v[], int n, Metrics *metrica)
{
    int i, continua, fim = n;
    int temp;
    do
    {
        continua = 0;
        for (i = 0; i < fim - 1; i++)
        {
            metrica->comparacoes++;
            if (v[i] > v[i + 1])
            {
                temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
                continua = i;
                metrica->trocas++;
            }
        }
        fim--;
    } while (continua != 0);
};

void optimizedCod(int arr[], int n, Metrics *metrica)
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

    for (t = 0; t < 4; t++)
    {
        int n = tamanhos[t];
        int vetores[NUM_VETORES][n];
        int copia[n];

        // Gerar 10 vetores aleatórios de tamanho n
        for (i = 0; i < NUM_VETORES; i++)
        {
            gerarVetorAleatorio(vetores[i], n);
        }

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
                optimizedCod(copia, n, &metrica);
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

    return 0;
}