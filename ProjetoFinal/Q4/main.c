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
    // Construir as árvores
    Node *tree1 = buildTree1();
    Node *tree25 = buildTree25();

    int id = 0;
    int captch = 0;
     Node *arv = NULL;
 
    do
    {
        printf("digite seu codigo de acesso, ou digite 0 para encerrar o processo: ");
        scanf("%d", &id);
        scanf("%d", &captch);
        getchar();
        printf("\n [%d] [%d]", id, captch);
         if (id == 1)
         {
           arv = tree1;
         }else if (captch == 25)
         {
           arv = tree25;
         }
         
         
       switch (id)
       {
       case 1:
       printf("Mensagem escondida: ");
       printf("[");
       preorder(arv);
         printf("]\n");
        break;

         case 2:
           printf("Mensagem escondida: ");
       printf("[");
        inorder(arv);
          printf("]\n");
        break;

         case 3:
           printf("Mensagem escondida: ");
       printf("[");
        postorder(arv);
          printf("]\n");
        break;
       
       default:
        break;
       }
    } while (id != 4);
    printf("FINALIZANDO...");

    return 0;
}
