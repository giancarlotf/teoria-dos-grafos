#ifndef DAG_H
#define DAG_H

typedef struct No
{
    int destino;
    struct No *prox;
} No;

typedef struct
{
    int n;
    No **adj;
} GrafoLista;

GrafoLista *criar_grafo(int n);
void inserir_arco(GrafoLista *grafo, int u, int v);
void remover_arco(GrafoLista *grafo, int u, int v);
void liberar_grafo(GrafoLista *grafo);

typedef struct {
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;

Fila* criar_fila(int capacidade);
void enfileirar(Fila *f, int v);
int desenfileirar(Fila *f);
int fila_vazia(Fila *f);
void liberar_fila(Fila *f);

int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho);
int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho);
int eh_dag(GrafoLista *g);

#endif