#include <stdio.h>
#include "dijkstra.h"

int main()
{
    GrafoListaPonderado *grafo_lp = criar_grafo(6);

    inserir_aresta(grafo_lp, 0, 1, 4);
    inserir_aresta(grafo_lp, 0, 2, 2);
    inserir_aresta(grafo_lp, 1, 2, 1);
    inserir_aresta(grafo_lp, 1, 3, 5);
    inserir_aresta(grafo_lp, 1, 4, 8);
    inserir_aresta(grafo_lp, 2, 3, 4);
    inserir_aresta(grafo_lp, 2, 4, 10);
    inserir_aresta(grafo_lp, 3, 4, 2);
    inserir_aresta(grafo_lp, 3, 5, 1);
    inserir_aresta(grafo_lp, 4, 5, 3);

    int dist[6] = {0};
    int pred[6] = {0};

    int origem = 0;
    int destino = 5;

    dijkstra(grafo_lp, origem, dist, pred);

    printf("Resultado do algoritmo de Dijkstra (origem em %d):\n", origem);

    for (int i = 0; i < grafo_lp->n; i++)
    {
        printf("Vertice: %d\n\tDistancia: %d; Predecessor: %d\n", i, dist[i], pred[i]);
    }

    printf("\nCaminho (%d -> %d):\n", origem, destino);
    reconstruir_caminho(origem, destino, pred);

    liberar_grafo(grafo_lp);

    puts("");

    return 0;
}
