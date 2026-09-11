#include <stdio.h>
#include <stdlib.h>
#include "../pratica01/grafo_lista.h"
#include "busca_largura.h"
#include "busca_profundidade.h"

int main()
{
    int n = 5;
    GrafoLista *grafo_l = criar_grafo_lista(n);

    inserir_aresta_lista(grafo_l, 0, 1);
    inserir_aresta_lista(grafo_l, 1, 2);
    inserir_aresta_lista(grafo_l, 3, 4);

    // BFS
    int *dist = (int *)malloc(n * sizeof(int));
    int *pred = (int *)malloc(n * sizeof(int));

    bfs(grafo_l, 0, dist, pred);
    puts("Exemplo de Busca por Largura (BFS) a partir de 0:");

    for (int i = 0; i < n; i++)
    {
        printf("Vertice [%d] -> Distancia: %d, Predecessor: %d\n", i, dist[i], pred[i]);
    }

    // DFS
    int *visitado = (int *)calloc(n, sizeof(int));
    int *tempo_entrada = (int *)malloc(n * sizeof(int));
    int *tempo_saida = (int *)malloc(n * sizeof(int));
    int tempo = 0;

    puts("\nExemplo de Busca por Profundidade (DFS) a partir de 0:");
    dfs_recursiva(grafo_l, 0, visitado, tempo_entrada, tempo_saida, &tempo);

    for (int i = 0; i < n; i++)
    {
        printf("Vertice [%d]; Visitado: %d\n", i, visitado[i]);
    }

    // Contar Componentes
    puts("\nExemplo contar_componentes:");
    printf("Total de componentes conexas: %d\n", contar_componentes(grafo_l));

    // Detecção de Ciclo
    puts("\nExemplo tem_ciclo:");

    if (tem_ciclo(grafo_l))
    {
        puts("O grafo possui ciclo.");
    }
    else
    {
        puts("O grafo nao possui ciclo.");
    }

    // Detecção de Bipartição
    puts("\nExemplo eh_bipartido:");

    if (eh_bipartido(grafo_l))
    {
        puts("O grafo e bipartido.");
    }
    else
    {
        puts("O grafo nao e bipartido.");
    }

    free(dist);
    free(pred);
    free(visitado);
    liberar_grafo_lista(grafo_l);

    puts("");
    return 0;
}
