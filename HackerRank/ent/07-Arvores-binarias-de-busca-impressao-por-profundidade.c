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
#define N 5

typedef struct NodeB NodeB;

struct NodeB{
     int nro_chaves;
     int chaves[N - 1];
     NodeB *filhos[N];
     int eh_no_folha;
};


NodeB* criar(){
    NodeB *tree = malloc(sizeof(NodeB));
    int i;

    tree->eh_no_folha = 1;
    tree->nro_chaves = 0;

    for (i = 0; i < N; i++)
        tree->filhos[i] = NULL;

    return tree;
}


int liberar(NodeB *tree){
    if (tree != NULL){
        free(tree);

        return 1;
    }

    return 0;
}


static int busca_binaria(int key, NodeB *tree){
    int ini, fim, meio;

    if (tree != NULL){
        ini = 0;
        fim = tree->nro_chaves - 1;

        while (ini <= fim){
            meio = (ini + fim) / 2;

            if (tree->chaves[meio] == key)
                return meio;
            else if (tree->chaves[meio] > key)
                fim = meio - 1;
            else
                ini = meio + 1;
        }

        return ini;
    }

    return -1;
}


int pesquisaSequencial(int key, NodeB *tree){
    int i;

    if (tree != NULL){
        for (i = 0; i < tree->nro_chaves && key < tree->chaves[i]; i++);

	if ((i < tree->nro_chaves) && (key == tree->chaves[i]))
        	return 1;
        else
        	return pesquisaSequencial(key, tree->filhos[i]);
    }

    return 0;
}


int pesquisar(int key, NodeB *tree){
    int pos = busca_binaria(key, tree);

    if (pos >= 0){
        if (tree->chaves[pos] == key)
            return 1;
        else
            return pesquisar(key, tree->filhos[pos]);
    }

    return 0;
}


static NodeB * split_pag(NodeB *pai, int posF_cheio){
    int i;
    
    NodeB *pag_esq = pai->filhos[posF_cheio];
    NodeB *pag_dir;

    pag_dir = criar();
    pag_dir->eh_no_folha = pag_esq->eh_no_folha; 

    pag_dir->nro_chaves = round((N - 1) / 2);
    pag_esq->nro_chaves = (N - 1) / 2;

    for (i = 0; i < pag_dir->nro_chaves; i++)
        pag_dir->chaves[i] = pag_esq->chaves[i + pag_esq->nro_chaves];

    if (!pag_esq->eh_no_folha)
        for (i = 0; i < pag_dir->nro_chaves; i++)
            pag_dir->filhos[i] = pag_esq->filhos[i + pag_esq->nro_chaves];

    for (i = pai->nro_chaves + 1; i > posF_cheio + 1; i--)
        pai->filhos[i + 1] = pai->filhos[i];

    pai->filhos[posF_cheio + 1] = pag_dir;
    pai->filhos[posF_cheio] = pag_esq;
    pai->chaves[posF_cheio] = pag_dir->chaves[0];
    pai->nro_chaves++;

    for (i = 0; i < pag_dir->nro_chaves ; i++)
        pag_dir->chaves[i] = pag_dir->chaves[i + 1];

    pag_dir->nro_chaves--;

    
    return pai;
}


static NodeB * inserir_pagina_nao_cheia(NodeB *tree, int key){
    int i;
    int pos = busca_binaria(key, tree);

    if (tree->eh_no_folha){
        for (i = tree->nro_chaves; i > pos; i--)
            tree->chaves[i] = tree->chaves[i - 1];

        tree->chaves[i] = key;
        tree->nro_chaves++;

    }else{
        if (tree->filhos[pos]->nro_chaves == N - 1){
            tree = split_pag(tree, pos);

            if (key > tree->chaves[pos])
                pos++;
        }

        tree->filhos[pos] = inserir_pagina_nao_cheia(tree->filhos[pos], key);

    }

    return tree;
}


NodeB * inserir(NodeB *tree, int key){
    NodeB *aux = tree;
    NodeB *nova_pag;

    if (aux->nro_chaves == N - 1){
        nova_pag = criar();
        
        tree = nova_pag;
        
        nova_pag->eh_no_folha = 0;
        nova_pag->filhos[0] = aux;
        nova_pag = split_pag(nova_pag, 0);
        nova_pag = inserir_pagina_nao_cheia(nova_pag, key);

        tree = nova_pag;
    }else
        tree = inserir_pagina_nao_cheia(aux, key);

    return tree;
}
void imprimirProfundidade(NodeB* root, int profundidade_atual, int profundidade_alvo) {
    if (root == NULL) {
        return;
    }

    if (profundidade_atual == profundidade_alvo) {
        for (int i = 0; i < root->nro_chaves; i++) {
            printf("%d ", root->chaves[i]);
        }
    } else {
        for (int i = 0; i < root->nro_chaves + 1; i++) {
            imprimirProfundidade(root->filhos[i], profundidade_atual + 1, profundidade_alvo);
        }
    }
}

int main() {
    int profundidade, p;
    scanf("%d", &profundidade);
    scanf("%d", &p);
    int num[p];
    NodeB* root = criar();

    for (int i = 0; i < p; ++i) {
        scanf("%d", &num[i]);
        root = inserir(root, num[i]);
    }

    imprimirProfundidade(root,1, profundidade);
    free(root);
    return 0;
}
