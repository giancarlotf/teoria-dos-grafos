#include <stdlib.h>
#include "dag.h"

GrafoLista *criar_grafo(int n)
{
    GrafoLista *grafo = (GrafoLista *)malloc(sizeof(GrafoLista));
    grafo->n = n;
    grafo->adj = (No **)malloc(n * sizeof(No *));

    for (int i = 0; i < n; i++)
    {
        grafo->adj[i] = NULL;
    }

    return grafo;
}

void inserir_arco(GrafoLista *grafo, int u, int v)
{
    if (u >= 0 && u < grafo->n && v >= 0 && v < grafo->n)
    {
        int sao_adjacentes = 0;
        No *atual = grafo->adj[u];

        while (atual != NULL)
        {
            if (atual->destino == v)
            {
                sao_adjacentes = 1;
                break;
            }

            atual = atual->prox;
        }

        if (sao_adjacentes == 0)
        {
            No *no = (No *)malloc(sizeof(No));
            no->destino = v;
            no->prox = grafo->adj[u];
            grafo->adj[u] = no;
        }
    }
}

void remover_arco(GrafoLista *grafo, int u, int v)
{
    if (u >= 0 && u < grafo->n && v >= 0 && v < grafo->n)
    {
        No *atual = grafo->adj[u];
        No *anterior = NULL;

        while (atual != NULL && atual->destino != v)
        {
            anterior = atual;
            atual = atual->prox;
        }

        if (atual != NULL)
        {
            (anterior == NULL) ? (grafo->adj[u] = atual->prox) : (anterior->prox = atual->prox);
            free(atual);
        }
    }
}

void liberar_grafo(GrafoLista *grafo)
{
    if (grafo == NULL)
        return;

    for (int i = 0; i < grafo->n; i++)
    {
        No *atual = grafo->adj[i];

        while (atual != NULL)
        {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    free(grafo->adj);
    free(grafo);
}

Fila* criar_fila(int capacidade)
{
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->capacidade = capacidade;
    f->dados = (int*) malloc(capacidade * sizeof(int));
    f->inicio = 0;
    f->fim = -1;
    f->tamanho = 0;
    return f;
}

void enfileirar(Fila *f, int v)
{
    if (f->tamanho < f->capacidade)
    {
        f->fim = (f->fim + 1) % f->capacidade;
        f->dados[f->fim] = v;
        f->tamanho++;
    }
}

int desenfileirar(Fila *f)
{
    if (f->tamanho == 0) return -1;
    int v = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return v;
}

int fila_vazia(Fila *f)
{
    return f->tamanho == 0;
}

void liberar_fila(Fila *f)
{
    free(f->dados);
    free(f);
}

int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho)
{
    int n = g->n;
    int *grau_entrada = (int *)calloc(n, sizeof(int));

    for (int u = 0; u < n; u++)
    {
        No *atual = g->adj[u];

        while (atual != NULL)
        {
            grau_entrada[atual->destino]++;
            atual = atual->prox;
        }
    }

    Fila *f = criar_fila(n);
    for (int i = 0; i < n; i++)
    {
        if (grau_entrada[i] == 0)
        {
            enfileirar(f, i);
        }
    }

    int *ordenacao = (int *)malloc(n * sizeof(int));
    int count = 0;

    while (!fila_vazia(f))
    {
        int u = desenfileirar(f);
        ordenacao[count++] = u;
        No *atual = g->adj[u];

        while (atual != NULL)
        {
            int v = atual->destino;
            grau_entrada[v]--;

            if (grau_entrada[v] == 0)
            {
                enfileirar(f, v);
            }

            atual = atual->prox;
        }
    }

    liberar_fila(f);
    free(grau_entrada);

    if (count != n)
    {
        free(ordenacao);
        *tamanho = 0;
        return NULL;
    }

    *tamanho = n;
    return ordenacao;
}

int dfs_visitar_topologica(GrafoLista *g, int u, int *visitado, int *pilha, int *topo)
{
    visitado[u] = 1;
    No *atual = g->adj[u];

    while (atual != NULL)
    {
        int v = atual->destino;

        if (visitado[v] == 1)
        {
            return 0;
        }
        if (visitado[v] == 0)
        {
            if (!dfs_visitar_topologica(g, v, visitado, pilha, topo))
            {
                return 0;
            }
        }
        atual = atual->prox;
    }

    visitado[u] = 2;
    pilha[(*topo)--] = u;
    return 1;
}

int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho)
{
    int n = g->n;
    int *visitado = (int *)calloc(n, sizeof(int));
    int *pilha = (int *)malloc(n * sizeof(int));
    int topo = n - 1;

    for (int i = 0; i < n; i++)
    {
        if (visitado[i] == 0)
        {
            if (!dfs_visitar_topologica(g, i, visitado, pilha, &topo))
            {
                free(visitado);
                free(pilha);
                *tamanho = 0;
                return NULL;
            }
        }
    }

    free(visitado);
    *tamanho = n;
    return pilha;
}

int dfs_ciclo(GrafoLista *g, int u, int *pilha_rec)
{
    pilha_rec[u] = 1;
    No *atual = g->adj[u];

    while (atual != NULL)
    {
        int v = atual->destino;

        if (pilha_rec[v] == 1)
        {
            return 1;
        }
        if (pilha_rec[v] == 0)
        {
            if (dfs_ciclo(g, v, pilha_rec))
            {
                return 1;
            }
        }

        atual = atual->prox;
    }

    pilha_rec[u] = 2;
    return 0;
}

int eh_dag(GrafoLista *g)
{
    int n = g->n;
    int *pilha_rec = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
    {
        if (pilha_rec[i] == 0) {
            if (dfs_ciclo(g, i, pilha_rec))
            {
                free(pilha_rec);
                return 0;
            }
        }
    }

    free(pilha_rec);
    return 1;
}
