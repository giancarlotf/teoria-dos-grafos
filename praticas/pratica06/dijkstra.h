#ifndef DIJKSTRA_H
#define DIJKSTRA_H 1

// Contexto do ambiente
#ifndef INT_MAX
#define INT_MAX 0x7FFFFFFF
#endif

typedef struct Aresta
{
    int destino;
    int peso;
    struct Aresta *prox;
} Aresta;

typedef struct
{
    int n;
    Aresta **adj;
} GrafoListaPonderado;

GrafoListaPonderado *criar_grafo(int n);
void inserir_arco(GrafoListaPonderado *grafo, int u, int v, int peso);
void inserir_aresta(GrafoListaPonderado *grafo, int u, int v, int peso);
void remover_arco(GrafoListaPonderado *grafo, int u, int v);
void remover_aresta(GrafoListaPonderado *grafo, int u, int v);
void liberar_grafo(GrafoListaPonderado *grafo);

// Implementação do código

typedef struct
{
    int vertice;
    int distancia;
} NoHeap;

typedef struct
{
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; // mapeia vértice -> índice no heap
} MinHeap;

MinHeap *criar_min_heap(GrafoListaPonderado *grafo, int origem);
NoHeap extrair_minimo(MinHeap *heap);
void diminuir_chave(MinHeap *heap, int vertice, int distancia);
void liberar_min_heap(MinHeap *heap);

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_caminho(int origem, int destino, int *pred);

#endif // DIJKSTRA_H
