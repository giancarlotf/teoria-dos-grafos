#include <stdio.h>
#include "grafo_matriz.h"

GrafoMatriz *criar_grafo_matriz(int n)
{
    GrafoMatriz *grafo = (GrafoMatriz *)malloc(sizeof(GrafoMatriz));
    grafo->n = n;
    grafo->adj = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++)
    {
        grafo->adj[i] = (int *)calloc(n, sizeof(int));
    }

    return grafo;
}

void inserir_aresta_matriz(GrafoMatriz *grafo, int u, int v)
{
    if (u >= 0 && u < grafo->n && v >= 0 && v < grafo->n)
    {
        grafo->adj[u][v] = 1;
        grafo->adj[v][u] = 1;
    }
}

void remover_aresta_matriz(GrafoMatriz *grafo, int u, int v)
{
    if (u >= 0 && u < grafo->n && v >= 0 && v < grafo->n)
    {
        grafo->adj[u][v] = 0;
        grafo->adj[v][u] = 0;
    }
}

int grau_matriz(GrafoMatriz *grafo, int v)
{
    int grau = 0;

    if (v >= 0 && v < grafo->n)
    {
        for (int i = 0; i < grafo->n; i++)
        {
            if (grafo->adj[v][i] == 1)
            {
                grau++;
            }
        }
    }

    return grau;
}

int sao_adjacentes_matriz(GrafoMatriz *grafo, int u, int v)
{
    if (u >= 0 && u < grafo->n && v >= 0 && v < grafo->n)
    {
        return grafo->adj[u][v] == 1;
    }

    return 0;
}

void liberar_grafo_matriz(GrafoMatriz *grafo)
{
    if (grafo == NULL)
        return;

    for (int i = 0; i < grafo->n; i++)
    {
        free(grafo->adj[i]);
    }

    free(grafo->adj);
    free(grafo);
}
