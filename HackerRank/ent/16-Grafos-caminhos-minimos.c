/*Implemente o algoritmo de Dijkstra. A função deve receber um grafo representado 
por uma lista de adjacência e construir uma árvore de caminhos mínimos, que deve 
ser construída a partir do vértice "0".

Para a implementação, considere o grafo representado por lista de adjacências, 
conforme as estruturas apresentadas abaixo:

typedef struct {
   int V; // número de vértices
   int A; // número de arestas
   Lista **adj; // lista de adjacências
}GrafoLA;

typedef struct Cell Cell;

struct Cell{
    int key;
    Cell *next;
};


typedef struct{
    Cell *head;
}Lista;
Input Format

A primeira linha contém o número de vértices. A segunda linha contém a quantidade 
de arestas (A). Para cada uma das "A" próximas linhas devem der lidos dois números 
inteiros. sendo os 2 primeiros, a aresta, e o último, o peso da aresta.

Constraints

O não uso do TAD de lista de adjacências acerratará em 75% de desconto da nota, 
já que a versão com matriz de adjacências é implementada em aula..

Output Format

Imprimir a árvore de caminhos mínimos. Cada linha deve ser impressa no seguinte 
formato: "v_i: pai[v_i]".

Para o vértice da árvore que não tiver "pai", deve ser impresso o caractere "-"
(traço/sinal de menos). Como o algoritmo deve ser iniciada a partir do vértice 
"0", então a primeira linha sempre será "0: -"

Sample Input 0
6
12
0 1 10
0 2 5
1 2 2
1 3 1
2 1 3
2 3 9
2 4 2
3 4 4
3 5 2
4 0 7
4 3 6
4 5 5

Sample Output 0
0: -
1: 2
2: 0
3: 1
4: 2
5: 3

Explanation 0

Na linha 3 da entrada, 0 e 1 forma uma aresta e o valor 10 é o respectivo peso dessa 
aresta.*/ 
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

/***************************************************************/
typedef struct Cell Cell;
typedef struct Lista Lista;
typedef struct GrafoLA GrafoLA;

struct Cell {
    int key;
    int peso;
    Cell *next;
};

struct Lista {
    Cell *head;
};

struct GrafoLA {
    int V;
    int A;
    Lista **adj;
    int *nalila;  
    int *pai;
    int *key;
};

/***************************************************************/
// Lista encadeada

Lista* criar_lista() {
    Lista* l = (Lista*)malloc(sizeof(Lista));
    l->head = NULL;
    return l;
}

Cell* criar_celula(int key, int peso) {
    Cell *c = (Cell*)malloc(sizeof(Cell));
    c->key = key;
    c->peso = peso;
    c->next = NULL;
    return c;
}

int lista_vazia(Lista *l) {
    return (l == NULL) || (l->head == NULL);
}

int procurar(int key, Lista *l) {
    Cell *aux;

    if (l != NULL) {
        aux = l->head;

        while ((aux != NULL) && (key < aux->key))
            aux = aux->next;
    }

    if ((aux != NULL) && (key == aux->key))
        return 1;
    else
        return 0;
}

void inserir_na_lista(int key, int peso, Lista *l) {
    Cell *c = criar_celula(key, peso);

    if (l->head == NULL || peso < l->head->peso) {
        c->next = l->head;
        l->head = c;
    } else {
        Cell *prev = NULL;
        Cell *atual = l->head;

        while (atual != NULL && peso >= atual->peso) {
            prev = atual;
            atual = atual->next;
        }

        prev->next = c;
        c->next = atual;
    }
}

int remover_na_lista(int key, Lista *l) {
    Cell *auxA, *auxP;

    if (!lista_vazia(l)) {
        auxA = l->head;

        if (auxA->key == key)
            l->head = l->head->next;
        else {
            auxP = auxA;

            while ((auxA != NULL) && (key < auxA->key)) {
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

void imprimir(Lista *l) {
    Cell *aux;

    if (!lista_vazia(l)) {
        aux = l->head;

        while (aux != NULL) {
            printf("%d\n", aux->key);

            aux = aux->next;
        }
    }
}

int liberar_lista(Lista *l) {
    Cell *aux;

    if ((l != NULL) && !lista_vazia(l)) {

        while (l->head != NULL) {
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

static Lista** iniciar_LA(int n) {
    int i;
    Lista **adj = (Lista**)malloc(n * sizeof(Lista*));

    for (i = 0; i < n; i++)
        adj[i] = criar_lista();

    return adj;
}

GrafoLA* iniciar_grafoLA(int v) {
    GrafoLA* G = (GrafoLA*)malloc(sizeof(GrafoLA));
    G->V = v;
    G->A = 0;
    G->adj = (Lista**)malloc(v * sizeof(Lista*));
    G->nalila = malloc(sizeof(int) * v);
    G->pai = malloc(sizeof(int) * v);
    G->key = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++)
        G->adj[i] = criar_lista();

    return G;
}

int aresta_existeLA(GrafoLA* G, int v1, int v2) {
    if ((G != NULL) && (G->adj[v1]->head != NULL))
        return procurar(v2, G->adj[v1]);

    return 0;
}

void inserir_arestaLA(GrafoLA* G, int v1, int v2, int peso) {
    inserir_na_lista(v2, peso, G->adj[v1]);
    G->A++;
}

void remover_arestaLA(GrafoLA* G, int v1, int v2) {
    if (aresta_existeLA(G, v1, v2)) {
        remover_na_lista(v2, G->adj[v1]);
        remover_na_lista(v1, G->adj[v2]);
        G->A--;
    }
}

void imprimir_arestasLA(GrafoLA* G) {
    int i;
    Cell *aux;

    if (G != NULL)
        for (i = 0; i < G->V; i++) {
            aux = G->adj[i]->head;

            while (aux != NULL) {
                printf("(%d, %d)\n", i, aux->key);

                aux = aux->next;
            }
        }
}

void liberarGLA(GrafoLA* G) {
    int i;

    if (G != NULL) {
        for (i = 0; i < G->V; i++)
            liberar_lista(G->adj[i]);

        free(G);
    }
}

void dijkstra(GrafoLA* G) {
    int *distancia = (int*)malloc(G->V * sizeof(int));
    int *pai = (int*)malloc(G->V * sizeof(int));
    int *processado = (int*)malloc(G->V * sizeof(int));

    for (int i = 0; i < G->V; i++) {
        distancia[i] = INT_MAX;
        pai[i] = -1;
        processado[i] = 0;
    }

    distancia[0] = 0;

    for (int i = 0; i < G->V; i++) {
        int u = -1;

        for (int j = 0; j < G->V; j++) {
            if (!processado[j] && (u == -1 || distancia[j] < distancia[u])) {
                u = j;
            }
        }

        processado[u] = 1;

        Cell *v = G->adj[u]->head;

        while (v != NULL) {
            int alt = distancia[u] + v->peso;

            if (alt < distancia[v->key]) {
                distancia[v->key] = alt;
                pai[v->key] = u;
            }

            v = v->next;
        }
    }

    // Imprimir resultados
    for (int v = 0; v < G->V; v++) {
        printf("%d: ", v);

        if (pai[v] >= 0)
            printf("%d\n", pai[v]);
        else
            printf("-\n");
    }

    free(distancia);
    free(pai);
    free(processado);
}

void liberar_grafo(GrafoLA* G) {
    for (int i = 0; i < G->V; i++)
        liberar_lista(G->adj[i]);

    free(G->adj);
    free(G);
}

int main() {
    int numVertices;
    scanf("%d", &numVertices);

    GrafoLA* grafo = iniciar_grafoLA(numVertices);

    int numArestas;
    scanf("%d", &numArestas);

    for (int i = 0; i < numArestas; i++) {
        int v1, v2, peso;
        scanf("%d %d %d", &v1, &v2, &peso);
        inserir_arestaLA(grafo, v1, v2, peso);
    }

    dijkstra(grafo);

    liberar_grafo(grafo);

    return 0;
}