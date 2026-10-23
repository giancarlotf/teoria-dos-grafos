#include <stdio.h>
#include <stdlib.h>
#include "busca_grafo.h"
#include "grafo_lista.h"

#define MAX_VISITADO 10
#define MAX_FILA 10

int main()
{
    GrafoLista *grafo = criar_grafo_lista(6);

    adicionar_aresta(grafo, 1, 2);
    adicionar_aresta(grafo, 1, 3);
    adicionar_aresta(grafo, 2, 4);
    adicionar_aresta(grafo, 3, 4);
    adicionar_aresta(grafo, 4, 5);

    int *visitado = (int *)calloc(MAX_VISITADO, sizeof(int));
    dfs(grafo, 1, visitado);

    for (int i = 0; i < MAX_VISITADO; i++)
    {
        visitado[i] = 0;
    }

    puts("");

    int *fila = (int *)malloc(MAX_FILA * sizeof(int));
    bfs(grafo, 1, fila, visitado);

    free(fila);
    free(visitado);
    liberar_grafo_lista(grafo);

    puts("");
    return 0;
}
