#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

void BucketOptimized(int v[], int n, Metrics *metrica)
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
