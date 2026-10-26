#include "bellman_ford.h"
#include <stdio.h>
#include <stdlib.h>

// Contexto do ambiente

GrafoListaPonderado *criar_grafo(int n)
{
    GrafoListaPonderado *grafo = (GrafoListaPonderado *)malloc(sizeof(GrafoListaPonderado));
    grafo->n = n;
    grafo->adj = (Aresta **)malloc(n * sizeof(Aresta *));

    for (int i = 0; i < n; i++)
    {
        grafo->adj[i] = NULL;
    }

    return grafo;
}

void inserir_arco(GrafoListaPonderado *grafo, int u, int v, int peso)
{
    if (u >= 0 && u < grafo->n && v >= 0 && v < grafo->n)
    {
        int sao_adjacentes = 0;
        Aresta *atual = grafo->adj[u];

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
            Aresta *aresta = (Aresta *)malloc(sizeof(Aresta));

            if (!aresta)
            {
                return;
            }

            aresta->destino = v;
            aresta->peso = peso;
            aresta->prox = grafo->adj[u];
            grafo->adj[u] = aresta;
        }
    }
}

void remover_arco(GrafoListaPonderado *grafo, int u, int v)
{
    if (u >= 0 && u < grafo->n && v >= 0 && v < grafo->n)
    {
        Aresta *atual = grafo->adj[u];
        Aresta *anterior = NULL;

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

void liberar_grafo(GrafoListaPonderado *grafo)
{
    if (grafo == NULL)
        return;

    for (int i = 0; i < grafo->n; i++)
    {
        Aresta *atual = grafo->adj[i];

        while (atual != NULL)
        {
            Aresta *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    free(grafo->adj);
    free(grafo);
}

// Implementação do código

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred)
{
    if (!g || !dist || !pred)
    {
        return -1;
    }

    for (int i = 0; i < g->n; i++)
    {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }

    dist[origem] = 0;

    for (int i = 0; i < g->n - 1; i++)
    {
        int alteracao = 0;

        for (int u = 0; u < g->n; u++)
        {
            if (dist[u] == INT_MAX)
            {
                continue;
            }

            Aresta *aresta = g->adj[u];

            while (aresta != NULL)
            {
                int v = aresta->destino;
                int peso = aresta->peso;

                if (dist[u] != INT_MAX && dist[v] > dist[u] + peso)
                {
                    dist[v] = dist[u] + peso;
                    pred[v] = u;
                    alteracao = 1;
                }

                aresta = aresta->prox;
            }
        }

        if (!alteracao)
        {
            break;
        }
    }

    for (int u = 0; u < g->n - 1; u++)
    {
        if (dist[u] == INT_MAX)
        {
            continue;
        }

        Aresta *aresta = g->adj[u];

        while (aresta != NULL)
        {
            int v = aresta->destino;
            int peso = aresta->peso;

            if (dist[u] != INT_MAX && dist[v] > dist[u] + peso)
            {
                pred[v] = u;
                reconstruir_ciclo_negativo(v, g->n, pred);
                return 0;
            }

            aresta = aresta->prox;
        }
    }

    return 1;
}

void reconstruir_ciclo_negativo(int vertice, int n, int *pred)
{
    if (vertice < 0 || vertice >= n || n <= 0 || !pred)
    {
        return;
    }

    int atual = vertice;

    for (int i = 0; i < n; i++)
    {
        if (atual == -1)
        {
            puts("Nao foi possivel reconstruir o ciclo");
            return;
        }

        atual = pred[atual];
    }

    if (atual == -1)
    {
        puts("Nao foi possivel reconstruir o ciclo");
        return;
    }

    int *ciclo = (int *)malloc((n + 1) * sizeof(int));

    if (!ciclo)
    {
        return;
    }

    int inicio = atual;
    int tamanho = 0;

    do
    {
        if (atual == -1 || tamanho >= n)
        {
            puts("Nao foi possivel reconstruir o ciclo");
            free(ciclo);
            return;
        }

        ciclo[tamanho++] = atual;
        atual = pred[atual];
    } while (atual != inicio);

    puts("Ciclo negativo:");

    for (int i = tamanho - 1; i >= 0; i--)
    {
        printf("%d -> ", ciclo[i]);
    }

    printf("%d", ciclo[tamanho - 1]);

    free(ciclo);
}
