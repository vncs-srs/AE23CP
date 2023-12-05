/*Implemente o algoritmo de busca em largura para grafos. Esse algoritmo 
deve ter dois parâmetros: um grafo e um número inteiro, sendo este último 
o vértice raiz da árvore de busca em largura, ou seja, é o vértice a partir 
de onde deve ser iniciado a exploração do grafo. Após, para cada vértice, 
imprima os respectivos pai e distância.

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

A primeira linha contém o número de vértices seguida pela respectiva lista 
de adjacência. Cada uma das seguintes linhas será referente a um vértice v_i, 
onde os vértices adjacentes devem ser lidos. Para cada linha, enquanto o número 
"-1" (menos um) não for lido, um vértice adjacente deve ser lido. Por exemplo, 
suponha que o i-ésimo vértice seja adjacente aos vértices 2 e 5, então a leitura 
deve seguir o seguinte formato:

2 5 -1

Caso o vértice não tenha adjacentes, basta ler -1 (menos 1). Exemplo:

-1

Na última linha deve ser lido um número inteiro que representa um vértice do 
grafo para iniciar a aplicação do algoritmo de busca em largura.

Constraints

O não uso do TAD de lista de adjacências acerratará em 75% de desconto da nota, 
já que a versão com matriz de adjacências é implementada em aula.

Output Format

Na primeira linha deve ser impressa a seguinte sequência de caracteres: "v d p".

A partir da próxima linha, imprimir o vértice, o pai e a distância.

Para cada vértice que não tem pai, deve ser impresso "-" em sua respectiva linha.

Para cada vértice que não foi possível ser descoberto a partir do "vértice raiz", 
também deve ser impresso o caractere "-". Por exemplo: se o vértice x não pode ser descoberto, na sua linha deve ser impresso "x - -"

Sample Input 0
8
1 3 -1
0 2 -1
1 -1
0 4 5 -1
3 5 6 -1
3 4 6 7 -1
4 5 7 -1
5 6 -1
0

Sample Output 0
v d p
0 0 -
1 1 0
2 2 1
3 1 0
4 2 3
5 2 3
6 3 4
7 3 5

Sample Input 1
5
2 4 -1
-1
0 3 -1
2 4 -1
0 3 -1
1

Sample Output 1
v d p
0 - -
1 0 -
2 - -
3 - -
4 - -

Sample Input 2
5
1 2 4 -1
0 -1
0 3 -1
2 4 -1
0 3 -1
1

Sample Output 2
v d p
0 1 1
1 0 -
2 2 0
3 3 2
4 2 0*/

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
void busca_em_largura(GrafoLA* G, int raiz) {
   
    int *distancia = (int*)malloc(G->V * sizeof(int));
    int *pai = (int*)malloc(G->V * sizeof(int));
    FilaE *fila = criar_filaE();

   
    for (int i = 0; i < G->V; i++) {
        distancia[i] = INT_MAX;
        pai[i] = -1;
    }


    distancia[raiz] = 0;
    pai[raiz] = -1;
    enfileirar(raiz, fila);

   
    while (!filaE_vazia(fila)) {
        int u = desenfileirar(fila);

       
        Cell *vizinho = G->adj[u]->head;
        while (vizinho != NULL) {
            int v = vizinho->key;

            
            if (distancia[v] == INT_MAX) {
                distancia[v] = distancia[u] + 1;
                pai[v] = u;
                enfileirar(v, fila);
            }

            vizinho = vizinho->next;
        }
    }

  
printf("v d p\n");
for (int i = 0; i < G->V; i++) {
    if (distancia[i] == INT_MAX) {
        printf("%d - -\n", i);
    } else {
        if (pai[i] == -1) {
            printf("%d 0 -\n", i);
        } else {
            printf("%d %d %d\n", i, distancia[i], pai[i]);
        }
    }
}



    free(distancia);
    free(pai);
    liberar_filaE(fila);
}


int main() {

    int numVertices;
    scanf("%d", &numVertices);

    
    GrafoLA *grafo = iniciar_grafoLA(numVertices);

    
    for (int i = 0; i < numVertices; i++) {
        int adjacente;
        while (1) {
            scanf("%d", &adjacente);
            if (adjacente == -1) {
                break;
            }
            inserir_arestaLA(grafo, i, adjacente);
        }
    }

   
    int verticeRaiz;
    scanf("%d", &verticeRaiz);

    
    busca_em_largura(grafo, verticeRaiz);

   
    liberarGLA(grafo);

    return 0;
}