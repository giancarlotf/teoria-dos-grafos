#ifndef AGM_H
#define AGM_H 1

// Contexto do ambiente

#ifndef MAX_VERTICES
#define MAX_VERTICES 512
#endif

#ifndef INT_MAX
#define INT_MAX 0x7FFFFFFF
#endif

typedef struct No
{
    int destino;
    int peso;
    struct No *prox;
} No;

typedef struct
{
    int n;
    No **adj;
} GrafoListaPonderado;

GrafoListaPonderado *criar_grafo(int n);
void inserir_arco(GrafoListaPonderado *grafo, int u, int v, int peso);
void inserir_aresta(GrafoListaPonderado *grafo, int u, int v, int peso);
void remover_arco(GrafoListaPonderado *grafo, int u, int v);
void remover_aresta(GrafoListaPonderado *grafo, int u, int v);
void liberar_grafo(GrafoListaPonderado *grafo);

typedef struct
{
    int vertice;
    int distancia;
} NoHeap;

typedef struct
{
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao;
} MinHeap;

MinHeap *criar_min_heap(GrafoListaPonderado *grafo, int origem);
NoHeap extrair_minimo(MinHeap *heap);
void diminuir_chave(MinHeap *heap, int vertice, int distancia);
void liberar_min_heap(MinHeap *heap);

// Implementação do código

typedef struct
{
    int *pai, *rank;
    int n;
} DSU;

typedef struct
{
    int u, v, peso;
} Aresta;

// Obs.: com compressão de caminho.
int find(DSU *d, int x);

// Obs.: com união por rank.
int unir(DSU *d, int x, int y);

// Ordenação + seleção, complexidade O(ElogE).
Aresta *kruskal(GrafoListaPonderado *g, int *custo);

// Heap + atualização de chaves, complexidade O((V + E)logV).
Aresta *prim(GrafoListaPonderado *g, int origem, int *custo);

#endif // AGM_H
