#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int senha;
} Pessoa;

typedef struct Node {
    Pessoa pessoa;
    struct Node *next;
} Node;

Node *imparHead = NULL;
Node *parHead = NULL;

// Função para inserir pessoa na lista de espera
void inserirNaFila(Pessoa novaPessoa) {
    Node *novo = (Node *)malloc(sizeof(Node));
    novo->pessoa = novaPessoa;
    novo->next = NULL;

    if (novaPessoa.senha % 2 == 0) {
        // Insere na fila de senhas pares
        if (parHead == NULL) {
            parHead = novo;
        } else {
            Node *temp = parHead;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = novo;
        }
    } else {
        // Insere na fila de senhas ímpares
        if (imparHead == NULL) {
            imparHead = novo;
        } else {
            Node *temp = imparHead;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = novo;
        }
    }
}

// Função para parear pessoas das filas de senhas ímpares e pares
void formarPares() {
    while (imparHead != NULL && parHead != NULL) {
        printf("%s e %s\n", imparHead->pessoa.nome, parHead->pessoa.nome);

        Node *tempImpar = imparHead;
        Node *tempPar = parHead;

        imparHead = imparHead->next;
        parHead = parHead->next;

        free(tempImpar);
        free(tempPar);
    }
}

// Função para exibir as pessoas restantes na fila
void mostrarFila() {
    Node *temp = imparHead;
    printf("Pessoas na fila com senha ímpar: ");
    while (temp != NULL) {
        printf("%s (senha %d) ", temp->pessoa.nome, temp->pessoa.senha);
        temp = temp->next;
    }
    printf("\n");

     Node *temp2 = parHead;
    printf("Pessoas na fila com senha par: ");
    while (temp2 != NULL) {
        printf("%s (senha %d) ", temp2->pessoa.nome, temp2->pessoa.senha);
        temp2 = temp2->next;
    }
    printf("\n");
}

void lerArquivoCSV(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Não foi possível abrir o arquivo");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        Pessoa novaPessoa;
        // Remove o caractere de nova linha, se existir
        linha[strcspn(linha, "\n")] = 0;

        // Usa sscanf para ler o nome e a senha
        sscanf(linha, "%[^,],%d", novaPessoa.nome, &novaPessoa.senha);
        inserirNaFila(novaPessoa);
        formarPares(); // Tentar formar pares com cada nova pessoa adicionada
    }

    fclose(arquivo);
}

int main() {
    int n;
      const char *inscritos = "inscritos.csv";
    lerArquivoCSV(inscritos);

    printf("Digite o número de pessoas a serem adicionadas: ");
    scanf("%d", &n);
    getchar(); // Limpar o buffer de entrada

    for (int i = 0; i < n; i++) {
        Pessoa novaPessoa;
        printf("Digite o nome e a senha (ex: Valentina 4): ");
        scanf("%s %d", novaPessoa.nome, &novaPessoa.senha);
        getchar(); // Limpar o buffer de entrada

        inserirNaFila(novaPessoa);
        formarPares(); // Tentar formar pares com cada nova pessoa adicionada
    }

    // Exibir a fila final de pessoas não pareadas
    mostrarFila();

    return 0;
}
