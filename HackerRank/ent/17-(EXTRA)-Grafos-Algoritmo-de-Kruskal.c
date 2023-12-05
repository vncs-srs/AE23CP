/*Implemente, na linguagem C, o algoritmo de Kruskal. A função deve receber um grafo 
representado por uma lista de adjacência e construir uma árvore geradora mínima. A 
nota do exercício será usado como bônus na segunda avaliação.

A entrada/saída do exercício deve seguir o mesmo padrão do exercício do HackerRank 
"Grafos - árvore geradora mínima (listas de adjacência) [05/12/2023]"

Formato de entrada:

A primeira linha contém o número de vértices. A segunda linha contém a quantidade 
de arestas (A). Para cada uma das "A" próximas linhas devem der lidos dois números 
inteiros. sendo os 2 primeiros, a aresta, e o último, o peso da aresta.

Formato de saída:

Imprimir a árvore geradora mínima. Cada linha deve ser impressa no seguinte formato: 
"v_i: pai[v_i]".

Para o vértice da árvore que não tiver "pai", deve ser impresso o caractere "-" 
(traço/sinal de menos). Como o algoritmo deve ser iniciada a partir do vértice "0", 
então a primeira linha sempre será "0: -"*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>


/***************************************************************/
typedef struct Cell Cell;
typedef struct Lista Lista;
typedef struct GrafoLA GrafoLA;
typedef struct FilaE FilaE;

struct Cell {
    int key;
    int item;
    Cell *next;
};

struct Lista {
    Cell *head;
};

struct GrafoLA {
    int V;
    int A;
    Lista **adj;
};

struct FilaE {
    Cell *inicio;
    Cell *fim;
};
typedef struct {
    int u, v, peso;
} Aresta;

typedef struct {
    int pai;
    int rank;
} Subset;
/***************************************************************/
// Lista encadeada

Lista* criar_lista(){
    Lista* l = (Lista*) malloc(sizeof(Lista));

    l->head = NULL;

    return l;
}


Cell* criar_celula(int key){
    Cell *c = (Cell*) malloc(sizeof(Cell));
    c->key = key;

    c->next = NULL;

    return c;
}

int lista_vazia(Lista *l){
    return (l == NULL) || (l->head == NULL);
}


int procurar(int key, Lista *l){
    Cell *aux;

    if (l != NULL){
        aux = l->head;

        while ((aux != NULL) && (key < aux->key))
            aux = aux->next;
    }

    if ((aux != NULL) && (key == aux->key))
        return 1;
    else
        return 0;
}


void inserir_na_lista(int key, Lista *l){
    Cell *auxA, *auxP;
    Cell* c;

    if (lista_vazia(l)){
        if (l == NULL)
            l = criar_lista();

        l->head = criar_celula(key);
    }else{
        c = criar_celula(key);

        if (l->head->key >= key){
           c->next = l->head;


           l->head = c;
        }else{
            auxA = l->head;
            auxP = auxA;

            while ((auxP != NULL) && (auxP->key < key)){
                auxA = auxP;
                auxP = auxP->next;
            }

            auxA->next = c;
            c->next = auxP;
        }
    }
}


int remover_na_lista(int key, Lista *l){
    Cell *auxA, *auxP;

    if (!lista_vazia(l)){
        auxA = l->head;

        if(auxA->key == key)
            l->head = l->head->next;
        else{
            auxP = auxA;

            while((auxA != NULL) && (key < auxA->key)){
                auxP = auxA;
                auxA = auxA->next;
            }

            if (auxA->key == key)
                auxP->next = auxA->next;
            else
                auxA = NULL;
        }

        if (auxA != NULL)
            free(auxA);

        return 1;
    }

        return 0;
}


void imprimir(Lista *l){
    Cell *aux;

    if (!lista_vazia(l)){
        aux = l->head;

        while (aux != NULL){
            printf("%d\n", aux->key);

            aux = aux->next;
        }
    }
}


int liberar_lista(Lista *l){
    Cell *aux;

    if ((l != NULL) && !lista_vazia(l)){

        while(l->head != NULL){
            aux = l->head;

            l->head = aux->next;

            free(aux);
        }

        free(l);

        return 1;
    }

    return 0;
}


/***************************************************************/
// Grafo

static Lista** iniciar_LA(int n){
    int i;
    Lista **adj = (Lista**) malloc(n * sizeof(Lista*));

    for (i = 0; i < n; i++)
        adj[i] = criar_lista();

    return adj;
}


GrafoLA* iniciar_grafoLA(int v){
    GrafoLA* G = (GrafoLA*) malloc(sizeof(GrafoLA));

    G->V = v;
    G->A = 0;
    G->adj = iniciar_LA(G->V);

    return G;
}


int aresta_existeLA(GrafoLA* G, int v1, int v2){
    if ((G!= NULL) && (G->adj[v1]->head != NULL))
        return procurar(v2, G->adj[v1]);

    return 0;
}


void inserir_arestaLA(GrafoLA* G, int v1, int v2){
    if (!aresta_existeLA(G, v1, v2)){
        inserir_na_lista(v2, G->adj[v1]);
      //  inserir_na_lista(v1, G->adj[v2]);
        G->A++;
    }
}


void remover_arestaLA(GrafoLA* G, int v1, int v2){
    if (aresta_existeLA(G, v1, v2)){
        remover_na_lista(v2, G->adj[v1]);
      //  remover_na_lista(v1, G->adj[v2]);
        G->A--;

    }
}


void imprimir_arestasLA(GrafoLA* G){
    int i;
    Cell *aux;

    if (G != NULL)
        for (i = 0; i < G->V; i++){
            aux = G->adj[i]->head;

            while (aux != NULL){
                printf("(%d, %d)\n", i, aux->key);

                aux = aux->next;
            }

        }
}
void liberarGLA(GrafoLA* G){
    int i;

    if (G != NULL){
        for (i = 0; i < G->V; i++)
            liberar_lista(G->adj[i]);

        free(G);
    }
}

FilaE* criar_filaE(){
    FilaE *f = (FilaE*) malloc(sizeof(FilaE));
    
    f->inicio = NULL;
    f->fim = NULL;
    
    return f;
}


int filaE_vazia(FilaE* f){
    return (f == NULL) || (f->inicio == NULL);
}


FilaE* enfileirar(int key, FilaE* f) {
    Cell *aux;

    if (f == NULL)
        f = criar_filaE();

    aux = criar_celula(key);

    if (f->inicio == NULL)
        f->inicio = f->fim = aux;
    else {
        f->fim->next = aux;
        f->fim = f->fim->next;
    }

    return f;  // Retorne a nova fila criada
}


int desenfileirar(FilaE* f) {
    Cell *aux;
    int item = INT_MIN;

    if (!filaE_vazia(f)) {
        aux = f->inicio;

        f->inicio = aux->next;

        item = aux->key;

        free(aux);
    }

    return item;
}



int liberar_filaE(FilaE* f){
    if (!filaE_vazia(f)){
        while (f->inicio != NULL)
            desenfileirar(f);

        free(f);

        return 1;
    }

    return 0;
}
int compararArestas(const void *a, const void *b) {
    return ((Aresta *)a)->peso - ((Aresta *)b)->peso;
}

int encontrar(Subset subsets[], int i) {
    if (subsets[i].pai != i)
        subsets[i].pai = encontrar(subsets, subsets[i].pai);
    return subsets[i].pai;
}

void unir(Subset subsets[], int x, int y) {
    int raizX = encontrar(subsets, x);
    int raizY = encontrar(subsets, y);

    if (subsets[raizX].rank < subsets[raizY].rank)
        subsets[raizX].pai = raizY;
    else if (subsets[raizX].rank > subsets[raizY].rank)
        subsets[raizY].pai = raizX;
    else {
        subsets[raizY].pai = raizX;
        subsets[raizX].rank++;
    }
}

void kruskal(Aresta arestas[], int numVertices, int numArestas) {
    qsort(arestas, numArestas, sizeof(Aresta), compararArestas);

    Subset *subsets = (Subset *)malloc(numVertices * sizeof(Subset));
    for (int i = 0; i < numVertices; i++) {
        subsets[i].pai = i;
        subsets[i].rank = 0;
    }

    printf("0: -\n");

    for (int i = 0; i < numArestas; i++) {
        int raizU = encontrar(subsets, arestas[i].u);
        int raizV = encontrar(subsets, arestas[i].v);

        if (raizU != raizV) {
            printf("%d: %d\n", arestas[i].v, arestas[i].u);
            unir(subsets, raizU, raizV);
        }
    }

    free(subsets);
}

int main() {
    int numVertices, numArestas;
    scanf("%d", &numVertices);
    scanf("%d", &numArestas);

    Aresta *arestas = (Aresta *)malloc(numArestas * sizeof(Aresta));
    for (int i = 0; i < numArestas; i++) {
        scanf("%d %d %d", &arestas[i].u, &arestas[i].v, &arestas[i].peso);
    }

    kruskal(arestas, numVertices, numArestas);

    free(arestas);

    return 0;
}