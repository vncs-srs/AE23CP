/*Implemente uma função que receba uma árvore binária de busca e um número p, que representa um 
valor de profundida. A função deverá imprimir todos os nós de profundidade p.

Input Format

Na primeira linha, deve ser lido um número inteiro p referente a um valor de profundidade.

Na segunda linha deve ser lido o número inteiro N, que é referente à quantidade de nós da
árvore binária de busca.

Em seguida, em cada linha seguinte deve ser lido um número inteiro para ser inserido como 
nó na árvore (fazer isso até que N números sejam lidos).

Constraints
.
Output Format

Em uma única linha, devem ser impressos os nós de profundidade p.

Sample Input 0
2
13
28
12
8
3
10
9
15
16
45
36
41
59
48

Sample Output 0
8 15 36 59*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node Node;

struct Node{
    int item;
    struct Node *left;
    struct Node *right;
};


Node* criar(int item){
    Node * tree = (Node *) malloc(sizeof(Node));
    
    tree->item = item;
    tree->left = NULL;
    tree->right = NULL;
        
    return tree;
}


Node* pesquisar(int item, Node* tree){
    if (tree != NULL){
        if (item == tree->item)
            return tree;
        else if (item < tree->item)
            return pesquisar(item, tree->left);
        else
            return pesquisar(item, tree->right);
    }else
        return NULL;
}


int min(Node* tree){
    Node* aux = tree;
    
    if (aux != NULL){
        while (aux->left != NULL)
            aux = aux->left;
        
        return aux->item;
    }
    
    return INT_MIN;
}


int max(Node* tree){
    Node* aux = tree;
    
    if (aux != NULL){
        while (aux->right != NULL)
            aux = aux->right;
        
        return aux->item;
    }
    
    return INT_MAX;
}



Node* inserir(int item, Node* tree){
    if (tree == NULL)
        tree = criar(item);
    else if (item < tree->item)
        tree->left = inserir(item, tree->left);
    else if (item > tree->item)
        tree->right = inserir(item, tree->right);
        
    return tree;
}


Node* remover(int item, Node* tree){
    Node *aux, *auxP, *auxF;
    
    if (tree != NULL){
        if (item < tree->item)
            tree->left = remover(item, tree->left);
        else if (item > tree->item)
            tree->right = remover(item, tree->right);
        else{
            aux = tree;
            
            if (aux->left == NULL)
                tree = tree->right;
            else if (aux->right == NULL)
                tree = tree->left;
            else{
                auxP = aux->right;
                auxF = auxP;
                
                while (auxF->left != NULL){
                    auxP = auxF;
                    auxF = auxF->left;
                }
                
                if (auxP != auxF){
                    auxP->left = auxF->right;
                    auxF->left = aux->left;
                }
                
                auxF->right = aux->right;
                
                tree = auxF;
            }
            
            free(aux);
        }
    }
    
    return tree;
}


void imprimirInfix(Node* tree){
    if (tree != NULL){
        imprimirInfix(tree->left);
        printf("\n%i", tree->item);
        imprimirInfix(tree->right);
    }
}


void imprimirPrefix(Node* tree){
    if (tree != NULL){
        printf("\n%i", tree->item);
        imprimirPrefix(tree->left);
        imprimirPrefix(tree->right);
    }
}


void imprimirPosfix(Node* tree){
    if (tree != NULL){
        imprimirPosfix(tree->left);
        imprimirPosfix(tree->right);
        printf("\n%i", tree->item);
    }
}


void liberar_arvore(Node* tree){
    if (tree != NULL){
        liberar_arvore(tree->left);
        liberar_arvore(tree->right);
        free(tree);
    }
}


void imprimirProfundidade(Node* root, int profundidade_alvo,int profundidade_atual) {
    if (root != NULL) {
        if (profundidade_atual == profundidade_alvo) {
            printf("%d ", root->item);
        }
        
            imprimirProfundidade(root->left, profundidade_alvo,profundidade_atual + 1);
            imprimirProfundidade(root->right, profundidade_alvo,profundidade_atual + 1);
    }
}


int main() {
    int profundidade, p;
    scanf("%d", &profundidade);
    scanf("%d", &p);
    int num;
    Node* root = NULL;

    for (int i = 0; i < p; ++i) {
        scanf("%d", &num);
        root = inserir(num,root);
    }

    imprimirProfundidade(root, profundidade,0);
    liberar_arvore(root);
    return 0;
}


