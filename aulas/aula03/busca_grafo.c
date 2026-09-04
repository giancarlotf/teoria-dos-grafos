#include <stdio.h>
#include "busca_grafo.h"

void dfs(GrafoLista *grafo, int u, int *visitado)
{
    visitado[u] = 1;
    printf("Empilha: [%d]\n", u);
    No *no = grafo->adj[u];

    while (no)
    {
        int v = no->destino;

        if (!visitado[v])
            dfs(grafo, v, visitado);

        no = no->prox;
    }

    printf("Desempilha: [%d]\n", u);
}

void bfs(GrafoLista *grafo, int vertice, int *fila, int *visitado)
{
    int inicio = 0;
    int fim = 0;
    visitado[vertice] = 1;
    printf("Enfileira: [%d]\n", vertice);
    fila[fim++] = vertice;

    while (inicio < fim)
    {
        int u = fila[inicio++];
        printf("Desenfileira: [%d]\n", u);
        No *no = grafo->adj[u];
        printf("\tVisita: [%d]\n", u);

        while (no)
        {
            int v = no->destino;

            if (!visitado[v])
            {
                visitado[v] = 1;
                fila[fim++] = v;
                printf("\tEnfileira: [%d]\n", v);
            }

            no = no->prox;
        }
    }
}