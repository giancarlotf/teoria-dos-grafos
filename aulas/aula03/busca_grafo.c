#include "busca_grafo.h"

void dfs(GrafoLista *grafo, int u, int *visitado)
{
    visitado[u] = 1;
    No *no = grafo->adj[u];

    while(no != NULL)
    {
        int v = no->destino;

        if(!visitado[v])
            dfs(grafo, v, visitado);

        no = no->prox;
    }
}

void bfs(GrafoLista *grafo, int u, int *fila, int *visitado)
{
    int inicio = 0, fim = 0;
    visitado[inicio] = 1;
    fila[fim++] = inicio;

    while(inicio < fim)
    {
        int u = fila[inicio++];
        No *no = grafo->listas[u];

        while (p != NULL)
        {
            int v = no->vertice;

            if(!visitado[v])
            {
                visitado[v] = 1;
                fila[fim++] = v;
            }

            no = no->prox;
        }
    }
}
