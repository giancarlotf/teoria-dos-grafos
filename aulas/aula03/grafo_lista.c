#include <stdio.h>
#include "grafo_lista.h"

GrafoLista *criar_grafo_lista(int n)
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

void adicionar_aresta(GrafoLista *grafo, int u, int v)
{
    if (u >= 0 && u < grafo->n && v >= 0 && v < grafo->n)
    {
        if (!sao_adjacentes_lista(grafo, u, v))
        {
            No *no_u = (No *)malloc(sizeof(No));
            no_u->destino = v;
            no_u->prox = grafo->adj[u];
            grafo->adj[u] = no_u;

            No *no_v = (No *)malloc(sizeof(No));
            no_v->destino = u;
            no_v->prox = grafo->adj[v];
            grafo->adj[v] = no_v;
        }
    }
}

void remover_aresta(No **fonte, int destino)
{
    No *atual = *fonte;
    No *anterior = NULL;

    while (atual != NULL && atual->destino != destino)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL)
    {
        (anterior == NULL) ? (*fonte = atual->prox) : (anterior->prox = atual->prox);
        free(atual);
    }
}

void remover_aresta_lista(GrafoLista *grafo, int u, int v)
{
    if (u >= 0 && u < grafo->n && v >= 0 && v < grafo->n)
    {
        remover_aresta(&(grafo->adj[u]), v);
        remover_aresta(&(grafo->adj[v]), u);
    }
}

int grau_lista(GrafoLista *grafo, int v)
{
    int grau = 0;

    if (v >= 0 && v < grafo->n)
    {
        No *atual = grafo->adj[v];

        while (atual != NULL)
        {
            grau++;
            atual = atual->prox;
        }
    }

    return grau;
}

int sao_adjacentes_lista(GrafoLista *grafo, int u, int v)
{
    if (u >= 0 && u < grafo->n)
    {
        No *atual = grafo->adj[u];

        while (atual != NULL)
        {
            if (atual->destino == v)
                return 1;

            atual = atual->prox;
        }
    }

    return 0;
}

void liberar_grafo_lista(GrafoLista *grafo)
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
