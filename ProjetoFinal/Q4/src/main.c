#include <stdio.h>
#include <stdlib.h>

// Estrutura para o nó da árvore AVL
typedef struct Node {
    char data;
    int key;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

// Função para obter a altura de um nó
int height(Node *node) {
    return node ? node->height : 0;
}

// Função para atualizar a altura de um nó
void updateHeight(Node *node) {
    if (node) {
        node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));
    }
}

// Rotação à direita
Node *rotateRight(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Rotação à esquerda
Node *rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Balanceamento do nó
Node *balance(Node *node) {
    if (!node) return NULL;

    updateHeight(node);
    int bf = height(node->left) - height(node->right);

    // Rotação à direita
    if (bf > 1 && height(node->left->left) >= height(node->left->right))
        return rotateRight(node);

    // Rotação dupla à direita
    if (bf > 1 && height(node->left->left) < height(node->left->right)) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Rotação à esquerda
    if (bf < -1 && height(node->right->right) >= height(node->right->left))
        return rotateLeft(node);

    // Rotação dupla à esquerda
    if (bf < -1 && height(node->right->right) < height(node->right->left)) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Inserção na árvore AVL
Node *insert(Node *node, char data, int key) {
    if (!node) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = data;
        newNode->key = key;
        newNode->height = 1;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (key < node->key)
        node->left = insert(node->left, data, key);
    else if (key > node->key)
        node->right = insert(node->right, data, key);
    else
        return node; // Chaves duplicadas não são permitidas

    return balance(node);
}

// Percurso em-ordem
void preorder(Node *node) {
    if (node) {
        printf("%c", node->data);
        preorder(node->left);
        preorder(node->right);
    }
}
void inorder(Node *node) {
    if (node) {
        inorder(node->left);
        printf("%c", node->data);
        inorder(node->right);
    }
}
void postorder(Node *node) {
    if (node) {
        postorder(node->left);
        postorder(node->right);
        printf("%c", node->data);
    }
}
// Função para construir a árvore de ID 1
Node *buildTree1() {
    Node *root = NULL;
    root = insert(root, 'l', 15);
    root = insert(root, 'e', 8);
    root = insert(root, 'o', 23);
    root = insert(root, 'h', 1);
    root = insert(root, 'l', 19);
    return root;
}

// Função para construir a árvore de ID 25
Node *buildTree25() {
    Node *root = NULL;
    root = insert(root, 'e', 15);
    root = insert(root, 'h', 8);
    root = insert(root, 't', 1);
    root = insert(root, 'r', 19);
    root = insert(root, 'e', 23);
    return root;
}


int main() {
    Node *tree1 = NULL;  // Inicializa as árvores
    Node *tree25 = NULL;
    int orderTree1 = 0;
    int orderTree25 = 0;


    FILE *file = fopen("D:\\Laboratio_AED\\Laboratoio_AED\\ProjetoFinal\\Q4\\src\\input.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    char line[100];
    int id = 0;
    int order = 0;

    // Lê as linhas do arquivo
    while (fgets(line, sizeof(line), file)) {
        // Remove o caractere de nova linha, se presente
        line[strcspn(line, "\n")] = 0;

        // Verifica se a linha é para selecionar a árvore ou inserir um nó
        if (sscanf(line, "%d,%d", &id, &order) == 2) {
            if (id == 1) {
                orderTree1 = order; // Armazena a ordem para a árvore 1
                tree1 = NULL; // Reinicializa a árvore 1
            } else if (id == 25) {
                orderTree25 = order; // Armazena a ordem para a árvore 25
                tree25 = NULL; // Reinicializa a árvore 25
            }
        } else {
                // Se a linha for do tipo "ID árvore AVL, caractere, chave"
            int key;
            char data;
            int treeId;

            if (sscanf(line, "%d,%c,%d", &treeId, &data, &key) == 3) {
                if (treeId == 1) {
                    tree1 = insert(tree1, data, key);
                } else if (treeId == 25) {
                    tree25 = insert(tree25, data, key);
                } else {
                    printf("ID de árvore inválido.\n");
                }
            } else {
                printf("Formato de entrada inválido: %s\n", line);
            }
        }
    }

    fclose(file); // Fecha o arquivo

    // Imprime a mensagem escondida na ordem especificada
    printf("Mensagem escondida: [");
    if (order == 1) {
        preorder(tree1); // Imprime a árvore 1 em pré-ordem
    } else if (order == 2) {
        inorder(tree1); // Imprime a árvore 1 em em-ordem
    } else if (order == 3) {
        postorder(tree1); // Imprime a árvore 1 em pós-ordem
    } else {
        printf("Ordem inválida.\n");
    }
    printf(" ");
    if (orderTree25 == 1) {
    preorder(tree25); // Imprime a árvore 25 em pré-ordem
} else if (orderTree25 == 2) {
    inorder(tree25); // Imprime a árvore 25 em em-ordem
} else if (orderTree25 == 3) {
    postorder(tree25); // Imprime a árvore 25 em pós-ordem
} else {
    printf("Ordem inválida.\n");
}
    printf("]\n");

    printf("FINALIZANDO...\n");
    return 0;
}