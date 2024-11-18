#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *prox;
} No;

No* novoNo(int valor) {
    No *no = (No*) malloc(sizeof(No));
    no->dado = valor;
    no->prox = NULL;
    return no;
}

void empilhar(No **topo, int valor) {
    No *no = novoNo(valor);
    no->prox = *topo;
    *topo = no;
}

int desempilhar(No **topo) {
    if (*topo == NULL) {
        printf("Erro: a pilha está vazia!\n");
        return -1;
    }
    No *temp = *topo;
    int valor = temp->dado;
    *topo = (*topo)->prox;
    free(temp);
    return valor;
}

void decimalParaBinario(int numero) {
    No *pilha = NULL;

    if (numero == 0) {
        printf("Binário: 0\n");
        return;
    }

    while (numero > 0) {
        int resto = numero % 2;
        empilhar(&pilha, resto);
        numero /= 2;
    }

    printf("Binário: ");
    while (pilha != NULL) {
        printf("%d", desempilhar(&pilha));
    }
    printf("\n");
}

int main() {
    int numero;

    printf("Digite um número decimal: ");
    scanf("%d", &numero);

    decimalParaBinario(numero);

    return 0;
}
