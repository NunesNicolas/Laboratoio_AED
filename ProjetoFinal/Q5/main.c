#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Paciente {
    char nome[50];
    int hora, minuto, segundo; 
    int risco;                 
} Paciente;


typedef struct Heap {
    Paciente *pacientes;
    int tamanho;
    int capacidade;
} Heap;


Heap *criarHeap(int capacidade) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->pacientes = (Paciente *)malloc(capacidade * sizeof(Paciente));
    heap->tamanho = 0;
    heap->capacidade = capacidade;
    return heap;
}


void destruirHeap(Heap *heap) {
    free(heap->pacientes);
    free(heap);
}


int compararPacientes(Paciente p1, Paciente p2) {
    if (p1.risco > p2.risco) return -1;
    if (p1.risco < p2.risco) return 1;
    if (p1.hora < p2.hora || (p1.hora == p2.hora && p1.minuto < p2.minuto) || 
        (p1.hora == p2.hora && p1.minuto == p2.minuto && p1.segundo < p2.segundo)) {
        return -1;
    }
    return 1;
}

void trocar(Paciente *a, Paciente *b) {
    Paciente temp = *a;
    *a = *b;
    *b = temp;
}


void subir(Heap *heap, int idx) {
    int pai = (idx - 1) / 2;
    while (idx > 0 && compararPacientes(heap->pacientes[idx], heap->pacientes[pai]) == -1) {
        trocar(&heap->pacientes[idx], &heap->pacientes[pai]);
        idx = pai;
        pai = (idx - 1) / 2;
    }
}


void descer(Heap *heap, int idx) {
    int maior = idx;
    int esq = 2 * idx + 1;
    int dir = 2 * idx + 2;

    if (esq < heap->tamanho && compararPacientes(heap->pacientes[esq], heap->pacientes[maior]) == -1)
        maior = esq;

    if (dir < heap->tamanho && compararPacientes(heap->pacientes[dir], heap->pacientes[maior]) == -1)
        maior = dir;

    if (maior != idx) {
        trocar(&heap->pacientes[idx], &heap->pacientes[maior]);
        descer(heap, maior);
    }
}

void inserirPaciente(Heap *heap, Paciente paciente) {
    if (heap->tamanho == heap->capacidade) {
        printf("A fila de pacientes está cheia!\n");
        return;
    }
    heap->pacientes[heap->tamanho] = paciente;
    subir(heap, heap->tamanho);
    heap->tamanho++;
}

Paciente removerPaciente(Heap *heap) {
    if (heap->tamanho == 0) {
        printf("Não há pacientes na fila!\n");
        Paciente vazio = {"", 0, 0, 0, 0};
        return vazio;
    }
    Paciente paciente = heap->pacientes[0];
    heap->pacientes[0] = heap->pacientes[--heap->tamanho];
    descer(heap, 0);
    return paciente;
}

void exibirMenu() {
    printf("\n---- Fila de Prioridade (Urgência) ----\n");
    printf("1. Inserir paciente na fila\n");
    printf("2. Atender paciente\n");
    printf("3. Encerrar programa\n");
    printf("Escolha uma opção: ");
}

int main() {
    int capacidade = 100;
    Heap *heap = criarHeap(capacidade);

    int opcao;
    do {
        exibirMenu();
        scanf("%d", &opcao);

        if (opcao == 1) {
            Paciente novo;
            printf("Digite o nome do paciente: ");
            scanf(" %[^\n]", novo.nome);
            printf("Digite a hora de chegada (hh mm ss): ");
            scanf("%d %d %d", &novo.hora, &novo.minuto, &novo.segundo);
            printf("Digite o grau de urgência (1-5, onde 5 é o mais urgente): ");
            scanf("%d", &novo.risco);

            inserirPaciente(heap, novo);
            printf("Paciente %s inserido na fila!\n", novo.nome);

        } else if (opcao == 2) {
            Paciente atendido = removerPaciente(heap);
            if (strlen(atendido.nome) > 0) {
                printf("Paciente %s será atendido agora.\n", atendido.nome);
            }
        } else if (opcao == 3) {
            printf("Encerrando o programa...\n");
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 3);

    destruirHeap(heap);
    return 0;
}
