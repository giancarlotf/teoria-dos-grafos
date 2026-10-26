#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H 1

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
void remover_arco(GrafoListaPonderado *grafo, int u, int v);
void liberar_grafo(GrafoListaPonderado *grafo);

// Implementação do código

// Retorna 1 (sucesso) ou 0 (ciclo negativo).
int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred);

// Retrocede n vezes pelo pred[] e imprime o ciclo.
void reconstruir_ciclo_negativo(int vertice, int n, int *pred);

#endif // BELLMAN_FORD_H
